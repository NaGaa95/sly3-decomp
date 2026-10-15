// Set the object mode, register both resources, and dispatch the complete virtual notification.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00185908(M2C_UNK *, s32, void *, void *); /* extern */
M2C_UNK func_00225EE8(s32, s32);                    /* extern */
M2C_UNK func_0025D3F8(M2C_UNK *, s32, void *, void *, M2C_UNK); /* extern */
extern M2C_UNK D_0036C700;
extern M2C_UNK D_00475480;

void func_001A20F8(void *arg0, s32 arg1) {
    s32 temp_4;
    void *temp_2;

    M2C_FIELD(arg0, s32 *, 0x11C) = arg1;
    func_0025D3F8(&D_00475480, M2C_FIELD(arg0, s32 *, 0x128), arg0 + 0x12C, arg0, 1);
    func_00185908(&D_0036C700, M2C_FIELD(arg0, s32 *, 0x16C), arg0 + 0x170, arg0);
    temp_2 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(arg0 + M2C_FIELD(temp_2, s16 *, 0x18), 5, 0, 0, 0, 0);
    temp_4 = M2C_FIELD(arg0, s32 *, 0x124);
    if (temp_4 != 0) {
        func_00225EE8(temp_4, arg1);
    }
}
