// Initialize the object limits, modes, and sentinel, then activate its tagged flag word.
// Bit zero distinguishes an immediate flag word from a pointer to flag storage.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001C7340(void *);                            /* extern */

void func_00278A48(void *arg0) {
    s32 temp_6;

    func_001C7340(arg0);
    temp_6 = M2C_FIELD(arg0, s32 *, 0x3C);
    M2C_FIELD(arg0, f32 *, 0x4C) = 5000.0f;
    M2C_FIELD(arg0, f32 *, 0x268) = 500.0f;
    M2C_FIELD(arg0, s32 *, 0x290) = 0x36;
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    M2C_FIELD(arg0, s32 *, 0x284) = 8;
    if ((temp_6 ^ 1) & 1) {
        M2C_FIELD(temp_6, s32 *, 0) = (s32) (M2C_FIELD(temp_6, s32 *, 0) | 2);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_6 | 2);
}
