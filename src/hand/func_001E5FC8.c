// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_001E5FC8(void *arg0) {
    s32 temp_v1;
    s32 var_a1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x13C);
    var_a1 = 0;
    if (((temp_v1 >= 0) && (temp_v1 < M2C_FIELD(arg0, s32 *, 0x140))) || (temp_v1 == -1)) {
        var_a1 = 1;
    }
    return var_a1;
}
