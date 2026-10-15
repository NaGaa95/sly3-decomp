// Replace the active handle and apply the ordered resource and virtual activation notifications.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001DE690(void *, M2C_UNK);             /* extern */
M2C_UNK func_0023FE38(s32, M2C_UNK);                /* extern */
M2C_UNK func_0023FEC0(s32, M2C_UNK);                /* extern */

void func_001E47F0(void *arg0, s32 arg1) {
    s32 temp_4;
    void *temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_2_4;
    void *temp_3;
    void *temp_3_2;
    void *temp_3_3;
    void *temp_3_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x1C90);
    if (arg1 != temp_4) {
        if (temp_4 != 0) {
            func_0023FE38(temp_4, 0x779);
            func_0023FE38(M2C_FIELD(arg0, s32 *, 0x1C90), 0x77A);
            temp_3 = M2C_FIELD(arg0, void **, 0x1C94);
            if (temp_3 != NULL) {
                temp_2 = M2C_FIELD(temp_3, void **, 0xC);
                M2C_FIELD(temp_2, M2C_UNK (**)(void *), 0x4C)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x48));
            }
            temp_3_2 = M2C_FIELD(arg0, void **, 0x1C98);
            if (temp_3_2 != NULL) {
                temp_2_2 = M2C_FIELD(temp_3_2, void **, 0xC);
                M2C_FIELD(temp_2_2, M2C_UNK (**)(void *), 0x4C)(temp_3_2 + M2C_FIELD(temp_2_2, s16 *, 0x48));
            }
            func_001DE690(arg0, 0);
        }
        M2C_FIELD(arg0, s32 *, 0x1C90) = arg1;
        if (arg1 != 0) {
            func_0023FEC0(arg1, 0x779);
            func_0023FEC0(M2C_FIELD(arg0, s32 *, 0x1C90), 0x77A);
            temp_3_3 = M2C_FIELD(arg0, void **, 0x1C94);
            if (temp_3_3 != NULL) {
                temp_2_3 = M2C_FIELD(temp_3_3, void **, 0xC);
                M2C_FIELD(temp_2_3, M2C_UNK (**)(void *), 0x44)(temp_3_3 + M2C_FIELD(temp_2_3, s16 *, 0x40));
            }
            temp_3_4 = M2C_FIELD(arg0, void **, 0x1C98);
            if (temp_3_4 != NULL) {
                temp_2_4 = M2C_FIELD(temp_3_4, void **, 0xC);
                M2C_FIELD(temp_2_4, M2C_UNK (**)(void *), 0x44)(temp_3_4 + M2C_FIELD(temp_2_4, s16 *, 0x40));
            }
            func_001DE690(arg0, 0x17);
        }
    }
}
