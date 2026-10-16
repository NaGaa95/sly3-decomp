// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"

s32 func_0013B500(void *, M2C_UNK);
M2C_UNK func_00168568(M2C_UNK *);
M2C_UNK func_001856E0(M2C_UNK *, s32, s32);
M2C_UNK func_001B67C0(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK);
void func_001F49C8(void *, s32);
s32 func_0025AE28(M2C_UNK *);
extern M2C_UNK D_0036C700;
extern M2C_UNK D_00475480;

void func_001F4B38(void *arg0, void *arg1) {
    void *temp_2;
    void *temp_2_2;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x110C);
    if (temp_3 != arg1) {
        if (temp_3 != NULL) {
            temp_2 = M2C_FIELD(temp_3, void **, 0xC);
            M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK), 0x29C)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x298), -1);
        }
        if (arg1 != NULL) {
            temp_2_2 = M2C_FIELD(arg1, void **, 0xC);
            M2C_FIELD(temp_2_2, M2C_UNK (**)(void *, s32), 0x29C)(arg1 + M2C_FIELD(temp_2_2, s16 *, 0x298), M2C_FIELD(arg0, s32 *, 0x1040));
        }
        func_00168568(&D_00475480);
        if ((arg1 != NULL) && (func_0013B500(arg1, 0x33) != 0) && (M2C_FIELD(arg0, s32 *, 0x1040) != -1) && (func_0025AE28(&D_00475480) == 0)) {
            func_001856E0(&D_0036C700, M2C_FIELD(arg0, s32 *, 0x1040), M2C_FIELD(arg1, s32 *, 0x18));
        }
        func_001B67C0(&D_00475480, 0, 0, 0);
        func_001F49C8(&D_00475480, M2C_FIELD(arg0, s32 *, 0x1040));
    }
}
