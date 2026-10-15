// Traverse global pointer slots and release the attachment on every nonempty referenced object.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00172D10(s32, M2C_UNK);                /* extern */
extern void **D_00344050[];
extern s32 D_00344068;

void func_001734E0(void) {
    s32 temp_4;
    s32 var_16;
    void *temp_2;

    var_16 = 0;
    if (D_00344068 > 0) {
        do {
            temp_2 = *D_00344050[var_16];
            if (temp_2 != NULL) {
                temp_4 = M2C_FIELD(temp_2, s32 *, 0x1108);
                if (temp_4 != 0) {
                    func_00172D10(temp_4, -1);
                }
            }
            var_16 += 1;
        } while (var_16 < D_00344068);
    }
}
