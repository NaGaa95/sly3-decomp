// Initialize the resource request and set the activation bit through the tagged flag word.
// Bit zero distinguishes an immediate flag word from a pointer to flag storage.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "activation_selector_api.h"
#include "m2c_prelude.h"

M2C_UNK func_001C8970(void *, M2C_UNK, M2C_UNK *, M2C_UNK); /* extern */
M2C_UNK func_0023C580(void *);                            /* extern */
extern M2C_UNK D_00344880;

void func_00170E20(void *arg0) {
    s32 temp_3;

    func_0023C580(arg0);
    func_001C8970(arg0, 2, &D_00344880, 0);
    M2C_FIELD(arg0, s32 *, 0x144) = 0;
    func_0023AAE8(M2C_FIELD(arg0, void **, 0x138), arg0, 0x73D, 0, (void **)((char *)arg0 + 0x13C));
    temp_3 = M2C_FIELD(arg0, s32 *, 0x3C);
    if ((temp_3 ^ 1) & 1) {
        M2C_FIELD(temp_3, s32 *, 0) = (s32) (M2C_FIELD(temp_3, s32 *, 0) | 2);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_3 | 2);
}
