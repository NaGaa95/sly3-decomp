// Synchronize global list membership with a changed object state.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011AF60(M2C_UNK *, void *);           /* extern */
M2C_UNK func_0011B028(M2C_UNK *, void *);           /* extern */
s32 func_0011B0C0(M2C_UNK *, void *);               /* extern */
extern M2C_UNK D_0047979C;

void func_00263080(void *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x98);
    if (temp_2 != arg1) {
        if ((temp_2 == 0) && (func_0011B0C0(&D_0047979C, arg0) != 0)) {
            func_0011B028(&D_0047979C, arg0);
        }
        M2C_FIELD(arg0, s32 *, 0x98) = arg1;
        if ((arg1 == 0) && (func_0011B0C0(&D_0047979C, arg0) == 0)) {
            func_0011AF60(&D_0047979C, arg0);
        }
    }
}
