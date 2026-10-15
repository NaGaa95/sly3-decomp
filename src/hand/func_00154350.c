// Change the record mode and timestamp, dispatching its virtual transition or release.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00154330(s32);                             /* extern */
M2C_UNK func_00172BA8(s32, s32);                    /* extern */
s32 func_00173560(s32);                             /* extern */
extern f32 D_0036BB98;

void func_00154350(void *arg0, void *arg1, s32 arg2) {
    s32 temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_2_4;

    temp_2 = M2C_FIELD(arg1, s32 *, 4);
    if (temp_2 != arg2) {
        if (temp_2 == 1) {
            temp_2_2 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_2, M2C_UNK (**)(void *, s32), 0x3A4)(arg0 + M2C_FIELD(temp_2_2, s16 *, 0x3A0), M2C_FIELD(arg1, s32 *, 0));
        }
        M2C_FIELD(arg1, s32 *, 4) = arg2;
        M2C_FIELD(arg1, f32 *, 8) = (f32) D_0036BB98;
        switch (arg2) {                             /* irregular */
        case 2:
            temp_2_3 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_3, M2C_UNK (**)(void *, s32), 0x394)(arg0 + M2C_FIELD(temp_2_3, s16 *, 0x390), M2C_FIELD(arg1, s32 *, 0));
            M2C_FIELD(arg1, s32 *, 4) = 0;
            return;
        case 1:
            temp_2_4 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_4, M2C_UNK (**)(void *, s32), 0x394)(arg0 + M2C_FIELD(temp_2_4, s16 *, 0x390), M2C_FIELD(arg1, s32 *, 0));
            return;
        case -1:
            if (func_00154330(M2C_FIELD(arg1, s32 *, 0)) != 0) {
                func_00172BA8(M2C_FIELD(arg0, s32 *, 0x1108), func_00173560(M2C_FIELD(arg1, s32 *, 0)));
            }
            break;
        }
    }
}
