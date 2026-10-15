// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_002BC760(void **arg0, void *arg1) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    if (arg1 != NULL) {
        temp_v0 = M2C_FIELD(arg1, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0xC)(arg1 + M2C_FIELD(temp_v0, s16 *, 8));
    }
    temp_v1 = *arg0;
    if (temp_v1 != NULL) {
        temp_v0_2 = M2C_FIELD(temp_v1, void **, 0xC);
        M2C_FIELD(temp_v0_2, M2C_UNK (**)(void *), 0x14)(temp_v1 + M2C_FIELD(temp_v0_2, s16 *, 0x10));
    }
    *arg0 = arg1;
}
