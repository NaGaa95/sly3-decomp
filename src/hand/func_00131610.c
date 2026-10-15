// Change the mode and timestamp, preserving the timed resource state across activation and release.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00238A38(void *);                      /* extern */
M2C_UNK func_00238AB8(void *);                      /* extern */
s32 func_002533C0(void *, M2C_UNK);                 /* extern */
M2C_UNK func_00254D38(void *, void *, s32, f32);    /* extern */
M2C_UNK func_00254E18(void *);                      /* extern */
extern f32 D_0036BB98;

void func_00131610(void *arg0, s32 arg1) {
    f32 var_f12;
    void *temp_2;
    void *temp_2_2;
    void *temp_3;
    void *temp_3_2;
    void *temp_5;

    if (M2C_FIELD(arg0, s32 *, 0x30) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x30) = arg1;
        M2C_FIELD(arg0, f32 *, 0x34) = (f32) D_0036BB98;
        switch (arg1) {                             /* irregular */
        case 0:
            if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0) == 0) && (func_002533C0(M2C_FIELD(arg0, void **, 0x10), 0xE) != 0) && (temp_3 = M2C_FIELD(arg0, void **, 0x10), (D_0036BB98 == M2C_FIELD(temp_3, f32 *, 0x1150)))) {
                var_f12 = M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), void **, 4), f32 *, 0x64) * M2C_FIELD(temp_3, f32 *, 0x114C);
            } else {
                var_f12 = 0.0f;
            }
            temp_5 = M2C_FIELD(arg0, void **, 0x10);
            temp_3_2 = M2C_FIELD(arg0, void **, 0x40);
            M2C_FIELD(arg0, s32 *, 0x44) = (s32) M2C_FIELD(temp_5, s32 *, 0x1B8);
            func_00254D38(temp_3_2, temp_5, M2C_FIELD(temp_3_2, s32 *, 0xC) | 1, var_f12);
            return;
        case 1:
            func_00238A38(arg0);
            func_00238AB8(arg0);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x1B4) = 0;
            temp_2 = M2C_FIELD(arg0, void **, 0x40);
            if (temp_2 != NULL) {
                if ((M2C_FIELD(temp_2, s32 *, 0) == 0) && (func_002533C0(M2C_FIELD(arg0, void **, 0x10), 0xE) != 0)) {
                    temp_2_2 = M2C_FIELD(arg0, void **, 0x40);
                    M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), f32 *, 0x114C) = (f32) (M2C_FIELD(M2C_FIELD(temp_2_2, void **, 8), f32 *, 0x1C) / M2C_FIELD(M2C_FIELD(temp_2_2, void **, 4), f32 *, 0x64));
                    M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), f32 *, 0x1150) = (f32) D_0036BB98;
                }
                func_00254E18(M2C_FIELD(arg0, void **, 0x40));
                M2C_FIELD(arg0, void **, 0x40) = NULL;
            }
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x1B8) = (s32) M2C_FIELD(arg0, s32 *, 0x44);
            break;
        }
    }
}
