// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_001D2100(void *arg0) {
    void *temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x34);
    if (temp_v1 != NULL) {
        temp_v0 = M2C_FIELD(temp_v1, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0x1B4)(temp_v1 + M2C_FIELD(temp_v0, s16 *, 0x1B0));
    }
}
