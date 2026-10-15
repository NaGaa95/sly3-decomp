// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_00146E70(void *arg0, s32 arg1, s32 arg2) {
    u32 temp_a3;
    void *temp_v0;

    temp_a3 = M2C_FIELD(arg0, u32 *, 0x274);
    if (temp_a3 < 4U) {
        M2C_FIELD(arg0, u32 *, 0x274) = (u32) (temp_a3 + 1);
        temp_v0 = arg0 + ((temp_a3 * 0xC) + 0x244);
        M2C_FIELD(temp_v0, s32 *, 0) = arg1;
        M2C_FIELD(temp_v0, s32 *, 4) = arg2;
        M2C_FIELD(temp_v0, s32 *, 8) = 0;
    }
}
