// Reset the existing resource and compute the original sentinel-based duration.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001C7DC8(void *);                            /* extern */
f32 func_0022F998(void *);                          /* extern */
M2C_UNK func_00273E48(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_001A0A78(void *arg0) {
    s32 temp_4;
    s32 var_2;

    func_001C7DC8(arg0);
    temp_4 = M2C_FIELD(arg0, s32 *, 0x180);
    if (temp_4 != 0) {
        func_00273E48(temp_4, 0, 0, 0);
    }
    var_2 = 1;
    if (M2C_FIELD(arg0, f32 *, 0x1A8) != 1250.0f) {
        var_2 = 0;
    }
    if (var_2 != 0) {
        M2C_FIELD(arg0, f32 *, 0x1A8) = (f32) (func_0022F998(arg0) + 1250.0f);
    }
}
