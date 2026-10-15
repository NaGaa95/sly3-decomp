// Update the selected mode and clock, then notify the object and related component.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0021DD30(void *);                          /* extern */
extern f32 D_0036BBD8;

void func_001D0C08(void *arg0, s32 arg1) {
    void *temp_2;
    void *temp_2_2;
    void *temp_3;

    if (M2C_FIELD(arg0, s32 *, 0x50) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x50) = arg1;
        M2C_FIELD(arg0, f32 *, 0x54) = (f32) D_0036BBD8;
    }
    if (func_0021DD30(arg0) == 0) {
        temp_2 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK), 0x54)(arg0 + M2C_FIELD(temp_2, s16 *, 0x50), 0);
    }
    temp_3 = M2C_FIELD(arg0, void **, 0x34);
    if (temp_3 != NULL) {
        temp_2_2 = M2C_FIELD(temp_3, void **, 0xC);
        M2C_FIELD(temp_2_2, M2C_UNK (**)(void *), 0x1C4)(temp_3 + M2C_FIELD(temp_2_2, s16 *, 0x1C0));
    }
}
