// Handle the matching message locally, forwarding all other messages to the base handler.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00238AD8(void *, s32, void *);             /* extern */
s32 func_00257CF0(s32);                             /* extern */

s32 func_001A4F08(void *arg0, s32 arg1, void *arg2) {
    if (arg1 == 0xC) {
        if ((M2C_FIELD(arg2, s32 *, 0) == M2C_FIELD(arg0, s32 *, 0x30)) && (func_00257CF0(M2C_FIELD(arg2, s32 *, 4)) == M2C_FIELD(arg0, s32 *, 0x10))) {
            M2C_FIELD(arg0, s32 *, 0x40) = 1;
            return 1;
        }
        goto block_5;
    }
block_5:
    return func_00238AD8(arg0, arg1, arg2);
}
