// Apply the requested event identifier and synchronize both associated object resources.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_001F4350(void *, M2C_UNK);                 /* extern */
M2C_UNK func_001F4548(void *, s32);                            /* extern */
M2C_UNK func_002075E8(void *, M2C_UNK);             /* extern */
M2C_UNK func_00207880(void *);                      /* extern */
M2C_UNK func_00262450(void *, M2C_UNK);             /* extern */

void func_00207E18(void *arg0, s32 arg1) {
    void *temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_2_4;
    void *temp_3;
    void *temp_3_2;
    void *temp_3_3;
    void *temp_3_4;

    func_001F4548(arg0, arg1);
    if (func_001F4350(arg0, -1) != 0) {
        func_002075E8(arg0, 1);
        temp_3 = M2C_FIELD(arg0, void **, 0x400);
        if (temp_3 != NULL) {
            temp_2 = M2C_FIELD(temp_3, void **, 0xC);
            M2C_FIELD(temp_2, M2C_UNK (**)(void *), 0x1C4)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x1C0));
            func_00262450(M2C_FIELD(arg0, void **, 0x400), 0x37C);
            func_00207880(arg0);
        }
        temp_3_2 = M2C_FIELD(arg0, void **, 0x3A0);
        if (temp_3_2 != NULL) {
            temp_2_2 = M2C_FIELD(temp_3_2, void **, 0xC);
            M2C_FIELD(temp_2_2, M2C_UNK (**)(void *), 0x44)(temp_3_2 + M2C_FIELD(temp_2_2, s16 *, 0x40));
        }
    } else {
        func_002075E8(arg0, 0);
        temp_3_3 = M2C_FIELD(arg0, void **, 0x400);
        if (temp_3_3 != NULL) {
            temp_2_3 = M2C_FIELD(temp_3_3, void **, 0xC);
            M2C_FIELD(temp_2_3, M2C_UNK (**)(void *), 0x1B4)(temp_3_3 + M2C_FIELD(temp_2_3, s16 *, 0x1B0));
        }
        temp_3_4 = M2C_FIELD(arg0, void **, 0x3A0);
        if (temp_3_4 != NULL) {
            temp_2_4 = M2C_FIELD(temp_3_4, void **, 0xC);
            M2C_FIELD(temp_2_4, M2C_UNK (**)(void *), 0x4C)(temp_3_4 + M2C_FIELD(temp_2_4, s16 *, 0x48));
        }
    }
}
