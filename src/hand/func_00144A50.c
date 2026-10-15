// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

f32 func_00144A50(void *arg0) {
    f32 var_f1;

    var_f1 = M2C_FIELD(arg0, f32 *, 0x19C);
    if (M2C_FIELD(arg0, s32 *, 0x3CC) != 0) {
        var_f1 *= M2C_FIELD(arg0, f32 *, 0x1A0);
    }
    return var_f1;
}
