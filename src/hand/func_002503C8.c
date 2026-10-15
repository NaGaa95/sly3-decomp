// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern f32 D_0036BB98;

s32 func_002503C8(void *arg0, f32 fparg0) {
    s32 var_v0;
    void *temp_v0;

    var_v0 = 0;
    if (fparg0 < (D_0036BB98 - M2C_FIELD(arg0, f32 *, 0x21C))) {
        temp_v0 = M2C_FIELD(arg0, void **, 0xC);
        var_v0 = M2C_FIELD(temp_v0, s32 (**)(void *), 0x214)(arg0 + M2C_FIELD(temp_v0, s16 *, 0x210)) == 0;
    }
    return var_v0;
}
