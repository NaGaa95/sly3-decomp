// Advance the original four-phase timed sequence and publish its selected record index.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0011AEF8(s32);                             /* extern */
M2C_UNK func_00237220(void *, s32);                 /* extern */
M2C_UNK func_002378C0(void *, s32);                 /* extern */
extern f32 D_0036BB98;
extern f32 D_0036BB9C;

void func_002379E8(void *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_4;
    s32 var_5;

    if (func_0011AEF8(arg0 + 0x38) == 0) {
        temp_4 = M2C_FIELD(arg0, s32 *, 0x1C);
        if (temp_4 >= 2) {
            var_5 = M2C_FIELD(arg0, s32 *, 0x64);
            switch (var_5) {                        /* irregular */
            case 0:
                if (M2C_FIELD(arg0, f32 *, 0x6C) <= (D_0036BB98 - M2C_FIELD(arg0, f32 *, 0x68))) {
                    var_5 = 1;
                }
                break;
            case 1:
                temp_f2 = M2C_FIELD(arg0, f32 *, 0x70) * D_0036BB9C;
                temp_f0 = M2C_FIELD(arg0, f32 *, 0x74) + temp_f2;
                M2C_FIELD(arg0, f32 *, 0x74) = temp_f0;
                if ((f32) temp_4 <= temp_f0) {
                    temp_f0_2 = temp_f0 - temp_f2;
                    M2C_FIELD(arg0, f32 *, 0x74) = temp_f0_2;
                    var_5 = (((s32) temp_f0_2 ^ (temp_4 - 1)) == 0) ? 2 : 3;
                }
                break;
            case 2:
                if (M2C_FIELD(arg0, f32 *, 0x78) < 1.0f) {
                    var_5 = 3;
                }
                break;
            case 3:
                temp_f1 = M2C_FIELD(arg0, f32 *, 0x74) - (M2C_FIELD(arg0, f32 *, 0x70) * D_0036BB9C);
                M2C_FIELD(arg0, f32 *, 0x74) = temp_f1;
                if (temp_f1 <= ((f32) temp_4 * M2C_FIELD(arg0, f32 *, 0x78))) {
                    var_5 = 0;
                }
                break;
            }
            func_002378C0(arg0, var_5);
            func_00237220(arg0, (s32) M2C_FIELD(arg0, f32 *, 0x74));
        }
    }
}
