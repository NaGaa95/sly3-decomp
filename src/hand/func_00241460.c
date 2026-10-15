// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_00241460(void *arg0, f32 fparg0) {
    s32 temp_v1;
    void *temp_v0;

    if (fparg0 != 0.0f) {
        temp_v0 = M2C_FIELD(arg0, void **, 0xC);
        {
            void (*method)(void *) = M2C_FIELD(temp_v0, void (**)(void *), 0x44);
            s16 adjustment = M2C_FIELD(temp_v0, s16 *, 0x40);
            method((char *)arg0 + adjustment);
        }
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x3C);
        if ((temp_v1 ^ 1) & 1) {
            *(s32 *)temp_v1 = (s32) (*(s32 *)temp_v1 | 2);
        } else {
            M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_v1 | 2);
        }
    }
    M2C_FIELD(arg0, f32 *, 0x108) = fparg0;
}
