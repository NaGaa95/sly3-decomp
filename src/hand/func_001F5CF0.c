// Release the current resource, notify its owner when needed, and clear the handle.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001F4B00(M2C_UNK *, s32, s32);         /* extern */
M2C_UNK func_001F6148(void *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_00259D50(void *);                      /* extern */
extern M2C_UNK D_00475480;

void func_001F5CF0(void *arg0) {
    s32 temp_5;
    s32 temp_6;

    temp_6 = M2C_FIELD(arg0, s32 *, 0x38);
    if (temp_6 != 0) {
        temp_5 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x130);
        if (temp_5 != -1) {
            func_001F4B00(&D_00475480, temp_5, temp_6);
        }
        func_00259D50(M2C_FIELD(arg0, void **, 0x10) + 0x4B0);
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x11CC) == 2) {
            func_001F6148(arg0, -1, 0);
        }
        M2C_FIELD(arg0, s32 *, 0x38) = 0;
    }
}
