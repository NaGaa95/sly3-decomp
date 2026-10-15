// Acquire the first descriptor resource and bind its second record when the identifiers are valid.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
void *func_0017E1B8(M2C_UNK *, M2C_UNK, s32, void *);
/* extern */ void func_0023B978(void *, void *);
/* extern */ void *func_0023F3B8(void *, s32);
/* extern */ extern M2C_UNK D_00475480;
void func_001C2138(void *arg0, void *arg1) {
    void *temp_2_3;
    s32 temp_5;
    s32 temp_6;
    void *temp_2;
    void *temp_2_2;
    temp_6 = M2C_FIELD(arg1, s32 *, 0);
    if (temp_6 != -1) {
        temp_2 = func_0017E1B8(&D_00475480, 1, temp_6, M2C_FIELD(arg0, void **, 0));
        M2C_FIELD(arg1, void **, 4) = temp_2;
        if (temp_2 != NULL) {
            temp_2_2 = M2C_FIELD(temp_2, void **, 0xC);
            M2C_FIELD(temp_2_2, M2C_UNK (**)(void *), 0x4C)(temp_2 + M2C_FIELD(temp_2_2, s16 *, 0x48));
        }
    }
    temp_5 = M2C_FIELD(arg1, s32 *, 8);
    if (temp_5 != -1) {
        temp_2_3 = func_0023F3B8(M2C_FIELD(arg0, void **, 0), temp_5);
        M2C_FIELD(arg1, void **, 0xC) = temp_2_3;
        if (temp_2_3 != 0) {
            func_0023B978(M2C_FIELD(arg0, void **, 0), temp_2_3);
        }
    }
}
