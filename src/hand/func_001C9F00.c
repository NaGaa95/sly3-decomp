// Retry timed mode transitions until the callbacks leave the state unchanged.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001CA030(void *, M2C_UNK);             /* extern */
M2C_UNK func_001CAD10(void *, M2C_UNK);             /* extern */
s32 func_001CAFC8(void *);                          /* extern */
extern f32 D_0036BB98;

void func_001C9F00(void *arg0) {
    s32 temp_17;
    s32 temp_3;

    do {
        temp_17 = M2C_FIELD(arg0, s32 *, 0x1C4);
        if (func_001CAFC8(arg0) != 0) {
            func_001CA030(arg0, 1);
        }
        temp_3 = M2C_FIELD(arg0, s32 *, 0x1C4);
        switch (temp_3) {                           /* irregular */
        case 0:
            if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), f32 *, 8) >= 1.0f) {
                func_001CAD10(arg0, 1);
            }
            break;
        case 1:
            if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), f32 *, 8) < 1.0f) {
                func_001CAD10(arg0, 0);
            }
            break;
        case 2:
            if (((D_0036BB98 - M2C_FIELD(arg0, f32 *, 0x1CC)) > 0.25f) && (M2C_FIELD(arg0, f32 *, 0x200) == 0.0f)) {
                func_001CAD10(arg0, 0);
            }
            break;
        }
    } while (M2C_FIELD(arg0, s32 *, 0x1C4) != temp_17);
}
