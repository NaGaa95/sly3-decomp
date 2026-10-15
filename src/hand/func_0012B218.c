// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void *func_0012B218(void *arg0, void *arg1) {
    void *temp_v0;

    if (arg1 != NULL) {
        temp_v0 = M2C_FIELD(arg1, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0xC)(arg1 + M2C_FIELD(temp_v0, s16 *, 8));
    }
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, s16 *, 0) = 0x1F;
    return arg0;
}
