// Initialize the selected display resource and dispatch its original mode transition.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0015FD58(void *, M2C_UNK);             /* extern */
M2C_UNK func_00160960(void *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_00161B70(s32);                         /* extern */
M2C_UNK func_00238978(void);                            /* extern */
M2C_UNK func_00259D10(s32);                         /* extern */
extern s32 D_0036DBE0;

void func_0015F7F0(void *arg0) {
    s32 temp_3;

    func_00238978();
    func_00161B70(M2C_FIELD(arg0, s32 *, 0x10));
    func_00259D10(M2C_FIELD(arg0, s32 *, 0x10) + 0x4B0);
    if ((D_0036DBE0 ^ 2) == 0) {
        func_0015FD58(arg0, 0);
    } else {
        func_0015FD58(arg0, 1);
    }
    temp_3 = M2C_FIELD(arg0, s32 *, 0x40);
    switch (temp_3) {                               /* irregular */
    case 0:
        func_00160960(arg0, 2, 0);
        return;
    case 1:
        func_00160960(arg0, 0, 0);
        return;
    }
}
