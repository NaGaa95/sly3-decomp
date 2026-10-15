// Execute the eligible transition, publish its event, and notify the associated resources.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001854C8(M2C_UNK *, M2C_UNK, void *);  /* extern */
M2C_UNK func_00185A70(void *, M2C_UNK, s32, s32);   /* extern */
M2C_UNK func_00185DB0(void *, M2C_UNK, s32, s32, s32); /* extern */
M2C_UNK func_001871C0(s32);                         /* extern */
s32 func_001880F0(void *);                          /* extern */
M2C_UNK func_0018AAB8(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_0021E930(M2C_UNK *, s32);              /* extern */
s32 func_002845B0(M2C_UNK *, void *, M2C_UNK);      /* extern */
extern M2C_UNK D_0036C700;
extern M2C_UNK D_0046F770;
extern M2C_UNK D_00475480;
extern M2C_UNK D_004BC230;

void func_00188928(void *arg0) {
    s32 temp_5;
    void *temp_2;

    func_0018AAB8(&D_00475480, 0);
    if (func_002845B0(&D_004BC230, arg0, 5) != 0) {
        func_001871C0(M2C_FIELD(arg0, s32 *, 0x6C));
        return;
    }
    if (func_001880F0(arg0) != 0) {
        func_001854C8(&D_0036C700, 0x28, arg0);
        func_00185A70(arg0, 5, M2C_FIELD(arg0, s32 *, 0x98), M2C_FIELD(arg0, s32 *, 0x9C));
        func_00185DB0(arg0, 5, M2C_FIELD(arg0, s32 *, 0xA0), M2C_FIELD(arg0, s32 *, 0xA4), M2C_FIELD(arg0, s32 *, 0xFC));
        temp_5 = M2C_FIELD(arg0, s32 *, 0x4C);
        if ((temp_5 != -1) && (M2C_FIELD(arg0, s32 *, 0x50) != 0)) {
            func_0021E930(&D_0046F770, temp_5);
        }
        temp_2 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(arg0 + M2C_FIELD(temp_2, s16 *, 0x18), 0x17, 0, 0, 0, 0);
    }
}
