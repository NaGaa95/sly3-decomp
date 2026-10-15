// Update the changed-owner counter and perform the state-dependent resource reset.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0021A300(void *);                      /* extern */
s32 func_0021A710(void *);                                /* extern */
s32 func_0021A720(void *);                          /* extern */

void func_0021A450(void *arg0, s32 arg1) {
    s32 temp_2;
    void *temp_3;

    if (func_0021A710(arg0) != 0) {
        temp_3 = M2C_FIELD(arg0, void **, 0xA0);
        if ((temp_3 != NULL) && (M2C_FIELD(arg0, s32 *, 0xAC) == 0) && (arg1 != M2C_FIELD(arg0, s32 *, 0x40))) {
            M2C_FIELD(temp_3, s32 *, 0x120) = (s32) (M2C_FIELD(temp_3, s32 *, 0x120) + 1);
        }
        temp_2 = func_0021A720(arg0);
        if ((temp_2 == 0) || ((M2C_FIELD(arg0, s32 *, 0xAC) != 0) && (temp_2 == 1))) {
            func_0021A300(arg0);
        }
    }
}
