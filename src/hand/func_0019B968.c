// Resolve each 16-byte descriptor and store the resource in its type-specific slot.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
s32 func_0013B500(void *, M2C_UNK);
/* extern */ void *func_0017E1B8(M2C_UNK *, M2C_UNK, s32, void *);
/* extern */ extern M2C_UNK D_00475480;
void func_0019B968(void *arg0, s32 arg1, void *arg2) {
    void *temp_2;
    s32 temp_6;
    s32 var_18;
    void *var_17;
    if (arg1 > 0) {
        var_17 = arg2;
        var_18 = arg1;
        do {
            temp_6 = M2C_FIELD(var_17, s32 *, 0);
            if (temp_6 != -1) {
                temp_2 = func_0017E1B8(&D_00475480, 4, temp_6, arg0);
                if (temp_2 != 0) {
                    if (func_0013B500(temp_2, 0x82) != 0) {
                        M2C_FIELD(var_17, void **, 4) = temp_2;
                    }
                    else if (func_0013B500(temp_2, 0x84) != 0) {
                        M2C_FIELD(var_17, void **, 8) = temp_2;
                    }
                }
            }
            var_18 -= 1;
            var_17 += 0x10;
        }
        while (var_18 != 0);
    }
}
