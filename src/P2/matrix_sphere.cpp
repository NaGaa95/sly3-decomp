// Affine XYZ transform and scale of the actual fourth component.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "matrix_point_scale_intrinsics.h"
extern "C" float func_0011DF08(const MATRIX4 *);
extern "C" qword func_0011D5C8(const MATRIX4 *matrix,qword value) {
    MATRIX_SCALAR_CARRIER scale;
    MatrixScalarFromFloat(func_0011DF08(matrix),scale);
    return TransformPackedPointScaleW(matrix,value,scale.carrier);
}
