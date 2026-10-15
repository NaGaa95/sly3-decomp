// Drain the original record stack, releasing both resources on every entry.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001D2ED0(void *, M2C_UNK);             /* extern */
M2C_UNK func_00261050(s32, M2C_UNK);                /* extern */
M2C_UNK func_00261070(s32, M2C_UNK);                /* extern */

void func_001D2C90(void *arg0) {
    s32 temp_16;
    s32 temp_2;
    s32 var_3;

    var_3 = M2C_FIELD(arg0, s32 *, 0x38);
    if (var_3 > 0) {
        do {
            temp_16 = M2C_FIELD(((var_3 * 0x1C) + arg0), s32 *, 0x28);
            func_00261050(temp_16, 1);
            func_00261070(temp_16, 1);
            temp_2 = M2C_FIELD(arg0, s32 *, 0x38) - 1;
            M2C_FIELD(arg0, s32 *, 0x38) = temp_2;
            var_3 = temp_2;
        } while (temp_2 > 0);
    }
    func_001D2ED0(arg0, 0);
}
