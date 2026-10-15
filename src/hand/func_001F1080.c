// Dispatch modes 5 through 8 to their corresponding embedded component.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0013A9E0(void *);                      /* extern */
M2C_UNK func_001B5910(void *);                      /* extern */
M2C_UNK func_001B88E0(void *);                      /* extern */
M2C_UNK func_001C2870(void *);                      /* extern */
M2C_UNK func_0024E2B8(void *);                            /* extern */

void func_001F1080(void *arg0) {
    s32 temp_3;

    func_0024E2B8(arg0);
    temp_3 = M2C_FIELD(arg0, s32 *, 0x1470);
    switch (temp_3) {                               /* irregular */
    case 5:
        func_001B88E0(arg0 + 0x320);
        return;
    case 6:
        func_001B5910(arg0 + 0x500);
        return;
    case 7:
        func_001C2870(arg0 + 0xE40);
        return;
    case 8:
        func_0013A9E0(arg0 + 0x10D0);
        return;
    }
}
