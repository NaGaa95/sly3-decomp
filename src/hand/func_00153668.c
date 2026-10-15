// Select the original event-handling fallback after state and global eligibility checks.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_001C3EC8(void *, s32);                     /* extern */
s32 func_001F42E8(void *, s32);                     /* extern */
s32 func_001F4350(void *, s32);                    /* extern */
extern void *D_00468D08;

s32 func_00153668(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0xF78) != 1) {
        if (M2C_FIELD(arg0, s32 *, 0x33C) != 0x16) {
            if (((D_00468D08 == 0) || (func_001F4350(D_00468D08, -1) == 0)) && (func_001C3EC8(arg0 + 0xE40, arg1) == 0)) {
                return func_001F42E8(arg0, arg1);
            }
            /* Duplicate return node #7. Try simplifying control flow for better match */
            return 1;
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return 1;
    }
    return 1;
}
