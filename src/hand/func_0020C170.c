// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern f32 D_0036BB98;

void func_0020C170(void *arg0) {
    void *temp_v0;

    if (M2C_FIELD(arg0, f32 *, 0x18) < (D_0036BB98 - M2C_FIELD(arg0, f32 *, 0x14))) {
        temp_v0 = M2C_FIELD(arg0, void **, 0xE8);
        M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0x34)(arg0 + M2C_FIELD(temp_v0, s16 *, 0x30));
    }
}
