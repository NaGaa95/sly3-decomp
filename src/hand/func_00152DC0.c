// Update the requested event state and perform the original resource and virtual notifications.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00137628(void *);                      /* extern */
M2C_UNK func_00156B00(void *);                      /* extern */
M2C_UNK func_001BDBB0(s32, M2C_UNK);                /* extern */
s32 func_001F4350(void *, M2C_UNK);                 /* extern */
M2C_UNK func_001F4548(void *, s32);                 /* extern */
M2C_UNK func_00238568(void *);                      /* extern */
M2C_UNK func_00241B18(void *, M2C_UNK, M2C_UNK);    /* extern */

void func_00152DC0(void *arg0, s32 arg1) {
    s32 temp_2;
    void *temp_2_2;

    if (arg1 == -1) {
        func_001BDBB0(arg0 + 0xF60, -1);
    }
    func_001F4548(arg0, arg1);
    temp_2 = func_001F4350(arg0, -1);
    func_00241B18(arg0, (temp_2 == 0) ? -1 : 0, 0);
    if (temp_2 != 0) {
        func_00238568(arg0 + 0x29C);
    }
    temp_2_2 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(temp_2_2, M2C_UNK (**)(void *), 0x3BC)(arg0 + M2C_FIELD(temp_2_2, s16 *, 0x3B8));
    if (temp_2 == 0) {
        func_00137628(arg0 + 0x13F8);
        M2C_FIELD(arg0, s32 *, 0x13FC) = -1;
    }
    if (arg1 != -1) {
        func_00156B00(arg0);
    }
}
