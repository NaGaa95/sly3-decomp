// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_0024DB68(void *arg0) {
    s32 *temp_v0;
    s32 var_v1;

    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x288), s32 **, 0x14);
    var_v1 = 0;
    if (temp_v0 != NULL) {
        var_v1 = *temp_v0 == 0;
    }
    return var_v1;
}
