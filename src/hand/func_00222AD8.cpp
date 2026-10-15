// Update the resource transform and clamp its elapsed-time fraction with the original scalar minimum.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Scalar EE minimum/maximum use the original GCC native C++ operators.
#include "m2c_prelude.h"
static inline f32 ee_min(f32 left, f32 right) {
    return left <? right;
}
static inline f32 ee_max(f32 left, f32 right) {
    return left >? right;
}
extern "C" void func_00261580(void *, int, f32);
/* extern */ extern "C" void func_002625D8(void *, const void *, s128);
/* extern */ extern f32 D_0036BB98;
extern "C" void func_00222AD8(void *arg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 var_f0;
    f32 now;
    void *temp_4;
    temp_4 = M2C_FIELD(arg0, void **, 0x30);
    if (temp_4 != 0) {
        func_002625D8(temp_4, M2C_FIELD(arg0, void **, 0x3C), M2C_FIELD(arg0, s128 *, 0x60));
        temp_f0 = M2C_FIELD(arg0, f32 *, 0x34);
        temp_f1 = M2C_FIELD(arg0, f32 *, 0x38);
        now = D_0036BB98;
        if (temp_f0 == temp_f1) {
            var_f0 = 0.0f;
        }
        else {
            var_f0 = (now - temp_f0) / (temp_f1 - temp_f0);
        }
        func_00261580(M2C_FIELD(arg0, void **, 0x30), 0x776, ee_min(1.0f, var_f0));
    }
}
