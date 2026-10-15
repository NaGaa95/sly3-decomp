// Clear three resource handles and invoke the complete eight-argument update.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00147E08(s32, M2C_UNK, M2C_UNK, void *, M2C_UNK, M2C_UNK, M2C_UNK, void *); /* extern */
M2C_UNK func_00273E48(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_001B71D8(void *arg0) {
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x134);
    if (temp_4 != 0) {
        func_00273E48(temp_4, 0, 0, 0);
    }
    temp_4_2 = M2C_FIELD(arg0, s32 *, 0x138);
    if (temp_4_2 != 0) {
        func_00273E48(temp_4_2, 0, 0, 0);
    }
    temp_4_3 = M2C_FIELD(arg0, s32 *, 0x184);
    if (temp_4_3 != 0) {
        func_00273E48(temp_4_3, 0, 0, 0);
    }
    func_00147E08(M2C_FIELD(arg0, s32 *, 0), 0xC, 5, arg0 + 0x144, 0, 0, 0, arg0 + 0x180);
}
