// Dispatch a pair update only when both eligible objects hold active records.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0013B500(u32, M2C_UNK);                    /* extern */
M2C_UNK func_00214DA8(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_0023EDD8(void);                            /* extern */

void func_00214F88(void *arg0, u32 arg1, s32 arg2) {
    s32 temp_7;

    func_0023EDD8();
    if ((M2C_FIELD(arg0, s32 *, 0x564) != 0) && ((u32) arg0 < arg1) && (func_0013B500(arg1, 0x58) != 0)) {
        temp_7 = M2C_FIELD(arg1, s32 *, 0x564);
        if (temp_7 != 0) {
            func_00214DA8(M2C_FIELD(arg0, s32 *, 0x560), M2C_FIELD(arg0, s32 *, 0x564), M2C_FIELD(arg1, s32 *, 0x560), temp_7, arg2);
        }
    }
}
