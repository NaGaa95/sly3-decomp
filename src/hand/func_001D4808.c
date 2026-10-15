// Require every global registry to be ready after the initial resource query.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0021DD30(M2C_UNK *);                       /* extern */
s32 func_0025AE28(M2C_UNK *);                       /* extern */
extern M2C_UNK D_003751D0;
extern M2C_UNK D_0046F550;
extern M2C_UNK D_0046F7A0;
extern M2C_UNK D_0046F810;
extern M2C_UNK D_0046FAA0;
extern M2C_UNK D_0046FBE0;
extern M2C_UNK D_0046FC30;
extern M2C_UNK D_0046FD00;
extern M2C_UNK D_00475480;

s32 func_001D4808(void) {
    s32 var_2;

    var_2 = 0;
    if (func_0025AE28(&D_00475480) == 0) {
        var_2 = 0;
        if (func_0021DD30(&D_0046F550) == 0) {
            var_2 = 0;
            if (func_0021DD30(&D_0046FAA0) == 0) {
                var_2 = 0;
                if (func_0021DD30(&D_0046FC30) == 0) {
                    var_2 = 0;
                    if (func_0021DD30(&D_0046F7A0) == 0) {
                        var_2 = 0;
                        if (func_0021DD30(&D_0046F810) == 0) {
                            var_2 = 0;
                            if (func_0021DD30(&D_003751D0) == 0) {
                                if (func_0021DD30(&D_0046FBE0) != 0) {
                                    return 0;
                                }
                                var_2 = func_0021DD30(&D_0046FD00) == 0;
                                /* Duplicate return node #11. Try simplifying control flow for better match */
                                return var_2;
                            }
                        }
                    }
                }
            }
        }
    }
    return var_2;
}
