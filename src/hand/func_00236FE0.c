// Copy the resource descriptor and choose the original list insertion path.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011AD60(s32, M2C_UNK);                /* extern */
M2C_UNK func_0011AD80(M2C_UNK *, void *);           /* extern */
M2C_UNK func_0011ADA8(M2C_UNK *, void *);           /* extern */
extern M2C_UNK D_00479DA4;

void func_00236FE0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) M2C_FIELD(arg1, u16 *, 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(arg1, u16 *, 0xA);
    func_0011AD60(arg0 + 0x38, 0x10);
    if (M2C_FIELD(arg0, s32 *, 0x34) == 0) {
        func_0011ADA8(&D_00479DA4, arg0);
        return;
    }
    func_0011AD80(&D_00479DA4, arg0);
}
