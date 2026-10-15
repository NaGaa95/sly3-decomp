// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern f32 D_0036BBD8;

void func_00261050(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x54) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x54) = arg1;
        M2C_FIELD(arg0, f32 *, 0x58) = (f32) D_0036BBD8;
    }
}
