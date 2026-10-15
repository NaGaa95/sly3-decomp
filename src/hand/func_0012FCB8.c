// SLY3_ASFIX: engine-local-jumps
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_0012FCB8(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, void **, 0x1C) = temp_v1;
    if (temp_v1 != NULL) {
        temp_v0 = M2C_FIELD(temp_v1, void **, 0x18);
        M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0xC)(temp_v1 + M2C_FIELD(temp_v0, s16 *, 8));
    }
}
