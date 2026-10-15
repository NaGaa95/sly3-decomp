// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
#include "animation_record_lookup_api.h"

f32 func_001368E0(struct LookupLibrary *library, int key) {
    f32 *temp_v0;
    f32 var_f0;

    temp_v0 = (f32 *)func_00136880(library, key);
    var_f0 = 0.0f;
    if (temp_v0 != NULL) {
        var_f0 = *temp_v0;
    }
    return var_f0;
}
