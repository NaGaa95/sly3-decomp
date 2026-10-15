// Choose the mode-specific availability result after the shared eligibility checks.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00156998(void *);                          /* extern */
s32 func_00173428(s32);                             /* extern */
s32 func_0021F410(s32);                             /* extern */

s32 func_00154518(void *arg0, s32 arg1) {
    s32 temp_4;
    s32 var_2;
    s32 var_2_2;

    var_2 = 0;
    if ((func_0021F410(arg1) != 0) && (var_2 = 0, (func_00156998(arg0) == 0))) {
        switch (arg1) {                             /* irregular */
        case 2:
            temp_4 = M2C_FIELD(arg0, s32 *, 0x1108);
            var_2_2 = 0;
            if (temp_4 != 0) {
                var_2_2 = func_00173428(temp_4) != 0;
            }
            return var_2_2 ^ 1;
        case 3:
            return M2C_FIELD(arg0, s32 *, 0x13E0);
        default:
            var_2 = M2C_FIELD(arg0, s32 *, 0x1274) == 0;
            /* Duplicate return node #13. Try simplifying control flow for better match */
            return var_2;
        }
    } else {
        return var_2;
    }
}
