// Apply a changed selection or forced refresh, then perform the requested notifications.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0023DD40(void *);                      /* extern */
s32 func_0024DB68(void *);                                /* extern */
M2C_UNK func_0024DCE0(void *);                      /* extern */
M2C_UNK func_0024DFC8(void *, M2C_UNK);             /* extern */

void func_0024DF48(void *arg0, s32 arg1, s32 arg2) {
    if ((M2C_FIELD(arg0, s32 *, 0x28C) != arg1) || ((arg2 != 0) && (func_0024DB68(arg0) != 0))) {
        M2C_FIELD(arg0, s32 *, 0x28C) = arg1;
        func_0024DCE0(arg0);
        if (arg2 != 0) {
            func_0024DFC8(arg0, 1);
            func_0023DD40(arg0);
        }
    }
}
