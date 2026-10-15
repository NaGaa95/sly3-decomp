// Euler angles from a real rotation basis, including both gimbal limits.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "vector_intrinsics.h"
#include "matrix_algorithms.h"
extern "C" float func_0011E560(float value,float limit);
extern "C" float func_002A3DE8(float value);
extern "C" float atan2f(float y,float x);
extern "C" qword func_0011D3C0(const MATRIX3 *matrix) {
    float tilt=func_002A3DE8(func_0011E560(-matrix->mat[0][2],1.0f));
    qword output;
    if(tilt<1.5706963539123535f) {
        if(-1.5706963539123535f<tilt) {
            float first=atan2f(matrix->mat[1][2],matrix->mat[2][2]);
            float third=atan2f(matrix->mat[0][1],matrix->mat[0][0]);
            union { qword vector;float scalar; } value;
            value.vector=PackVectorXYZ(first,tilt,third);
            output=value.vector;
        }else {
            float third=atan2f(-matrix->mat[1][0],-matrix->mat[2][0]);
            union { qword vector;float scalar; } value;
            value.vector=PackVectorXYZ(0.0f,tilt,third);
            output=value.vector;
        }
    }else {
        float third=atan2f(-matrix->mat[1][0],matrix->mat[2][0]);
        union { qword vector;float scalar; } value;
        value.vector=PackVectorXYZ(0.0f,tilt,third);
        output=value.vector;
    }
    return output;
}
