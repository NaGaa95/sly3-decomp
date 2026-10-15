// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern f32 D_00320E54;
extern f32 D_00320E58;

void func_001697D0(void *arg0, s32 arg1) {
    void *temp_v1;

    M2C_FIELD(arg0, s32 *, 0x130) = arg1;
    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), void **, 0x90);
    M2C_FIELD(temp_v1, s32 *, 0x70) = arg1;
    if (arg1 != 0) {
        M2C_FIELD(temp_v1, f32 *, 0x60) = (f32) D_00320E54;
        return;
    }
    M2C_FIELD(temp_v1, f32 *, 0x60) = (f32) D_00320E58;
}
