// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_002385A8(void *arg0) {
    s32 var_s0;
    s32 var_v0;
    void *temp_v0;
    void *temp_v1;

    var_s0 = M2C_FIELD(arg0, s32 *, 4) - 1;
    if (var_s0 >= 0) {
        var_v0 = var_s0 * 4;
        do {
            var_s0 -= 1;
            temp_v1 = M2C_FIELD((arg0 + var_v0), void **, 8);
            temp_v0 = M2C_FIELD(temp_v1, void **, 0xC);
            M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0x54)(temp_v1 + M2C_FIELD(temp_v0, s16 *, 0x50));
            var_v0 = var_s0 * 4;
        } while (var_s0 >= 0);
    }
}
