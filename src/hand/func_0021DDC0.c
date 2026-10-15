// Replace the original global-list registration and preserve its associated key value.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011AF90(M2C_UNK *, void *);           /* extern */
s32 func_0021DC30(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_0021DC60(M2C_UNK *, s32, s32);         /* extern */
s32 func_0021DD30(void *);                                /* extern */
extern M2C_UNK D_0046F540;

void func_0021DDC0(void *arg0, s32 arg1) {
    s32 temp_19;
    void *temp_2;

    if (func_0021DD30(arg0) != 0) {
        temp_2 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_2, M2C_UNK (**)(void *), 0x5C)(arg0 + M2C_FIELD(temp_2, s16 *, 0x58));
    }
    temp_19 = func_0021DC30(&D_0046F540, arg1);
    func_0011AF90(&D_0046F540, arg0);
    M2C_FIELD(arg0, s32 *, 0x18) = arg1;
    if (arg1 != -1) {
        func_0021DC60(&D_0046F540, arg1, temp_19);
    }
}
