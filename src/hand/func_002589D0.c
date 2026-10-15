// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_002589D0(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    temp_v1 = M2C_FIELD(arg0, void **, 4);
    if (M2C_FIELD(temp_v1, s32 *, 0xA4) != 0) {
        temp_v0 = M2C_FIELD(temp_v1, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK (**)(void *, M2C_UNK), 0x84)(temp_v1 + M2C_FIELD(temp_v0, s16 *, 0x80), -1);
    }
}
