// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_0028EE98(s32, s32);                    /* extern */

void func_00138BA8(void *arg0, s32 arg1) {
    void *var_s0;

    var_s0 = M2C_FIELD(arg0, void **, 0x34);
    if (var_s0 != NULL) {
        do {
            M2C_FIELD(var_s0, s32 *, 0xC) = arg1;
            func_0028EE98(M2C_FIELD(var_s0, s32 *, 4), M2C_FIELD(var_s0, s32 *, 8));
            var_s0 = M2C_FIELD(var_s0, void **, 0x28);
        } while (var_s0 != NULL);
    }
}
