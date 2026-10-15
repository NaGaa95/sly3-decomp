// Preserve the supplied value or convert it for the original matching owner/type case.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0013B500(void *, M2C_UNK);                 /* extern */
s32 func_0013CD00(s32, M2C_UNK);                    /* extern */

s32 func_00272FB0(void *arg0, void *arg1, s32 arg2) {
    s32 temp_4;

    if (arg1 == M2C_FIELD(arg0, s32 *, 0x10)) {
        temp_4 = M2C_FIELD(arg0, s32 *, 4);
        if (temp_4 != -1) {
            if (temp_4 < 3) {
                if (func_0013B500(arg1, 0x33) != 0) {
                    if (M2C_FIELD(arg1, s32 *, 0x33C) == 0x13) {
                        goto block_5;
                    }
                    /* Duplicate return node #7. Try simplifying control flow for better match */
                    return arg2;
                }
                goto block_6;
            }
block_5:
            return func_0013CD00(arg2, 3);
        }
    }
block_6:
    return arg2;
}
