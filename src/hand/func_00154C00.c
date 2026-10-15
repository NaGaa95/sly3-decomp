// Dispatch activation to both components, or clear the matching virtual mode.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "actor_state_resource_api.h"
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"


void func_00154C00(void *arg0, void *arg1) {
    void *temp_2;

    if (arg1 != 0) {
        func_001B40F0(arg0 + 0x500, 5, arg1, 0);
        func_00209490(arg0 + 0x940, arg1);
    } else if (M2C_FIELD(arg0, s32 *, 0x508) == 5) {
        temp_2 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK), 0x31C)(arg0 + M2C_FIELD(temp_2, s16 *, 0x318), 0);
    }
}
