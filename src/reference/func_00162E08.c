// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_002A10B0();                                /* extern */
extern s32 D_003440C4;

s32 func_00162E08(void) {
    s32 temp_v0;

    temp_v0 = func_002A10B0();
    if (D_003440C4 != temp_v0) {
        D_003440C4 = temp_v0;
    }
    return D_003440C4 == 0x14;
}
