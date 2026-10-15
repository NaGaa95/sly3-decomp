// Replace the attached handle with guarded old/new virtual notifications and list updates.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0013BD00(void *, s32);                 /* extern */
M2C_UNK func_0013BD88(void *, s32);                 /* extern */

void func_001A28C8(void *arg0, s32 arg1) {
    s32 temp_3;
    void *temp_2;
    void *temp_2_2;
    void *temp_2_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x178);
    if ((arg1 != temp_3) && (M2C_FIELD(arg0, s32 *, 0x17C) == 0)) {
        M2C_FIELD(arg0, s32 *, 0x17C) = 1;
        if (temp_3 != 0) {
            if (arg1 != 0) {
                temp_2 = M2C_FIELD(arg0, void **, 0xC);
                M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK, void *), 0x24)(arg0 + M2C_FIELD(temp_2, s16 *, 0x20), 1, arg0);
            }
            temp_2_2 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_2, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(arg0 + M2C_FIELD(temp_2_2, s16 *, 0x18), 6, 0, 0, 0, 0);
            func_0013BD88(arg0, M2C_FIELD(arg0, s32 *, 0x178));
        }
        M2C_FIELD(arg0, s32 *, 0x178) = arg1;
        if (arg1 != 0) {
            temp_2_3 = M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_2_3, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(arg0 + M2C_FIELD(temp_2_3, s16 *, 0x18), 5, 0, 0, 0, 0);
            func_0013BD00(arg0, M2C_FIELD(arg0, s32 *, 0x178));
        }
        M2C_FIELD(arg0, s32 *, 0x17C) = 0;
    }
}
