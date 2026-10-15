// Resolve both handles in each inactive queue record and mark it initialized.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00146EE8(void *, s32, M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
extern M2C_UNK D_00320178;
extern M2C_UNK D_003201A0;

void func_00146F18(void *arg0) {
    s32 var_18;
    void *temp_16;

    var_18 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x274) > 0) {
        do {
            temp_16 = arg0 + ((var_18 * 0xC) + 0x244);
            if (M2C_FIELD(temp_16, s32 *, 8) == 0) {
                M2C_FIELD(temp_16, s32 *, 0) = func_00146EE8(arg0, M2C_FIELD(temp_16, s32 *, 0), 3, &D_00320178, 0);
                M2C_FIELD(temp_16, s32 *, 4) = func_00146EE8(arg0, M2C_FIELD(temp_16, s32 *, 4), 0x2D, &D_003201A0, 1);
                M2C_FIELD(temp_16, s32 *, 8) = 1;
            }
            var_18 += 1;
        } while (var_18 < M2C_FIELD(arg0, s32 *, 0x274));
    }
}
