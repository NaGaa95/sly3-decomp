// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_0011AF60(M2C_UNK *, void *);           /* extern */
extern M2C_UNK D_00479B74;

void *func_00256278(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, f32 *, 0x14) = 1.0f;
    M2C_FIELD(arg0, f32 *, 0x18) = 2.0f;
    M2C_FIELD(arg0, s32 *, 0x10) = -1;
    M2C_FIELD(arg0, s32 *, 8) = -1;
    func_0011AF60(&D_00479B74, arg0);
    return arg0;
}
