// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_0028F260(s32, s32);                    /* extern */

s32 func_002424C8(void *arg0, s32 arg1) {
    if (arg1 == 1) {
        func_0028F260(M2C_FIELD(arg0, s32 *, 0x20), M2C_FIELD(arg0, s32 *, 0x24));
    }
    return M2C_FIELD(arg0, s32 *, 0x24);
}
