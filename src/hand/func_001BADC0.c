// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_001BADC0(void *arg0) {
    s32 var_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x218);
    var_v0 = 0;
    if ((temp_v1 != NULL) && (M2C_FIELD(temp_v1, f32 *, 0x88) > 0.7f)) {
        var_v0 = 1;
    }
    return var_v0;
}
