// Update each registered resource when needed and activate the resolved object.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00168AB0(void *, M2C_UNK, M2C_UNK, s32); /* extern */
M2C_UNK func_001747A0(s32, s32);                    /* extern */
s32 func_00175070(s32);                             /* extern */
void *func_001750B0(s32);                           /* extern */
extern s32 D_00474F50;
extern s32 D_00474F58[];

void func_00175110(s32 arg0, s32 arg1, s32 arg2) {
    s32 *temp_3;
    s32 var_16;
    void *temp_2;

    if (func_00175070(arg1) <= 0) {
        var_16 = 0;
        if (D_00474F50 > 0) {
            do {
                temp_3 = &D_00474F58[var_16];
                var_16 += 1;
                func_001747A0(arg2, *temp_3);
            } while (var_16 < D_00474F50);
        }
    }
    temp_2 = func_001750B0(arg0);
    func_00168AB0(temp_2, 0, 0, arg2);
    M2C_FIELD(temp_2, s32 *, 0x448) = 1;
}
