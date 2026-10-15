// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_00240E10(void *arg0, s32 arg1) {
    s32 temp_a3;
    s32 var_a0;
    s32 var_a2;
    s32 var_v1;

    temp_a3 = M2C_FIELD(arg0, s32 *, 0x100);
    var_a2 = 0;
    if (temp_a3 != 0) {
        var_v1 = 0;
        var_a0 = 1;
        do {
            if (var_a0 & arg1) {
                var_a2 |= M2C_FIELD((temp_a3 + var_v1), u8 *, 4);
            }
            var_v1 += 1;
            var_a0 *= 2;
        } while (var_v1 < 0x1A);
    }
    return var_a2;
}
