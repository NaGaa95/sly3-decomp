// Original four-row matrix scaling, including the actual fourth lanes.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "packed_matrix_intrinsics.h"
extern "C" MATRIX4 *func_0011D518(MATRIX4 *output,const MATRIX4 *input,qword scaleBits) {
    const qword *rows=(const qword *)input;
    qword *result=(qword *)output;
    qword first,scale;
    LoadScaleAndMultiply(scaleBits,rows[0],scale,first);
    result[0]=first;
    result[1]=ScalePackedMatrixRow(rows[1],scale);
    result[2]=ScalePackedMatrixRow(rows[2],scale);
    result[3]=ScalePackedMatrixRow(rows[3],scale);
    return output;
}
