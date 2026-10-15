// Append a cleared 160-byte record when both source validations succeed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_002577A0(s32, void *);                     /* extern */
M2C_UNK func_00257B80(void *);                      /* extern */
M2C_UNK func_00292034(void *, M2C_UNK, M2C_UNK);    /* extern */

void func_002578D8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 temp_3;
    void *temp_16;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x11E8);
    if (temp_3 < 8U) {
        temp_16 = arg0 + ((temp_3 * 0xA0) + 0x11EC);
        func_00292034(temp_16, 0, 0xA0);
        M2C_FIELD(temp_16, s32 *, 0) = arg1;
        M2C_FIELD(temp_16, s32 *, 4) = arg4;
        if ((func_002577A0(arg2, temp_16 + 8) != 0) && (func_002577A0(arg3, temp_16 + 0x10) != 0)) {
            func_00257B80(temp_16);
            M2C_FIELD(arg0, u32 *, 0x11E8) = (u32) (M2C_FIELD(arg0, u32 *, 0x11E8) + 1);
        }
    }
}
