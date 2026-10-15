// Run reverse registered callbacks, notify the object, and enable its tagged activation flags when eligible.
// Bit zero distinguishes an immediate flag word from a pointer to flag storage.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00129B58(s32, M2C_UNK, M2C_UNK);           /* extern */
M2C_UNK func_001C7F18(void *);                            /* extern */
M2C_UNK func_001C7FA8(void *, f32);                 /* extern */
M2C_UNK func_001C9118(void *, M2C_UNK);             /* extern */
extern f32 D_0036BB98;

void func_001C7DC8(void *arg0) {
    s32 temp_3;
    s32 temp_4;
    void *temp_2;

    func_001C7F18(arg0);
    temp_2 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(arg0 + M2C_FIELD(temp_2, s16 *, 0x18), 0, 1, 0, 0, 0);
    temp_4 = M2C_FIELD(arg0, s32 *, 0);
    if ((temp_4 != 0) && (func_00129B58(temp_4, 1, 1) != 0)) {
        if (((s64) (M2C_FIELD(arg0, s64 *, 0x28) << 0xC) >> 0x3C) == 2) {
            func_001C9118(arg0, 0);
        }
        temp_3 = M2C_FIELD(arg0, s32 *, 0x3C);
        if ((temp_3 ^ 1) & 1) {
            M2C_FIELD(temp_3, s32 *, 0) = (s32) (M2C_FIELD(temp_3, s32 *, 0) | 2);
        } else {
            M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_3 | 2);
        }
        func_001C7FA8(arg0, D_0036BB98);
    }
}
