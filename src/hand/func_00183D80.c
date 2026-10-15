// Initialize the three distance limits and activate the tagged flag word.
// Bit zero distinguishes an immediate flag word from a pointer to flag storage.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001C7340(void *);                            /* extern */
M2C_UNK func_001C9118(void *, M2C_UNK);             /* extern */

void func_00183D80(void *arg0) {
    s32 temp_3;

    func_001C7340(arg0);
    M2C_FIELD(arg0, f32 *, 0x50) = 50.0f;
    M2C_FIELD(arg0, f32 *, 0x58) = 100.0f;
    M2C_FIELD(arg0, f32 *, 0x60) = 2000.0f;
    func_001C9118(arg0, 1);
    temp_3 = M2C_FIELD(arg0, s32 *, 0x3C);
    if ((temp_3 ^ 1) & 1) {
        M2C_FIELD(temp_3, s32 *, 0) = (s32) (M2C_FIELD(temp_3, s32 *, 0) | 0xA);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_3 | 0xA);
}
