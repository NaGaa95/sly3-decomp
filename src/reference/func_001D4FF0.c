// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_001D3818(M2C_UNK *, s32, s32);         /* extern */
extern M2C_UNK D_0046F550;

void func_001D4FF0(void *arg0) {
    func_001D3818(&D_0046F550, M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0xC));
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 2);
    }
}
