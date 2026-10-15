// On the final reference release, notify and free every linked record before the virtual cleanup.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011E1F0(M2C_UNK *, void *);           /* extern */
extern M2C_UNK D_004798D0;

void func_0020BDC0(void *arg0) {
    s32 temp_2;
    void *temp_16;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_3;
    void *var_17;

    temp_2 = M2C_FIELD(arg0, s32 *, 0) - 1;
    M2C_FIELD(arg0, s32 *, 0) = temp_2;
    if (temp_2 == 0) {
        var_17 = M2C_FIELD(arg0, void **, 0xE4);
        if (var_17 != NULL) {
            do {
                temp_3 = M2C_FIELD(var_17, void **, 0);
                temp_2_2 = M2C_FIELD(temp_3, void **, 0xC);
                M2C_FIELD(temp_2_2, M2C_UNK (**)(void *, M2C_UNK, void *), 0x2C)(temp_3 + M2C_FIELD(temp_2_2, s16 *, 0x28), 9, arg0);
                temp_16 = M2C_FIELD(var_17, void **, 8);
                func_0011E1F0(&D_004798D0, var_17);
                var_17 = temp_16;
            } while (var_17 != NULL);
        }
        M2C_FIELD(arg0, void **, 0xE4) = NULL;
        temp_2_3 = M2C_FIELD(arg0, void **, 0xE8);
        M2C_FIELD(temp_2_3, M2C_UNK (**)(void *), 0x4C)(arg0 + M2C_FIELD(temp_2_3, s16 *, 0x48));
    }
}
