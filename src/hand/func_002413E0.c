// Apply the requested value and choose the eligible virtual activation or release callback.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0013B500(void *, s32);                         /* extern */

void func_002413E0(void *arg0, f32 fparg0) {
    void *temp_2;
    void *temp_2_2;

    if (fparg0 <= 0.0f) {
        if (func_0013B500(arg0, 0x76) == 0) {
            temp_2 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2, M2C_UNK (**)(void *), 0x4C)(arg0 + M2C_FIELD(temp_2, s16 *, 0x48));
        }
    } else {
        temp_2_2 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_2_2, M2C_UNK (**)(void *), 0x44)(arg0 + M2C_FIELD(temp_2_2, s16 *, 0x40));
    }
    M2C_FIELD(arg0, f32 *, 0x104) = fparg0;
}
