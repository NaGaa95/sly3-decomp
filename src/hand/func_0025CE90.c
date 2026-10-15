// Actual callback context A0 is a real pointer; compare against dereferenced node-owner context pointer.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

s32 func_0025CE90(void *arg0, void *arg1) {
    s32 var_a2;
    void *temp_a1;

    var_a2 = 0;
    if (!(M2C_FIELD(arg1, s64 *, 0x18) & 0x10000)) {
        temp_a1 = M2C_FIELD(M2C_FIELD(arg1, void **, 4), void **, 0xDC);
        if (!(M2C_FIELD(temp_a1, s64 *, 0x70) & 4)) {
            var_a2 = temp_a1 != arg0;
        }
    }
    return var_a2;
}
