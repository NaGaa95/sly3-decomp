#include "m2c_prelude.h"
#include "sequence_activity_api.h"

void func_001E5E10(void *arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = arg1;
    if (var_s0 == -1) {
        var_s0 = M2C_FIELD(arg0, s32 *, 0x18);
    }
    M2C_FIELD(func_001E5F60(arg0, 1), s32 *, 4) = var_s0;
}
