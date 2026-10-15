// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_001633E0(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x190) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x190) = arg1;
        if (arg1 == 1) {
            M2C_FIELD(arg0, s32 *, 0x198) = -1;
        }
    }
}
