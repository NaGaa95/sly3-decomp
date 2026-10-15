// Execute the enabled resource transition and optional selected-object notification.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
#include "actor_state_resource_api.h"

s32 func_0013B500(void *, M2C_UNK);                    /* extern */
M2C_UNK func_00155ED8(void *, M2C_UNK);                /* extern */
M2C_UNK func_001854C8(M2C_UNK *, M2C_UNK, s32);     /* extern */
M2C_UNK func_00186248(s32);                         /* extern */
s32 func_00187CB8(s32);                                /* extern */
extern M2C_UNK D_0036C700;
extern M2C_UNK D_00475480;

void func_00186DA0(s32 arg0) {
    void *temp_2;

    if (func_00187CB8(arg0) == 0) {
        func_001854C8(&D_0036C700, 0x1F, arg0);
        temp_2 = func_001F4AD0(&D_00475480, 0);
        if ((temp_2 != 0) && (func_0013B500(temp_2, 0x33) != 0)) {
            func_00155ED8(temp_2, 5);
        }
        func_00186248(arg0);
    }
}
