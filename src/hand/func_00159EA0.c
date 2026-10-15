// Apply the mode-specific resource transition after availability checks.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00137688(void *);                      /* extern */
s32 func_00138AC8(s32);                             /* extern */
M2C_UNK func_0015A038(void *, M2C_UNK);             /* extern */
s32 func_00248858(M2C_UNK *, s32);                  /* extern */
extern M2C_UNK D_00474FF0;

void func_00159EA0(void *arg0) {
    s32 temp_3;
    s32 temp_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x130);
    switch (temp_3) {                               /* irregular */
    case 0:
        func_0015A038(arg0, 1);
        return;
    case 3:
        if (func_00248858(&D_00474FF0, M2C_FIELD(arg0, s32 *, 0x150)) == 0) {
            func_0015A038(arg0, 2);
            return;
        }
        return;
    case 2:
        temp_4 = M2C_FIELD(arg0, s32 *, 0x140);
        if ((temp_4 == 0) || (func_00138AC8(temp_4) != 0)) {
            func_00137688(arg0 + 0x140);
            func_0015A038(arg0, -1);
        }
        break;
    }
}
