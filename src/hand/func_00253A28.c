// Reset each 32-byte record and then the three embedded record collections.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_002539E0(void *, void *);              /* extern */
M2C_UNK func_00254FE0(void *);                      /* extern */

void func_00253A28(void *arg0) {
    s32 var_18;
    void *var_17;

    var_18 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x4D0) > 0) {
        var_17 = arg0 + 0x4E0;
        do {
            var_18 += 1;
            func_00254FE0(var_17);
            var_17 += 0x20;
        } while (var_18 < M2C_FIELD(arg0, s32 *, 0x4D0));
    }
    func_002539E0(arg0, arg0 + 0xE20);
    func_002539E0(arg0, arg0 + 0xAE0);
    func_002539E0(arg0, arg0 + 0xC80);
}
