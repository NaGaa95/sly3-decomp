// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"
void func_00131598(void *);
 M2C_UNK func_00170360(s32);
 s32 func_002533C0(void *, M2C_UNK);
 M2C_UNK func_00256828(void *, M2C_UNK, M2C_UNK, s128);
 M2C_UNK func_0028F068(void *, void *, M2C_UNK);
 extern s128 D_00317560;
void func_00131BB0(void *arg0) {
    s32 temp_2;
    void *temp_4;
    void *temp_4_2;
    func_00131598(arg0);
    if (func_002533C0(M2C_FIELD(arg0, void **, 0x10), 1) != 0) {
        func_00256828(M2C_FIELD(arg0, void **, 0x10), 0, 0, D_00317560);
        func_00170360(M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x10D0));
        temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x1138);
        if (temp_2 != 0) {
            M2C_FIELD(arg0, s32 *, 0x38) = temp_2;
        }
    }
    temp_4 = M2C_FIELD(arg0, void **, 0x10);
    func_0028F068(temp_4, M2C_FIELD(temp_4, void **, 0x48), 1);
    if (M2C_FIELD(arg0, s32 *, 0x38) == 0) {
        temp_4_2 = M2C_FIELD(arg0, void **, 0x10);
        func_0028F068(temp_4_2, M2C_FIELD(temp_4_2, void **, 0x4C), 1);
    }
}
