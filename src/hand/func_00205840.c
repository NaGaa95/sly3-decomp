// Original callers at 0x205B28 and 0x207078 pass owner in a0 and the list in a1.
// Return the list entry with the greatest score; this operation does not access owner.
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern f32 D_00325780;

void *func_00205840(void *owner, void *arg1) {
    f32 temp_f0;
    f32 var_f1;
    void *var_v0;
    void *var_v1;

    var_v1 = M2C_FIELD(arg1, void **, 4);
    var_f1 = D_00325780;
    var_v0 = NULL;
    if (var_v1 != NULL) {
        do {
            temp_f0 = M2C_FIELD(var_v1, f32 *, 0x90);
            if (var_f1 < temp_f0) {
                var_f1 = temp_f0;
                var_v0 = var_v1;
            }
            var_v1 = M2C_FIELD(var_v1, void **, 0xAC);
        } while (var_v1 != NULL);
    }
    return var_v0;
}
