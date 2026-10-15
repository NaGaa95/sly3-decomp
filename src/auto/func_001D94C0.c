// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_001D7F90(s32);                             /* extern */
M2C_UNK func_001D9500(void *, M2C_UNK);             /* extern */
M2C_UNK func_002389A0();                            /* extern */

void func_001D94C0(void *arg0) {
    func_002389A0();
    if (func_001D7F90(M2C_FIELD(arg0, s32 *, 0x18)) != 0) {
        func_001D9500(arg0, 0);
    }
}
