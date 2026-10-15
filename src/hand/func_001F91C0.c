// Enter the requested state through the associated-resource and virtual notifications.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001F7588(void *);                      /* extern */
M2C_UNK func_001FE728(s32, M2C_UNK);                /* extern */

void func_001F91C0(void *arg0, s32 arg1) {
    s32 temp_4;
    void *temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_3;

    if (M2C_FIELD(arg0, s32 *, 0x130) != arg1) {
        if (arg1 == 1) {
            temp_3 = M2C_FIELD(arg0, void **, 0x16C);
            if (temp_3 != NULL) {
                temp_2 = M2C_FIELD(temp_3, void **, 0xC);
                M2C_FIELD(temp_2, M2C_UNK (**)(void *, void *), 0x2C4)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x2C0), arg0);
            }
            temp_4 = M2C_FIELD(arg0, s32 *, 0x194);
            if (temp_4 != 0) {
                func_001FE728(temp_4, 1);
            }
            temp_2_2 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_2, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(arg0 + M2C_FIELD(temp_2_2, s16 *, 0x18), 5, 0, 0, 0, 0);
            temp_2_3 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_3, M2C_UNK (**)(void *, M2C_UNK), 0x284)(arg0 + M2C_FIELD(temp_2_3, s16 *, 0x280), -1);
            return;
        }
        func_001F7588(arg0);
    }
}
