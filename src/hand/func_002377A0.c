// Advance the countdown and choose the next cyclic entry when its timer expires.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0011AEF8(s32);                             /* extern */
s32 func_0011E8F0(M2C_UNK, s32);                    /* extern */
f32 func_0011E940(f32, f32);                        /* extern */
M2C_UNK func_00237220(void *, s32);                 /* extern */
extern f32 D_0036BB9C;

void func_002377A0(void *arg0) {
    f32 temp_f1;
    f32 var_f0;
    s32 temp_5;

    if (func_0011AEF8(arg0 + 0x38) == 0) {
        temp_5 = M2C_FIELD(arg0, s32 *, 0x1C);
        if (temp_5 >= 2) {
            temp_f1 = M2C_FIELD(arg0, f32 *, 0x58);
            if (temp_f1 > 0.0f) {
                var_f0 = temp_f1 - D_0036BB9C;
            } else {
                func_00237220(arg0, (s32) (M2C_FIELD(arg0, u16 *, 0x28) + func_0011E8F0(1, temp_5 - 1)) % (s32) M2C_FIELD(arg0, s32 *, 0x1C));
                var_f0 = func_0011E940(M2C_FIELD(arg0, f32 *, 0x50), M2C_FIELD(arg0, f32 *, 0x54));
            }
            M2C_FIELD(arg0, f32 *, 0x58) = var_f0;
        }
    }
}
