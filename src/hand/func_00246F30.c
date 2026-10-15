// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"
extern s32 D_00349850[7];
s32 func_00246F30(u32 context, u32 index) {
    if (index >= 7U) return -1;
    return *(s32 *)(index * sizeof(s32) + (u32)D_00349850);
}
