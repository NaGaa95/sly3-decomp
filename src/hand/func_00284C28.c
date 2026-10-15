// Update the normalized progress and emit every original threshold-crossing event.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

f32 func_0011EE68(M2C_UNK *, f32);                  /* extern */
M2C_UNK func_001854C8(M2C_UNK *, M2C_UNK, void *);  /* extern */
s32 func_002852B0(void *);                                /* extern */
extern M2C_UNK D_00341FF0;
extern M2C_UNK D_0036C700;

void func_00284C28(void *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f20;
    void *temp_6;
    void *temp_6_2;
    void *temp_6_3;
    void *temp_6_4;

    if (func_002852B0(arg0) != 0) {
        temp_f20 = M2C_FIELD(arg0, f32 *, 0x1C);
        temp_f0 = func_0011EE68(&D_00341FF0, fparg0);
        M2C_FIELD(arg0, f32 *, 0x1C) = temp_f0;
        if ((temp_f20 > 0.0f) && (temp_f0 == 0.0f)) {
            func_001854C8(&D_0036C700, 0x2D, M2C_FIELD(arg0, void **, 0x14));
        }
        if ((temp_f20 < 1.0f) && (M2C_FIELD(arg0, f32 *, 0x1C) == 1.0f)) {
            func_001854C8(&D_0036C700, 0x2E, M2C_FIELD(arg0, void **, 0x14));
        }
        temp_6 = M2C_FIELD(arg0, void **, 0x14);
        temp_f1 = M2C_FIELD(temp_6, f32 *, 0x84);
        if ((temp_f1 <= temp_f20) && (M2C_FIELD(arg0, f32 *, 0x1C) < temp_f1)) {
            func_001854C8(&D_0036C700, 0x30, temp_6);
        }
        temp_6_2 = M2C_FIELD(arg0, void **, 0x14);
        temp_f1_2 = M2C_FIELD(temp_6_2, f32 *, 0x84);
        if ((temp_f20 < temp_f1_2) && (temp_f1_2 <= M2C_FIELD(arg0, f32 *, 0x1C))) {
            func_001854C8(&D_0036C700, 0x2F, temp_6_2);
        }
        temp_6_3 = M2C_FIELD(arg0, void **, 0x14);
        temp_f1_3 = M2C_FIELD(temp_6_3, f32 *, 0xA4);
        if ((temp_f1_3 <= temp_f20) && (M2C_FIELD(arg0, f32 *, 0x1C) < temp_f1_3)) {
            func_001854C8(&D_0036C700, 0x32, temp_6_3);
        }
        temp_6_4 = M2C_FIELD(arg0, void **, 0x14);
        temp_f1_4 = M2C_FIELD(temp_6_4, f32 *, 0xA4);
        if ((temp_f20 < temp_f1_4) && (temp_f1_4 <= M2C_FIELD(arg0, f32 *, 0x1C))) {
            func_001854C8(&D_0036C700, 0x31, temp_6_4);
        }
    }
}
