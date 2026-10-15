// Search the cyclic 24-byte table for an acceptable record, stopping at the starting index.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

void *func_0017BFF0(void *);                              /* extern */
s32 func_0017C1C0(void *, s32);                     /* extern */

void func_0017C078(void *arg0) {
    s32 temp_18;
    s32 temp_2_2;
    s32 temp_hi;
    void *temp_2;

    temp_2 = func_0017BFF0(arg0);
    if (temp_2 != NULL) {
        temp_18 = M2C_FIELD(arg0, s32 *, 0x12C);
loop_2:
        temp_2_2 = M2C_FIELD(arg0, s32 *, 0x12C) + 1;
        M2C_FIELD(arg0, s32 *, 0x12C) = temp_2_2;
        temp_hi = temp_2_2 % (s32) M2C_FIELD(temp_2, s32 *, 0);
        M2C_FIELD(arg0, s32 *, 0x12C) = temp_hi;
        if ((temp_18 != temp_hi) && ((temp_hi >= 0) || (temp_hi < M2C_FIELD(temp_2, s32 *, 0)))) {
            if (func_0017C1C0(arg0, M2C_FIELD(temp_2, s32 *, 4) + (temp_hi * 0x18)) == 0) {
                goto loop_2;
            }
        }
    }
}
