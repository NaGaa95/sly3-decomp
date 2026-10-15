// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s128 func_0028B388(s32, s32);                       /* extern */

void func_0012F320(void *arg0, s128 *arg1, void *arg2) {
    s32 temp_a0;

    if (arg1 != NULL) {
        temp_a0 = M2C_FIELD(arg0, s32 *, 8);
        *arg1 = func_0028B388(temp_a0, temp_a0);
    }
    if (arg2 != NULL) {
        M2C_FIELD(arg2, s32 *, 8) = 0;
        M2C_FIELD(arg2, s32 *, 4) = 0;
        M2C_FIELD(arg2, s32 *, 0) = 0;
    }
}
