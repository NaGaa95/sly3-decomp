#include "actor_resource_lookup_api.h"
// Acquire and configure the replacement resource when its identifier changes.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
s32 func_0014DBA0(s32);
/* extern */ M2C_UNK func_0014DBB8(void *, s32);
/* extern */ M2C_UNK func_0014DC98(void *, M2C_UNK);
/* extern */ M2C_UNK func_00155ED8(void *, M2C_UNK);
/* extern */ extern s32 D_0047A2CC;
void func_00155E30(void *arg0, s32 arg1) {
    s32 temp_4;
    void *temp_2;
    temp_4 = M2C_FIELD(arg0, s32 *, 0x127C);
    if ((temp_4 == 0) || (func_0014DBA0(temp_4) != arg1)) {
        func_00155ED8(arg0, 5);
        if (arg1 != -1) {
            if (D_0047A2CC != 0) {
                temp_2 = func_001FBE30((void *)D_0047A2CC, 1);
                func_0014DBB8(temp_2, arg1);
                M2C_FIELD(temp_2, void **, 0x140) = arg0;
                func_0014DC98(temp_2, 6);
                func_0014DC98(temp_2, 4);
            }
        }
    }
}
