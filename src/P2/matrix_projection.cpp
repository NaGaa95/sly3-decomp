// Scalar perspective projection, recovered from original inputs and Sly 2.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "matrix_algorithms.h"
extern "C" void *memset(void *pv,int b,unsigned int cb);
extern "C" void func_0011D8A8(float rx,float ry,float dxOffset,float dyOffset,
                             float sFar,float sNear,MATRIX4 *pmat) {
    memset(pmat,0,sizeof(MATRIX4));
    float zScale=(sFar+sNear)/(sFar-sNear);
    float zTrans=sFar*(1.0f-zScale);
    pmat->mat[0][0]=rx;
    pmat->mat[2][3]=1.0f;
    pmat->mat[2][0]=dxOffset;
    pmat->mat[1][1]=ry;
    pmat->mat[2][1]=dyOffset;
    pmat->mat[2][2]=zScale;
    pmat->mat[3][2]=zTrans;
}
