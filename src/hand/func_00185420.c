// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern f32 D_0036BB98;

void func_00185420(void *arg0, f32 fparg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x42FC);
    if (temp_v1 != NULL) {
        M2C_FIELD(temp_v1, s32 *, 0x7C) = 0;
        temp_v0 = M2C_FIELD(temp_v1, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0x1C4)(temp_v1 + M2C_FIELD(temp_v0, s16 *, 0x1C0));
    }
    M2C_FIELD(arg0, f32 *, 0x4F60) = (f32) (D_0036BB98 + fparg0);
}
