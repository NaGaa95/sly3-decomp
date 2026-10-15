// Retry mode transitions until the callbacks leave the state unchanged.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001A4CD0(void *, M2C_UNK);             /* extern */
M2C_UNK func_002389A0(void);                            /* extern */
s32 func_00238AA8(void *);                          /* extern */
s32 func_00238AD0(void *);                          /* extern */

void func_001A4E50(void *arg0) {
    s32 temp_17;

    func_002389A0();
loop_1:
    if (func_00238AA8(arg0) == 0) {
        temp_17 = M2C_FIELD(arg0, s32 *, 0x34);
        switch (temp_17) {                          /* irregular */
        case 0:
            if (M2C_FIELD(arg0, s32 *, 0x40) != 0) {
                func_001A4CD0(arg0, 1);
            } else if (func_00238AD0(arg0) != 0) {
                func_001A4CD0(arg0, -1);
            }
            break;
        case 1:
            if (func_00238AD0(arg0) != 0) {
                func_001A4CD0(arg0, -1);
            }
            break;
        }
        if (temp_17 != M2C_FIELD(arg0, s32 *, 0x34)) {
            goto loop_1;
        }
    }
}
