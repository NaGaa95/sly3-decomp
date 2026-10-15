// Advance the enabled resource time and apply the interpolated output when global state permits.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
#include "approach_curve.h"
s32 func_001A9478(M2C_UNK *, M2C_UNK);
/* extern */ s32 func_0025AE28(M2C_UNK *);
/* extern */ void func_00261580(void *, int, f32);
/* extern */ s32 func_00261BD0(void *);
/* extern */ M2C_UNK func_00284C28(void *, f32);
/* extern */ s32 func_002852B0(void *);
/* extern */ extern const struct ApproachCurve D_0034A138;
extern f32 D_0036BB9C;
extern M2C_UNK D_00475480;
void func_002848D0(void *arg0) {
    f32 temp_f0;
    void *temp_4;
    if ((func_002852B0(arg0) != 0) && (func_001A9478(&D_00475480, -1) == 0) && (func_0025AE28(&D_00475480) == 0)) {
        if (M2C_FIELD(arg0, s32 *, 0x7CD4) == 1) {
            func_00284C28(arg0, M2C_FIELD(arg0, f32 *, 0x1C) + (M2C_FIELD(arg0, f32 *, 0x24) * D_0036BB9C));
        }
        temp_4 = M2C_FIELD(arg0, void **, 0x18);
        if ((temp_4 != 0) && (func_00261BD0(temp_4) != 0)) {
            temp_f0 = func_0011E598(M2C_FIELD(arg0, f32 *, 0x20), M2C_FIELD(arg0, f32 *, 0x1C), &D_0034A138, 0, D_0036BB9C);
            M2C_FIELD(arg0, f32 *, 0x20) = temp_f0;
            func_00261580(M2C_FIELD(arg0, void **, 0x18), 0x3E8, temp_f0);
        }
    }
}
