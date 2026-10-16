// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"

s32 func_001852E0(void *context);                   /* context unused by the original getter */
M2C_UNK func_00185328(M2C_UNK *, s32);
M2C_UNK func_00189078(s32, M2C_UNK, void *);
M2C_UNK func_001F7588(void *);
void *func_001FE728(void *receiver,int flags);
M2C_UNK func_00244F08(s32, M2C_UNK);
s32 func_002459F8(M2C_UNK);
extern M2C_UNK D_0036C700;

void func_001F8020(void *arg0, s32 arg1) {
    s32 temp_18;
    s32 temp_4;
    s32 temp_4_2;
    void *temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_3;

    if (M2C_FIELD(arg0, s32 *, 0x130) != arg1) {
        if (arg1 == 1) {
            temp_3 = M2C_FIELD(arg0, void **, 0x16C);
            if (temp_3 != NULL) {
                temp_2 = M2C_FIELD(temp_3, void **, 0xC);
                M2C_FIELD(temp_2, M2C_UNK (**)(void *, void *), 0x2C4)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x2C0), arg0);
            }
            func_00244F08(func_002459F8(0), 0);
            temp_4 = M2C_FIELD(arg0, s32 *, 0x1A0);
            if (temp_4 != 0) {
                func_00189078(temp_4, 2, arg0);
            }
            temp_18 = M2C_FIELD(arg0, s32 *, 0x1A4);
            if (temp_18 != 0) {
                func_00185328(&D_0036C700, func_001852E0(&D_0036C700) + temp_18);
            }
            temp_4_2 = M2C_FIELD(arg0, s32 *, 0x194);
            if (temp_4_2 != 0) {
                func_001FE728((void *)temp_4_2, 1);
            }
            temp_2_2 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_2, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(arg0 + M2C_FIELD(temp_2_2, s16 *, 0x18), 5, 0, 0, 0, 0);
            temp_2_3 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_3, M2C_UNK (**)(void *, M2C_UNK), 0x284)(arg0 + M2C_FIELD(temp_2_3, s16 *, 0x280), -1);
            return;
        }
        func_001F7588(arg0);
    }
}
