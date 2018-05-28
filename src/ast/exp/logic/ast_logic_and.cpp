#include "sem/exp/sem_logic.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_logic.h"
#include "ast/exp/logic/ast_logic_and.h"

ast_logic_and::ast_logic_and(ast_value_node *child_l, ast_value_node *child_r) : ast_logic(child_l, child_r) {}

void ast_logic_and::do_logic() {
    s_value = sem::do_logic_and(child_l->get_value(), child_r->get_value());
}

void ast_logic_and::codegen() {
    if (s_value.known) {
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_logic_and(child_l->get_llvm_value(), child_r->get_llvm_value()
        );
    }
}

void ast_logic_and::explain_impl(std::string &res, int indent) const {
    logic_explain_impl("and", res, indent);
}