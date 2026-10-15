// Synchronize intrusive-list membership with the active, unblocked state.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011AF60(M2C_UNK *, void *);           /* extern */
M2C_UNK func_0011B028(M2C_UNK *, void *);           /* extern */
s32 func_0011B0C0(M2C_UNK *, void *);               /* extern */
extern M2C_UNK D_00479BE0;

void func_001F4EC0(void *arg0) {
    s32 temp_4;
    s32 var_3;

    temp_4 = func_0011B0C0(&D_00479BE0, arg0);
    var_3 = 0;
    if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
        var_3 = M2C_FIELD(arg0, s32 *, 8) > 0;
    }
    if (temp_4 != var_3) {
        if (var_3 != 0) {
            func_0011AF60(&D_00479BE0, arg0);
            return;
        }
        func_0011B028(&D_00479BE0, arg0);
    }
}
