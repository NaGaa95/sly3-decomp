// Initialize the embedded list and clock sentinel, then replace the tagged activation flags.
// Bit zero distinguishes an immediate flag word from a pointer to flag storage.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011AF38(s32, M2C_UNK);                /* extern */
M2C_UNK func_001C9118(void *, M2C_UNK);             /* extern */
M2C_UNK func_0028FD70(void *);                            /* extern */

void func_00149718(void *arg0) {
    s32 temp_3;

    func_0028FD70(arg0);
    func_0011AF38(arg0 + 0x438, 0x1090);
    M2C_FIELD(arg0, s32 *, 0x18) = -1;
    M2C_FIELD(arg0, f32 *, 0x34) = 1e10f;
    func_001C9118(arg0, 1);
    temp_3 = M2C_FIELD(arg0, s32 *, 0x3C);
    if ((temp_3 ^ 1) & 1) {
        M2C_FIELD(temp_3, s32 *, 0) = (s32) ((M2C_FIELD(temp_3, s32 *, 0) & 1) | 0xE);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) ((temp_3 & 1) | 0xE);
}
