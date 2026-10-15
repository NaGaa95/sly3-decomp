// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Preserve incoming a0 context independently assigned by original callers.
// Notify each object in the pointer array through its adjusted virtual method.
#include "m2c_prelude.h"

void func_001FC338(u32 context, s32 arg1, s32 arg2, void **arg3) {
    s32 var_s0;
    void **var_s1;
    void *temp_v0;
    void *temp_v1;

    if (arg2 > 0) {
        var_s1 = arg3;
        var_s0 = arg2;
        do {
            temp_v1 = *var_s1;
            var_s1 += 1;
            temp_v0 = M2C_FIELD(temp_v1, void **, 0xC);
            M2C_FIELD(temp_v0, M2C_UNK (**)(void *, s32), 0xEC)(temp_v1 + M2C_FIELD(temp_v0, s16 *, 0xE8), arg1);
            var_s0 -= 1;
        } while (var_s0 != 0);
    }
}
