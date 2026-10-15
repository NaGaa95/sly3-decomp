// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

f32 func_002575C0(void *arg0) {
    f32 var_f0;
    void *temp_a0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x11D4);
    var_f0 = 1.0f;
    if (temp_v1 != NULL) {
        temp_a0 = M2C_FIELD(temp_v1, void **, 0x90);
        if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, s32 *, 0) == 1)) {
            var_f0 = M2C_FIELD(temp_a0, f32 *, 0x20);
        }
    }
    return var_f0;
}
