#include "sem/type/sem_range_type.h"
#include "sem/type/sem_array_type.h"
#include "sem/type/sem_str_type.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_arith.h"
#include "ast/exp/array/ast_array_idx.h"

ast_array_idx::ast_array_idx(ast_value_node *arr, ast_exp_seq *idx_seq) : arr(arr), idx_seq(idx_seq) {}

ast_array_idx::~ast_array_idx() {
    delete arr;
    delete idx_seq;
}

bool ast_array_idx::semantics_child() {
    return arr->analyse(false) && idx_seq->analyse();
}

bool ast_array_idx::semantics_self() {
    try {
        const std::vector<ast_value_node *> &idx_vec = idx_seq->get_exp_vec();
        const sem_type &t = arr->get_type();

        // Note: index operator can also visit a string
        try {
            sem::assert_is_array_value(t);
        } catch (const sem_exception &) {
            try {
                sem::assert_is_str_value(t);
            } catch (const sem_exception &) {
                throw sem_exception("semantics error, must be an array value or a string value");
            }
        }

        const sem_array_type &a_t = (
                t.tg == type_group::ARRAY ?
                sem::get_array_type_by_idx(t.id) :
                sem::get_str_array_type(t)
        );
        if (a_t.dim < idx_vec.size()) {
            throw sem_exception("semantics error, array dimension is not enough");
        }

        // Calculate bias of each dimension
        std::vector<llvm::Value *> v;
        v.emplace_back(gen::get_llvm_int(0));

        for (int i = 0; i < idx_vec.size(); i++) {
            const sem_range_type &r_t = sem::get_range_type_by_idx(a_t.range_vec[i]);
            if (r_t.type != idx_vec[i]->get_type()) {
                throw sem_exception(
                        "semantics error, index type is not consistent with the original index type of the array"
                );
            }
            llvm::Value *bias = gen::gen_arith_sub(
                    built_in_type::INT_TYPE,
                    idx_vec[i]->get_llvm_value(), gen::get_llvm_const(r_t.type, r_t.low)
            );
            v.emplace_back(bias);
        }

        // Determine semantics type
        if (a_t.dim == idx_vec.size()) {
            s_type = a_t.ele_type;
            s_type.is_type = false;
        } else {
            std::vector<int> na_t_v;
            for (auto i = (int) idx_vec.size(); i < a_t.dim; i++) {
                na_t_v.emplace_back(a_t.range_vec[i]);
            }
            sem_array_type na_t = {a_t.ele_type, a_t.dim - (int) idx_vec.size(), na_t_v};
            s_type = {false, type_group::ARRAY, sem::get_or_define_array_type(na_t)};
        }

        llvm_mem = ir_builder.CreateGEP(arr->get_llvm_mem(), v, "arr_ptr");
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_array_idx::codegen() {
    llvm_value = ir_builder.CreateLoad(llvm_mem, "load_arr");
}

void ast_array_idx::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "array_index(\n";

    explain_indent(res, indent + 1);
    res += "--- array ---\n";
    arr->explain_impl(res, indent + 1);

    explain_indent(res, indent + 1);
    res += "--- index ---\n";
    idx_seq->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}
