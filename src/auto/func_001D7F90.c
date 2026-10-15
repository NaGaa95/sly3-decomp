// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_001D8AC0(s32);                             /* extern */

s32 func_001D7F90(void *arg0) {
    s32 temp_s0;
    s32 var_v1;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x30);
    var_v1 = 0;
    if (temp_s0 == 1) {
        var_v1 = (func_001D8AC0(M2C_FIELD(arg0, s32 *, 0x18)) != 0) ? temp_s0 : 0;
    }
    return var_v1;
}
