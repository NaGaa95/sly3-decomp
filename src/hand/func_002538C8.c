// Update every 32-byte record, then the three embedded record collections.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00253878(void *, void *);              /* extern */
M2C_UNK func_00254C00(void *, void *);              /* extern */

void func_002538C8(void *arg0) {
    s32 var_18;
    void *var_17;

    var_18 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x4D0) > 0) {
        var_17 = arg0 + 0x4E0;
        do {
            func_00254C00(var_17, arg0);
            var_18 += 1;
            var_17 += 0x20;
        } while (var_18 < M2C_FIELD(arg0, s32 *, 0x4D0));
    }
    func_00253878(arg0, arg0 + 0xE20);
    func_00253878(arg0, arg0 + 0xAE0);
    func_00253878(arg0, arg0 + 0xC80);
}
