// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
void func_00163F28(void **arg0) {
    void *var_a0;

    var_a0 = *arg0;
    if (var_a0 != NULL) {
        do {
            M2C_FIELD(var_a0, s32 *, 0x10) = 0;
            var_a0 = M2C_FIELD(var_a0, void **, 0x18);
        } while (var_a0 != NULL);
    }
}
