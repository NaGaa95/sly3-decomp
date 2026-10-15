// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_00290F00(s32);                         /* extern */

void func_002489E0(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x104) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x104) = arg1;
        func_00290F00(arg1);
    }
}
