// Resolve the descriptor pair and initialize the selected object record with all seven inputs.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0014B248(void *, s32);                 /* extern */
M2C_UNK func_0014B808(s32, s32, s32);               /* extern */
void *func_0014BBB8(void *, s32);                   /* extern */
M2C_UNK func_0014BC70(void *);                      /* extern */
M2C_UNK func_0014BD58(void *);                      /* extern */
M2C_UNK func_001D2898(void *, s32, M2C_UNK);        /* extern */
s32 func_0023DDA0(void *, s32, M2C_UNK);            /* extern */

void func_0014B590(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 fparg0) {
    s32 var_18;
    s32 var_19;
    void *temp_2;
    void *temp_2_2;

    if (arg2 == -1) {
        var_19 = M2C_FIELD(arg0, s32 *, 0x48);
        var_18 = M2C_FIELD(arg0, s32 *, 0x4C);
        goto block_5;
    }
    var_19 = func_0023DDA0(arg0, arg2, 1);
    if (var_19 != 0) {
        var_18 = func_0023DDA0(arg0, arg2, 6);
        if (var_18 == 0) {
            if (arg3 < 2) {
block_5:
                goto block_6;
            }
        } else {
block_6:
            temp_2 = func_0014BBB8(arg0, arg3);
            func_0014BD58(temp_2);
            M2C_FIELD(temp_2, s32 *, 8) = arg1;
            M2C_FIELD(temp_2, s32 *, 0xC) = var_19;
            M2C_FIELD(temp_2, s32 *, 0x10) = var_18;
            M2C_FIELD(temp_2, f32 *, 0x14) = fparg0;
            M2C_FIELD(temp_2, s32 *, 0x138) = arg5;
            M2C_FIELD(temp_2, void **, 4) = arg0;
            M2C_FIELD(temp_2, s32 *, 0x18) = arg3;
            func_001D2898(temp_2 + 0x20, arg4, 0x80);
            M2C_FIELD(temp_2, f32 *, 0) = -1.0f;
            func_0014B808(arg3, arg4, M2C_FIELD(temp_2, s32 *, 0xA4));
            temp_2_2 = M2C_FIELD(arg0, void **, 0xC);
            func_0014B248(temp_2, M2C_FIELD(temp_2_2, s32 (**)(void *), 0x124)(arg0 + M2C_FIELD(temp_2_2, s16 *, 0x120)));
            func_0014BC70(temp_2);
        }
    }
}
