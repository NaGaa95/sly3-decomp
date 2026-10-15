// Retry the timed state transition until a callback leaves the state unchanged.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0019E8F0(s32, void *, M2C_UNK);        /* extern */
extern f32 D_0036BB98;

void func_0019E868(s32 arg0, void *arg1) {
    s32 temp_17;

    do {
        temp_17 = M2C_FIELD(arg1, s32 *, 0x24);
        if ((temp_17 == 1) && ((D_0036BB98 - M2C_FIELD(arg1, f32 *, 0x28)) > 0.15f)) {
            func_0019E8F0(arg0, arg1, 0);
        }
    } while (M2C_FIELD(arg1, s32 *, 0x24) != temp_17);
}
