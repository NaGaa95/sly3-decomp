// Choose the original transition from the selected resource and its three global identities.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "actor_state_resource_api.h"
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
void func_0021FAE0(void *, int);
/* extern */ extern M2C_UNK D_00475480;
void func_0021FA38(void *arg0) {
    void *temp_2_2;
    void *temp_2;
    temp_2 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(temp_2, M2C_UNK (**)(void *), 0x54)(arg0 + M2C_FIELD(temp_2, s16 *, 0x50));
    temp_2_2 = func_001F4AD0(&D_00475480, 0);
    if (temp_2_2 != 0) {
        if (temp_2_2 == D_00370AC0) {
            func_0021FAE0(arg0, 0);
            return;
        }
        if (temp_2_2 == D_0036B250) {
            func_0021FAE0(arg0, 1);
            return;
        }
        if (temp_2_2 == D_0038AE90) {
            func_0021FAE0(arg0, 2);
        }
    }
}
