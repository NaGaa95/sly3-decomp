// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_00260738(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x48) < 2) {
        var_v1 = M2C_FIELD(arg0, s32 *, 0x54) < 2;
    }
    return var_v1;
}
