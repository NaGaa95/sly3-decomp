// Append an eligible request to the bounded 32-entry queue and process its record.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00170410(void *, void *, M2C_UNK);     /* extern */
s32 func_00170528(void *, s32);                                /* extern */

void func_00170118(void *arg0, s32 arg1, s32 arg2) {
    u32 temp_4;
    void *temp_2;

    if ((arg1 != 0) && (arg1 != M2C_FIELD(arg0, s32 *, 0xD0)) && (func_00170528(arg0, arg1) == 0)) {
        temp_4 = M2C_FIELD(arg0, u32 *, 0xD8);
        if (temp_4 < 0x20U) {
            M2C_FIELD(arg0, u32 *, 0xD8) = (u32) (temp_4 + 1);
            temp_2 = arg0 + ((temp_4 * 0x14) + 0xDC);
            M2C_FIELD(temp_2, s32 *, 0) = arg1;
            M2C_FIELD(temp_2, s32 *, 4) = arg2;
            func_00170410(arg0, temp_2, 0);
        }
    }
}
