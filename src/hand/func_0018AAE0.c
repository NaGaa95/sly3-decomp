// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern s32 D_0036DBA0;

void func_0018AAE0(void *arg0, void *arg1) {
    if (arg1 != NULL) {
        D_0036DBA0 = M2C_FIELD(arg1, s32 *, 0x18);
    } else {
        D_0036DBA0 = -1;
    }
    M2C_FIELD(arg0, void **, 0x404C) = arg1;
}
