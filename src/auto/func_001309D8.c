// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_0012F410(s32);                         /* extern */
M2C_UNK func_001306C8(s32);                         /* extern */

void func_001309D8(s32 *arg0) {
    s32 temp_s0;

    temp_s0 = *arg0;
    if (temp_s0 != 0) {
        func_0012F410(temp_s0);
        func_001306C8(temp_s0);
        *arg0 = 0;
    }
}
