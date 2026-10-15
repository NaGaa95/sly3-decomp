// Traverse the original 12-byte records and update each nonempty entry.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001C7938(void *);                            /* extern */
M2C_UNK func_0021AB48(void *, s32 *);               /* extern */

void func_0021AD78(void *arg0) {
    s32 *temp_5;
    s32 var_17;

    func_001C7938(arg0);
    if (M2C_FIELD(arg0, s32 *, 0x50) != 0) {
        var_17 = 0;
        if (M2C_FIELD(arg0, s32 *, 0x4C) > 0) {
            do {
                temp_5 = M2C_FIELD(arg0, s32 *, 0x50) + (var_17 * 0xC);
                if (*temp_5 != 0) {
                    func_0021AB48(arg0, temp_5);
                }
                var_17 += 1;
            } while (var_17 < M2C_FIELD(arg0, s32 *, 0x4C));
        }
    }
}
