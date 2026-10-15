// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_001CEFB8();              /* extern */
M2C_UNK func_002936C0(s32);                            /* extern */
M2C_UNK func_002936E0(s32);                              /* extern */
M2C_UNK func_00293530(s32, M2C_UNK);                /* extern */

void func_001CEF70(void *arg0) {
    if (func_001CEFB8() != 0) {
        func_00293530(M2C_FIELD(arg0, s32 *, 4), 1);
    }
    func_002936E0(M2C_FIELD(arg0, s32 *, 0));
    func_002936C0(M2C_FIELD(arg0, s32 *, 0));
}
