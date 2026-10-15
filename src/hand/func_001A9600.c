// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Receiver retained from original calls (common manager at 0x00475480).
// Only the second argument selects which global counter groups contribute.
#include "m2c_prelude.h"

extern s32 D_0036F8D0;
extern s32 D_00370A90;

s32 func_001A9600(void *receiver, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg1 != 1) {
        var_v1 = D_0036F8D0;
    }
    if (arg1 != 0) {
        var_v1 += D_00370A90;
    }
    return var_v1 > 0;
}
