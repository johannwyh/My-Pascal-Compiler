#ifndef MPC_GEN_ARRAY_TYPE_H
#define MPC_GEN_ARRAY_TYPE_H

#include <llvm/IR/DerivedTypes.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::ArrayType *get_llvm_array_type(const sem_type &type);
}

#endif //MPC_GEN_ARRAY_TYPE_H
