// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

extern f32 D_0036BB98;

void func_0020BE68(void *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 temp_f3;

    temp_f3 = M2C_FIELD(arg0, f32 *, 0x18);
    temp_f0 = temp_f3 - (D_0036BB98 - M2C_FIELD(arg0, f32 *, 0x14));
    if (fparg0 < temp_f0) {
        temp_f0_2 = temp_f0 / temp_f3;
        temp_f2 = fparg0 / temp_f0_2;
        M2C_FIELD(arg0, f32 *, 0x18) = temp_f2;
        M2C_FIELD(arg0, f32 *, 0x14) = (f32) (D_0036BB98 - ((1.0f - temp_f0_2) * temp_f2));
    }
}
