// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_001D2898(s32, s32, M2C_UNK);         /* extern */

void func_0012D2B0(s32 arg0, s32 arg1, void *arg2) {
    if (arg1 != 0) {
        func_001D2898(arg1, arg0 + 4, 0xC);
    }
    if (arg2 != NULL) {
        M2C_FIELD(arg2, s32 *, 8) = 0;
        M2C_FIELD(arg2, s32 *, 4) = 0;
        M2C_FIELD(arg2, s32 *, 0) = 0;
    }
}
