// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Copy four aligned transform rows and mark the active owner dirty.
// The independent callback beginning at 0x0012F6B0 has its own vtable entry.
#include "m2c_prelude.h"

void func_0012F670(void *arg0, void *arg1) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 8);
    M2C_FIELD(arg0, s128 *, 0x20) = (s128) M2C_FIELD(arg1, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0x30) = (s128) M2C_FIELD(arg1, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x40) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
    M2C_FIELD(arg0, s128 *, 0x50) = (s128) M2C_FIELD(arg1, s128 *, 0x30);
    if (M2C_FIELD(temp_v1, s32 *, 0x90) == arg0) {
        M2C_FIELD(temp_v1, s16 *, 0x9A) = 3;
    }
}
