// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_00277588(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x130);
    if ((temp_v1 > 0) && ((temp_v1 < 3) || (temp_v1 == 6))) {
        return 1;
    }
    return 0;
}
