#include "sem/id/sem_id.h"
#include "gen/gen.h"
#include "gen/id/gen_id.h"
#include "gen/val/gen_literal.h"
#include "ast/id/ast_id.h"

ast_id::ast_id(const char *id) : id(id) {
    for (char &c : this->id) {
        if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }
    }
}

const sem_type &ast_id::get_type() const {
    return sem::get_id_type(id);
}

const sem_value &ast_id::get_value() const {
    return sem::get_id_value(id);
}

const std::string &ast_id::get_id() const {
    return id;
}

llvm::Value *ast_id::get_llvm_mem() const {
    return gen::get_mem(id);
}

bool ast_id::semantics_self() {
    return true;
}

void ast_id::codegen() {
    if (sem::is_const_id(id)) {
        llvm_value = gen::get_llvm_const(get_type(), get_value());
    } else if (sem::is_declared_val(id) && !get_type().is_type) {
        llvm_value = ir_builder.CreateLoad(get_llvm_mem(), id);
    }
}

void ast_id::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "id(" + id + ")\n";
}
