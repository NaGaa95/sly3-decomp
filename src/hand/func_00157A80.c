// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_00157A80(void *arg0, s32 arg1) {
    s32 temp_a1;
    void *temp_v0;

    temp_a1 = arg1 == 0;
    temp_v0 = M2C_FIELD(arg0, void **, 0x18);
    M2C_FIELD(arg0, s32 *, 0x50) = temp_a1;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0xA0) = temp_a1;
    }
}
