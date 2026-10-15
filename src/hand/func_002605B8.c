// Format the start, end, and interval when the resource query succeeds.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00260758(void *, M2C_UNK);                 /* extern */
M2C_UNK func_00261250(void *);                            /* extern */
M2C_UNK func_00271530(void *, M2C_UNK, M2C_UNK *, s32); /* extern */
extern M2C_UNK D_00327ED0;

void func_002605B8(void *arg0) {
    func_00261250(arg0);
    if (func_00260758(arg0, 0x37B) != 0) {
        func_00271530(arg0 + 0x128, 4, &D_00327ED0, M2C_FIELD(arg0, s32 *, 0x120));
        func_00271530(arg0 + 0x12C, 4, &D_00327ED0, M2C_FIELD(arg0, s32 *, 0x124));
        func_00271530(arg0 + 0x130, 4, &D_00327ED0, M2C_FIELD(arg0, s32 *, 0x124) - M2C_FIELD(arg0, s32 *, 0x120));
    }
}
