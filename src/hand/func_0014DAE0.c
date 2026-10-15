// Append an initialized record to the bounded 32-entry queue.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0014DB68(void *);                            /* extern */

void func_0014DAE0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_3;
    void *temp_2;

    func_0014DB68(arg0);
    temp_3 = M2C_FIELD(arg0, s32 *, 0x130);
    if (temp_3 < 0x20) {
        M2C_FIELD(arg0, s32 *, 0x130) = (s32) (temp_3 + 1);
        temp_2 = M2C_FIELD(arg0, s32 *, 0x134) + (temp_3 * 0x2C);
        M2C_FIELD(arg0, void **, 0x138) = temp_2;
        M2C_FIELD(temp_2, s32 *, 0) = arg1;
        M2C_FIELD(temp_2, s32 *, 4) = arg2;
        M2C_FIELD(temp_2, s32 *, 0x14) = arg3;
        M2C_FIELD(temp_2, s32 *, 0x18) = -1;
        M2C_FIELD(temp_2, s32 *, 0x1C) = 0;
    }
}
