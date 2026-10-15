// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern s32 D_0036DB9C;

void func_0018AAB8(void *arg0, void *arg1) {
    if (arg1 != NULL) {
        D_0036DB9C = M2C_FIELD(arg1, s32 *, 0x18);
    } else {
        D_0036DB9C = -1;
    }
    M2C_FIELD(arg0, void **, 0x4048) = arg1;
}
