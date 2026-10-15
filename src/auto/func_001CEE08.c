// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_00271B20(M2C_UNK, M2C_UNK);              /* extern */

void func_001CEE08(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_00271B20(1, 1);
    M2C_FIELD(arg0, s32 *, 0) = temp_v0;
    M2C_FIELD(arg0, s32 *, 4) = -1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0x20;
}
