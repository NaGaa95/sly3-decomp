// Temporarily exit the selected mode and restore its two resource values when the resource remains valid.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0014DC98(void *, M2C_UNK);             /* extern */
s32 func_001C8658(s32);                             /* extern */

void func_0014DC08(void *arg0) {
    s32 temp_17;
    s32 temp_18;

    if (M2C_FIELD(arg0, s32 *, 0x164) == 5) {
        temp_17 = M2C_FIELD(arg0, s32 *, 0x13C);
        M2C_FIELD(arg0, s32 *, 0x13C) = 0;
        temp_18 = M2C_FIELD(arg0, s32 *, 0x138);
        func_0014DC98(arg0, 0);
        if ((temp_17 != 0) && (func_001C8658(temp_17) != 0)) {
            M2C_FIELD(arg0, s32 *, 0x13C) = temp_17;
            M2C_FIELD(arg0, s32 *, 0x138) = temp_18;
            func_0014DC98(arg0, 1);
        }
    }
}
