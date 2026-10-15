// Calculate a cyclic interval from two sampled times, wrapping through its duration.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

f32 func_001368E0(void *, s32);                     /* extern */

void func_002592A8(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    f32 temp_f20;
    f32 var_f1;

    temp_f20 = func_001368E0(arg1, arg2);
    var_f1 = func_001368E0(arg1, arg3);
    if (var_f1 < temp_f20) {
        var_f1 += M2C_FIELD(arg1, f32 *, 0x64);
    }
    M2C_FIELD(arg0, f32 *, 0) = temp_f20;
    M2C_FIELD(arg0, f32 *, 4) = (f32) (var_f1 - temp_f20);
}
