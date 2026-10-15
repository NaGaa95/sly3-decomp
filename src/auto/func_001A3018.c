// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_00296F38(s32, s32, s32);                         /* extern */

void func_001A3018(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x38);
    M2C_FIELD(arg0, s32 *, 0x10) = temp_v0;
    M2C_FIELD(arg0, s32 *, 0x14) = func_00296F38(M2C_FIELD(arg0, s32 *, 0x3C), temp_v0, M2C_FIELD(arg0, s32 *, 0x34));
}
