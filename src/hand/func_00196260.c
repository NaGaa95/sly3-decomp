// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_00196260(void *arg0, void *arg1) {
    s32 var_a2;

    var_a2 = 0;
    if ((M2C_FIELD(arg1, s32 *, 0) == M2C_FIELD(arg0, s32 *, 4)) && (M2C_FIELD(arg1, s32 *, 4) == M2C_FIELD(arg0, s32 *, 8))) {
        var_a2 = M2C_FIELD(arg1, s32 *, 8) == M2C_FIELD(arg0, s32 *, 0xC);
    }
    return var_a2;
}
