#ifndef MPC_SEM_CALL_H
#define MPC_SEM_CALL_H

#include <vector>

#include "sem/type/sem_type.h"
#include "sem/func/sem_func.h"

namespace sem {
    func_sign_ret get_call_func_sign_ret(const func_sign &call_sign, const std::vector<bool> &rval_vec);
}

#endif //MPC_SEM_CALL_H
