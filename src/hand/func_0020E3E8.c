// Attach the eligible object, optionally clone its resource, and complete the original update.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0013B500(void *, M2C_UNK);                 /* extern */
void *func_001FE728(void *, M2C_UNK);               /* extern */
M2C_UNK func_00202D30(void *, void *);              /* extern */
M2C_UNK func_0020BC78(void *);                      /* extern */
M2C_UNK func_0020BDA8(void);                            /* extern */

void func_0020E3E8(void *arg0, s32 *arg1, void *arg2) {
    s32 temp_2;
    void *temp_2_2;
    void *temp_3;

    func_0020BDA8();
    if ((arg2 != NULL) && (func_0013B500(arg2, 0x2D) != 0) && (M2C_FIELD(arg2, s32 *, 0xD8) == 0)) {
        M2C_FIELD(arg0, void **, 0xF4) = arg2;
        temp_2 = *arg1;
        M2C_FIELD(arg0, s32 *, 0xF0) = temp_2;
        if (temp_2 == 0) {
            temp_2_2 = func_001FE728(arg2, 1);
            M2C_FIELD(arg0, void **, 0xF8) = temp_2_2;
            temp_3 = M2C_FIELD(temp_2_2, void **, 0xC);
            M2C_FIELD(temp_3, M2C_UNK (**)(void *), 0xC)(temp_2_2 + M2C_FIELD(temp_3, s16 *, 8));
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xF8), s32 *, 0x14) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x14);
            func_00202D30(M2C_FIELD(arg0, void **, 0xF8), arg0);
            M2C_FIELD(M2C_FIELD(arg0, void **, 0xF8), s32 *, 0x60) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x60);
        }
    }
    func_0020BC78(arg0);
}
