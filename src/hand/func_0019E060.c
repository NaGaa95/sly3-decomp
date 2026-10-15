// Change the active mode, release its previous attachment, and notify the selected record.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001854C8(M2C_UNK *, M2C_UNK, void *);  /* extern */
M2C_UNK func_0019BA10(void *, void *);              /* extern */
M2C_UNK func_0019C570(void *, M2C_UNK);             /* extern */
M2C_UNK func_0019E1A0(void *);                            /* extern */
extern f32 D_0036BB98;
extern M2C_UNK D_0036C700;

void func_0019E060(void *arg0, s32 arg1) {
    s32 temp_3;
    void *var_5;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x1F0);
    if (temp_3 != arg1) {
        if ((temp_3 == 1) && (M2C_FIELD(arg0, void **, 0x1F8) != NULL)) {
            func_0019E1A0(arg0);
        }
        M2C_FIELD(arg0, s32 *, 0x1F0) = arg1;
        M2C_FIELD(arg0, f32 *, 0x1F4) = (f32) D_0036BB98;
        switch (arg1) {                             /* irregular */
        case 1:
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x1F8), s32 *, 0x2F0) = (s32) M2C_FIELD(arg0, s32 *, 0x1FC);
            func_0019C570(M2C_FIELD(arg0, void **, 0x1F8), 3);
            break;
        case 2:
            func_001854C8(&D_0036C700, 0x4A, arg0);
            break;
        }
        if (arg1 != -1) {
            var_5 = arg0 + ((arg1 * 0x10) + 0x200);
        } else {
            var_5 = NULL;
        }
        func_0019BA10(arg0, var_5);
    }
}
