// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s128 func_001A6CA8(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0x44);
    if ((M2C_FIELD(temp_a1, s32 *, 0x54) == 4) && (M2C_FIELD(temp_a1, s32 *, 0x44) == M2C_FIELD(arg0, s32 *, 0x10))) {
        return M2C_FIELD(temp_a1, s128 *, 0x20);
    }
    return M2C_FIELD(temp_a1, s128 *, 0x30);
}
