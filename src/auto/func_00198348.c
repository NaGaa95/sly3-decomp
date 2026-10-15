// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_001977A0(s32, s32);                        /* extern */
M2C_UNK func_00238AE8(void *);                      /* extern */

void func_00198348(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x30) != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x40) != 0) {
            func_00238AE8(arg0 + 0x18);
            M2C_FIELD(arg0, s32 *, 0x40) = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x38) = func_001977A0(M2C_FIELD(arg0, s32 *, 0x30), arg1);
    }
}
