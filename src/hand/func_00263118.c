// Allocate 48-byte resource records and initialize every indexed entry.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00117B40(s32, s32, M2C_UNK);               /* extern */
s32 func_00119048(s32);                             /* extern */
M2C_UNK func_00263748(void *, s32, s32 *, M2C_UNK); /* extern */

void func_00263118(void *arg0, s32 arg1) {
    s32 *temp_6;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_18;

    temp_2 = func_00119048(arg1);
    var_18 = 1;
    M2C_FIELD(arg0, s32 *, 0x40) = temp_2;
    M2C_FIELD(arg0, s32 *, 0x44) = func_00117B40(M2C_FIELD(arg0, s32 *, 0xB4), (temp_2 + 1) * 0x30, 0x1B);
    if (M2C_FIELD(arg0, s32 *, 0x40) > 0) {
        do {
            var_18 += 1;
            temp_2_2 = func_00119048(arg1);
            temp_6 = M2C_FIELD(arg0, s32 *, 0x44) + (temp_2_2 * 0x30);
            *temp_6 = temp_2_2;
            func_00263748(arg0, arg1, temp_6, 0);
        } while (M2C_FIELD(arg0, s32 *, 0x40) >= var_18);
    }
}
