// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"

void *func_001FE728(void *receiver,int flags);
extern s32 D_00348018[];
extern void *D_0038AE90;

void func_0020F508(void *arg0) {
    s32 temp_18;
    s32 temp_19;
    void *temp_2;
    void *temp_3;
    void *temp_3_2;
    void *var_16;

    var_16 = M2C_FIELD(arg0, void **, 0x200);
    if (var_16 == NULL) {
        temp_2 = M2C_FIELD(arg0, void **, 0x1F4);
        if (temp_2 != NULL) {
            var_16 = M2C_FIELD(temp_2, void **, 0x150);
        }
        if (var_16 != NULL) {
            goto block_4;
        }
    } else {
block_4:
        temp_19 = M2C_FIELD(var_16, s32 *, 0xE0);
        temp_18 = D_00348018[M2C_FIELD(D_0038AE90, s32 *, 0x1C64)];
        M2C_FIELD(var_16, s32 *, 0xE0) = 0;
        if (temp_18 & 1) {
            temp_3 = M2C_FIELD(var_16, void **, 0xC);
            M2C_FIELD(temp_3, M2C_UNK (**)(void *, s128), 0x114)(var_16 + M2C_FIELD(temp_3, s16 *, 0x110), M2C_FIELD(M2C_FIELD(arg0, void **, 0x1F8), s128 *, 0x70));
            func_001FE728(var_16, 1);
        }
        if (temp_18 & 2) {
            temp_3_2 = M2C_FIELD(var_16, void **, 0xC);
            M2C_FIELD(temp_3_2, M2C_UNK (**)(void *, s128), 0x114)(var_16 + M2C_FIELD(temp_3_2, s16 *, 0x110), M2C_FIELD(M2C_FIELD(arg0, void **, 0x1FC), s128 *, 0x70));
            func_001FE728(var_16, 1);
        }
        M2C_FIELD(var_16, s32 *, 0xE0) = temp_19;
    }
}
