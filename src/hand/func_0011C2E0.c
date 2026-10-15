// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern M2C_UNK D_00341EE0;
extern u32 D_0036B124;

void func_0011C2E0(s32 *arg0, s32 *arg1) {
    void *temp_v1;

    if ((u32) D_0036B124 >= 8U) {
        D_0036B124 = 0;
    }
    temp_v1 = (D_0036B124 * 8) + (char *)&D_00341EE0;
    if (arg0 != NULL) {
        *arg0 = M2C_FIELD(temp_v1, s32 *, 0);
    }
    if (arg1 != NULL) {
        *arg1 = M2C_FIELD(temp_v1, s32 *, 4);
    }
}
