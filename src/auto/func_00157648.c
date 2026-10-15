// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_00157950(s32);                             /* extern */
M2C_UNK func_00157688(void *, M2C_UNK);             /* extern */
M2C_UNK func_002389A0();                            /* extern */

void func_00157648(void *arg0) {
    func_002389A0();
    if (func_00157950(M2C_FIELD(arg0, s32 *, 0x18)) != 0) {
        func_00157688(arg0, 0);
    }
}
