// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Search the object pointer array by the identifier at offset 0x18.
#include "m2c_prelude.h"
void *func_002419F0(void *arg0, s32 arg1) {
    s32 count = M2C_FIELD(arg0, s32 *, 0x94);
    s32 index = 0;
    if (count > 0) {
        do {
            void *entry = *(void **)((index * 4) + M2C_FIELD(arg0, s32 *, 0x98));
            ++index;
            if (M2C_FIELD(entry, s32 *, 0x18) == arg1) return entry;
        } while (index < count);
    }
    return NULL;
}
