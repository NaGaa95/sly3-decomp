// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
void *func_00246E10(void *catalog, s32 id);
/* extern */ f32 func_00246E40(void *catalog, s32 id) {
    f32 var_f0;
    void *temp_v0;
    temp_v0 = func_00246E10(catalog, id);
    var_f0 = 0.0f;
    if (temp_v0 != NULL) {
        var_f0 = M2C_FIELD(temp_v0, f32 *, 0x50);
    }
    return var_f0;
}
