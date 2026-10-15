// Convert a packed direction using optional source and destination matrices.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "vector_matrix_intrinsics.h"
extern "C" void func_0011C6F8(MATRIX3 *,const MATRIX3 *);
extern "C" qword func_001C98A0(const MATRIX3 *source,const MATRIX3 *destination,qword value) {
    if(source)value=TransformPackedDirection(source,value);
    if(destination) {
        MATRIX3 inverse;
        func_0011C6F8(&inverse,destination);
        value=TransformPackedDirection(&inverse,value);
    }
    return value;
}
