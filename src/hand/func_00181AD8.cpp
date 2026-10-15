// Reset the text reader and scan its characters to return the maximum rendered line width.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Scalar EE minimum/maximum use the original GCC native C++ operators.
#include "m2c_prelude.h"

static inline f32 ee_min(f32 left, f32 right) { return left <? right; }
static inline f32 ee_max(f32 left, f32 right) { return left >? right; }

extern "C" f32 func_00180A30(s32, s32);                        /* extern */
extern "C" M2C_UNK func_001813B0(void *);                            /* extern */
extern "C" s32 func_00181410(void *);                          /* extern */

extern "C" f32 func_00181AD8(void *arg0) {
    f32 var_f20;
    f32 var_f21;
    s32 temp_2;

    var_f20 = 0.0f;
    var_f21 = 0.0f;
    func_001813B0(arg0);
    while ((temp_2 = func_00181410(arg0)) != 0) {
        if (temp_2 == 10) {
            var_f20 = ee_max(var_f21, var_f20);
            var_f21 = 0.0f;
        } else {
            var_f21 += func_00180A30(M2C_FIELD(arg0, s32 *, 0x10), temp_2);
        }
    }
    var_f20 = ee_max(var_f21, var_f20);
    return var_f20;
}
