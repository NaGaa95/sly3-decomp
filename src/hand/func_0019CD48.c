// Update selection ownership and derive the expiry time from the original delay.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0013CD10(M2C_UNK *, void *);           /* extern */
extern f32 D_00321FD4;
extern f32 D_0036BB98;
extern M2C_UNK D_00475480;

void func_0019CD48(void *arg0, s32 arg1) {
    f32 temp_f1;
    f32 var_f0;

    if (arg1 != M2C_FIELD(arg0, s32 *, 0x1F8)) {
        M2C_FIELD(arg0, s32 *, 0x1F8) = arg1;
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xDC), s32 *, 0x60) == arg0) {
            func_0013CD10(&D_00475480, arg0);
        }
    }
    temp_f1 = M2C_FIELD(arg0, f32 *, 0x1F4);
    if (temp_f1 != 0.0f) {
        var_f0 = D_0036BB98 + temp_f1;
    } else {
        var_f0 = D_00321FD4;
    }
    M2C_FIELD(arg0, f32 *, 0x1F0) = var_f0;
}
