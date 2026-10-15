// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_00215958(void *arg0) {
    s32 temp_a0;
    void *temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x1A8);
    if (temp_v1 != NULL) {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x1B0);
        if (temp_a0 >= -1) {
            if (temp_a0 >= 2) {
                if (temp_a0 < 8) {
                    if (temp_a0 >= 6) {
                        goto block_5;
                    }
                    goto block_7;
                }
                goto block_6;
            }
block_5:
            temp_v0 = M2C_FIELD(temp_v1, void **, 0xC);
            M2C_FIELD(temp_v0, M2C_UNK (**)(void *), 0x1B4)(temp_v1 + M2C_FIELD(temp_v0, s16 *, 0x1B0));
        } else {
block_6:
block_7:
            M2C_FIELD(M2C_FIELD(temp_v1, void **, 0xC), M2C_UNK (**)(void *), 0x1C4)(temp_v1 + M2C_FIELD(M2C_FIELD(temp_v1, void **, 0xC), s16 *, 0x1C0));
        }
    }
}
