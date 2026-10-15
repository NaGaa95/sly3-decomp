// Apply the seven requested mask bits to activate or deactivate their corresponding resources.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0012F3D0(s32);                         /* extern */
M2C_UNK func_0012F410(s32);                         /* extern */

void func_001ADCA0(void *arg0, s32 arg1) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x1AEC);
    if (temp_4 != 0) {
        if (arg1 & 1) {
            func_0012F3D0(temp_4);
        } else {
            func_0012F410(temp_4);
        }
        if (arg1 & 2) {
            func_0012F3D0(M2C_FIELD(arg0, s32 *, 0x1AF0));
        } else {
            func_0012F410(M2C_FIELD(arg0, s32 *, 0x1AF0));
        }
        if (arg1 & 4) {
            func_0012F3D0(M2C_FIELD(arg0, s32 *, 0x1AF4));
        } else {
            func_0012F410(M2C_FIELD(arg0, s32 *, 0x1AF4));
        }
        if (arg1 & 8) {
            func_0012F3D0(M2C_FIELD(arg0, s32 *, 0x1AF8));
        } else {
            func_0012F410(M2C_FIELD(arg0, s32 *, 0x1AF8));
        }
        if (arg1 & 0x10) {
            func_0012F3D0(M2C_FIELD(arg0, s32 *, 0x1AFC));
        } else {
            func_0012F410(M2C_FIELD(arg0, s32 *, 0x1AFC));
        }
        if (arg1 & 0x20) {
            func_0012F3D0(M2C_FIELD(arg0, s32 *, 0x1B04));
        } else {
            func_0012F410(M2C_FIELD(arg0, s32 *, 0x1B04));
        }
        if (arg1 & 0x40) {
            func_0012F3D0(M2C_FIELD(arg0, s32 *, 0x1B00));
            return;
        }
        func_0012F410(M2C_FIELD(arg0, s32 *, 0x1B00));
    }
}
