// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_00262B00(void *arg0, s32 arg1, s32 arg2) {
    s32 var_t0;
    void *temp_v1;

    var_t0 = 1;
    if (M2C_FIELD(arg0, s32 *, 0x40) > 0) {
        do {
            temp_v1 = M2C_FIELD(arg0, s32 *, 0x44) + (var_t0 * 0x30);
            if ((M2C_FIELD(temp_v1, s32 *, 4) == 1) && (M2C_FIELD(temp_v1, s32 *, 0xC) == arg1)) {
                M2C_FIELD(temp_v1, s32 *, 0x24) = arg2;
            }
            var_t0 += 1;
        } while (M2C_FIELD(arg0, s32 *, 0x40) >= var_t0);
    }
}
