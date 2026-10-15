// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_0019AED0(void *arg0) {
    s32 var_a0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x10);
    var_a0 = 0;
    if ((M2C_FIELD(temp_v1, s32 *, 0x1118) != 0) || (M2C_FIELD(temp_v1, s32 *, 0x1104) != 0)) {
        var_a0 = 1;
    }
    return var_a0;
}
