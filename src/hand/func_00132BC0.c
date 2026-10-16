// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"

M2C_UNK func_00132C58(void *, M2C_UNK);
void *func_001FE728(void *receiver,int flags);

void func_00132BC0(void *arg0) {
    s32 temp_3;
    s32 temp_5;
    void *temp_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xCC);
    if (temp_3 >= 3) {
        if (temp_3 >= 7) {
            if (temp_3 < 0xA) {
                if (temp_3 >= 8) {
                    goto block_4;
                }
                goto block_6;
            }
            goto block_5;
        }
block_4:
        func_00132C58(arg0, 4);
    } else {
block_5:
block_6:
        func_00132C58(arg0, 3);
    }
    temp_4 = M2C_FIELD(arg0, void **, 0x10);
    temp_5 = M2C_FIELD(temp_4, s32 *, 0x17C0);
    if (temp_5 != 0) {
        if (M2C_FIELD(temp_4, s32 *, 0x10F0) == -1) {
            func_001FE728((void *)temp_5, 1);
        }
    }
}
