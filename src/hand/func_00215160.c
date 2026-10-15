// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_00215160(void *arg0, s32 arg1) {
    s32 *temp_v1;
    s32 temp_a2;

    temp_a2 = M2C_FIELD(arg0, s32 *, 0x1D8);
    if (temp_a2 < 4) {
        M2C_FIELD(arg0, s32 *, 0x1D8) = (s32) (temp_a2 + 1);
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x1D4) + (temp_a2 * 0x2C);
        M2C_FIELD(arg0, s32 **, 0x1DC) = temp_v1;
        *temp_v1 = arg1;
    }
}
