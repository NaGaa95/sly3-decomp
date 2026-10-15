// Update the base object and clear the tagged activation bit on each of its three associated resources.
// Bit zero distinguishes an immediate flag word from a pointer to flag storage.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0023C580(void *);                            /* extern */

void func_00281B78(void *arg0) {
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_5;
    void *temp_3;
    void *temp_3_2;
    void *temp_4_3;

    func_0023C580(arg0);
    temp_3 = M2C_FIELD(arg0, void **, 0x14C);
    if (temp_3 != NULL) {
        temp_4 = M2C_FIELD(temp_3, s32 *, 0x3C);
        if ((temp_4 ^ 1) & 1) {
            M2C_FIELD(temp_4, s32 *, 0) = (s32) (M2C_FIELD(temp_4, s32 *, 0) & ~8);
        } else {
            M2C_FIELD(temp_3, s32 *, 0x3C) = (s32) (temp_4 & ~8);
        }
    }
    temp_3_2 = M2C_FIELD(arg0, void **, 0x150);
    if (temp_3_2 != NULL) {
        temp_4_2 = M2C_FIELD(temp_3_2, s32 *, 0x3C);
        if ((temp_4_2 ^ 1) & 1) {
            M2C_FIELD(temp_4_2, s32 *, 0) = (s32) (M2C_FIELD(temp_4_2, s32 *, 0) & ~8);
        } else {
            M2C_FIELD(temp_3_2, s32 *, 0x3C) = (s32) (temp_4_2 & ~8);
        }
    }
    temp_4_3 = M2C_FIELD(arg0, void **, 0x154);
    if (temp_4_3 != NULL) {
        temp_5 = M2C_FIELD(temp_4_3, s32 *, 0x3C);
        if ((temp_5 ^ 1) & 1) {
            M2C_FIELD(temp_5, s32 *, 0) = (s32) (M2C_FIELD(temp_5, s32 *, 0) & ~8);
            return;
        }
        M2C_FIELD(temp_4_3, s32 *, 0x3C) = (s32) (temp_5 & ~8);
    }
}
