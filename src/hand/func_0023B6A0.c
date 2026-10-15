// Resolve and cache the shared virtual identifier, registering the source when needed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0013CD10(M2C_UNK *, void *);           /* extern */
void *func_0023B650(void *);                              /* extern */
extern M2C_UNK D_00475480;

void func_0023B6A0(void *arg0) {
    void *temp_2;
    void *temp_2_2;

    if (M2C_FIELD(arg0, s32 *, 0xDC) == 0) {
        temp_2 = func_0023B650(arg0);
        if (M2C_FIELD(temp_2, s32 *, 0xDC) == 0) {
            temp_2_2 = M2C_FIELD(temp_2, void **, 0xC);
            M2C_FIELD(temp_2, s32 *, 0xDC) = M2C_FIELD(temp_2_2, s32 (**)(void *), 0x1CC)(temp_2 + M2C_FIELD(temp_2_2, s16 *, 0x1C8));
            func_0013CD10(&D_00475480, temp_2);
        }
        M2C_FIELD(arg0, s32 *, 0xDC) = M2C_FIELD(temp_2, s32 *, 0xDC);
    }
}
