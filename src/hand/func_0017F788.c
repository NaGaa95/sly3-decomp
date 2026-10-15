// Handle the matching event by clearing its mode and updating the source transform.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00156DC0(void *, s128, M2C_UNK);       /* extern */
M2C_UNK func_0017EAD0(void *, s32);                     /* extern */

void func_0017F788(void *arg0, s32 arg1, void *arg2) {
    void *temp_2;
    void *temp_3;

    if ((arg1 == 0xA) && (M2C_FIELD(arg2, s32 *, 0) == M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x113C)) && (M2C_FIELD(arg2, s32 *, 8) == 0x185) && (M2C_FIELD(arg0, s32 *, 0xC) == 3) && (M2C_FIELD(arg0, s32 *, 0x14) == 2)) {
        func_0017EAD0(arg0, 0);
        temp_3 = M2C_FIELD(arg0, void **, 0);
        temp_2 = M2C_FIELD(temp_3, void **, 0xC);
        func_00156DC0(M2C_FIELD(arg0, void **, 0), M2C_FIELD(M2C_FIELD(temp_2, void *(**)(void *), 0x124)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x120)), s128 *, 0x30), 1);
    }
}
