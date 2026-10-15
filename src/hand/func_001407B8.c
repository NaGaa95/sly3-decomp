// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_001407B8(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, s32 *, 0x11BC) >= 3)) {
        return M2C_FIELD(temp_v1, s32 *, 0x11B4);
    }
    return 0;
}
