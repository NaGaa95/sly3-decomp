// Resolve the pair of descriptor resources and clear its pending flag.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
void *func_0017E1B8(M2C_UNK *, M2C_UNK, s32, void *);
/* extern */ M2C_UNK func_001FF010(void *, s32);
/* extern */ extern M2C_UNK D_00475480;
void func_00202278(void *arg0, s32 arg1) {
    void *temp_16;
    s32 temp_6;
    s32 temp_6_2;
    void *temp_18;
    func_001FF010(arg0, arg1);
    temp_18 = M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x1C);
    if ((arg1 == 0) || (M2C_FIELD(temp_18, u16 *, 0x22) != 0)) {
        temp_6 = M2C_FIELD(temp_18, s32 *, 0xC);
        temp_16 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x10);
        if (temp_6 != -1) {
            M2C_FIELD(arg0, void **, 0x5C) = func_0017E1B8(&D_00475480, 4, temp_6, temp_16);
        }
        else {
            M2C_FIELD(arg0, void **, 0x5C) = 0;
        }
        temp_6_2 = M2C_FIELD(temp_18, s32 *, 0x10);
        if (temp_6_2 != -1) {
            M2C_FIELD(arg0, void **, 0x60) = func_0017E1B8(&D_00475480, 4, temp_6_2, temp_16);
        }
        else {
            M2C_FIELD(arg0, void **, 0x60) = 0;
        }
        M2C_FIELD(temp_18, u16 *, 0x22) = 0U;
    }
}
