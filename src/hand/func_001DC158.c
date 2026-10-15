// Initialize mapped resource storage, register all event callbacks, and wait for readiness.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0014EF50(void *, M2C_UNK, s32);        /* extern */
M2C_UNK func_001DB220(void *);                      /* extern */
s32 func_001DC430(void *, M2C_UNK);                 /* extern */
M2C_UNK func_002A9400(void *, s32, M2C_UNK);        /* extern */
M2C_UNK func_002A9EA8(void);                            /* extern */
M2C_UNK func_002AA050(void *, M2C_UNK, M2C_UNK *, void *); /* extern */
M2C_UNK func_002AE1B8(void *, M2C_UNK, s32, M2C_UNK *, void *); /* extern */
extern s32 D_0036B120;
extern M2C_UNK func_001DB560;
extern M2C_UNK func_001DB5A0;
extern M2C_UNK func_001DB5C8;
extern M2C_UNK func_001DB698;
extern M2C_UNK func_001DB6D0;

void func_001DC158(void *arg0, s32 arg1) {
    void *temp_17;

    M2C_FIELD(arg0, s32 *, 0x114) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10C) = 0;
    temp_17 = arg0 + 0x118;
    func_0014EF50(arg0 + 0x160, 0x40000, (M2C_FIELD(arg0, s32 *, 0x110) + 0x245A80) | 0x20000000);
    func_001DB220(arg0 + 0x180);
    func_002A9EA8();
    func_002A9400(temp_17, M2C_FIELD(arg0, s32 *, 0x110) + 0x98000, 0x1ADA60);
    func_002AE1B8(temp_17, 0, 0, &func_001DB560, arg0);
    func_002AE1B8(temp_17, 2, 0, &func_001DB5A0, arg0);
    func_002AE1B8(temp_17, 3, 0, &func_001DB5A0, arg0);
    func_002AE1B8(temp_17, 2, D_0036B120 + 1, &func_001DB5A0, arg0);
    func_002AE1B8(temp_17, 3, D_0036B120 + 1, &func_001DB5A0, arg0);
    func_002AA050(temp_17, 1, &func_001DB5C8, arg0);
    func_002AA050(temp_17, 4, &func_001DB698, arg0);
    func_002AA050(temp_17, 0, &func_001DB6D0, arg0);
    do {

    } while (func_001DC430(arg0, 1) == 0);
}
