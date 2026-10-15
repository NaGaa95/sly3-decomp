// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Copy a square submatrix into its transpose with an explicit row stride.
#include "m2c_prelude.h"

void func_0011DD48(s32 arg0, s32 arg1, const f32 *arg2, f32 *arg3) {
    const f32 *var_t0;
    f32 *var_t1;
    f32 temp_f0;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;

    var_t3 = 0;
    if (arg1 > 0) {
        var_t4 = 0;
        do {
            var_t2 = 0;
            if (arg1 > 0) {
                var_t1 = (f32 *)(var_t3 * sizeof(f32) + (u32)arg3);
                var_t0 = (const f32 *)(var_t4 * sizeof(f32) + (u32)arg2);
                do {
                    temp_f0 = *var_t0;
                    var_t0 += 1;
                    *var_t1 = temp_f0;
                    var_t1 = (f32 *)((u32)var_t1 + arg0 * sizeof(f32));
                    var_t2 += 1;
                } while (var_t2 < arg1);
            }
            var_t3 += 1;
            var_t4 += arg0;
        } while (var_t3 < arg1);
    }
}
