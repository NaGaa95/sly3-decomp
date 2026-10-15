// Process the current record outcome and emit the original final-record or continuation notifications.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001854C8(M2C_UNK *, M2C_UNK, void *);  /* extern */
M2C_UNK func_00225EE8(s32, void *);                 /* extern */
M2C_UNK func_00244F08(s32, M2C_UNK);                /* extern */
s32 func_002459F8(s32);                             /* extern */
s32 func_0025E188(void);                          /* extern */
M2C_UNK func_0025E2B8(M2C_UNK, s32, M2C_UNK *);     /* extern */
M2C_UNK func_00278E58(void *, M2C_UNK);             /* extern */
M2C_UNK func_002793A0(void *);                      /* extern */
M2C_UNK func_002793F0(void *);                      /* extern */
s32 func_00279568(void *);                                /* extern */
extern M2C_UNK D_0036C700;
extern M2C_UNK D_00468D30;

void func_00279278(void *arg0) {
    s32 temp_4;
    s32 temp_4_2;
    void *temp_2;
    void *temp_3;

    temp_4 = func_00279568(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x278) == (M2C_FIELD(arg0, s32 *, 0x54) - 1)) {
        M2C_FIELD(arg0, s32 *, 0x28C) = temp_4;
        if (temp_4 != 0) {
            func_002793F0(arg0);
        }
        temp_4_2 = M2C_FIELD(arg0, s32 *, 0x288);
        if (temp_4_2 != 0) {
            func_00225EE8(temp_4_2, M2C_FIELD(arg0, void **, 0x48));
        }
        if (M2C_FIELD(arg0, s32 *, 0x28C) != 0) {
            if (M2C_FIELD(arg0, s32 *, 0x294) != 0) {
                func_0025E2B8(1, func_0025E188(), &D_00468D30);
            }
            func_00278E58(arg0, 0);
        }
    } else {
        if (temp_4 != 0) {
            func_001854C8(&D_0036C700, 0x57, arg0);
            func_00244F08(func_002459F8(0x2D), 0);
            func_002793A0(arg0);
            return;
        }
        func_001854C8(&D_0036C700, 0x58, arg0);
        func_00244F08(func_002459F8(M2C_FIELD(arg0, s32 *, 0x290)), 0);
        temp_3 = M2C_FIELD(arg0, void **, 0x48);
        temp_2 = M2C_FIELD(temp_3, void **, 0xC);
        M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK), 0x31C)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x318), 0);
    }
}
