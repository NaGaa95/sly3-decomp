// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_001710E0(void *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x130) == 3) {
        var_a1 = M2C_FIELD(arg0, s32 *, 0x140) == M2C_FIELD(arg0, s32 *, 0x144);
    }
    return var_a1;
}
