// Release the matching attachment and its associated resources, then clear the pointer.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0016F120(s32);                         /* extern */
M2C_UNK func_00172E60(void *, M2C_UNK);             /* extern */
M2C_UNK func_00183668(M2C_UNK);                     /* extern */
M2C_UNK func_002589D0(void *);                      /* extern */

void func_00172BA8(void *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x58);
    if ((temp_2 != NULL) && (arg1 == M2C_FIELD(temp_2, s32 *, 0xE0))) {
        if ((M2C_FIELD(arg0, s32 *, 0x50) != 0) || (M2C_FIELD(arg0, s32 *, 0x54) != 0)) {
            func_00172E60(arg0, 0);
            M2C_FIELD(arg0, s32 *, 0x54) = 0;
        }
        func_00183668(0);
        if (M2C_FIELD(arg0, s32 *, 0x40) != 0) {
            func_002589D0(M2C_FIELD(arg0, void **, 0x58) + 0x30);
            func_0016F120(M2C_FIELD(arg0, s32 *, 0x40));
        }
        M2C_FIELD(arg0, void **, 0x58) = NULL;
    }
}
