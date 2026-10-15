// Handle modes 1 and 3 by finding and updating the eligible object record.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0013B500(s32, M2C_UNK);                    /* extern */
M2C_UNK func_0013BEC0(void);                            /* extern */
s32 func_001990D0(s32, s32);                        /* extern */
M2C_UNK func_00199118(s32, s32, M2C_UNK, M2C_UNK);  /* extern */

void func_00199F80(s32 arg0, s32 arg1, s32 arg2) {
    func_0013BEC0();
    if ((arg1 == 1) || (arg1 == 3)) {
        if (func_0013B500(arg2, 0x3A) != 0) {
            func_00199118(arg0, func_001990D0(arg0, arg2), 2, 0);
        }
    }
}
