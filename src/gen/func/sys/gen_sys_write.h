#ifndef MY_PASCAL_GEN_SYS_WRITE_H
#define MY_PASCAL_GEN_SYS_WRITE_H

#include <vector>

#include "ast/ast_node.h"

namespace gen {
    void gen_write(std::vector<ast_value_node *> args, bool new_line);
}

#endif //MY_PASCAL_GEN_SYS_WRITE_H