#ifndef SLY3_P2_ROTATION_MATRIX_INTRINSICS_H
#define SLY3_P2_ROTATION_MATRIX_INTRINSICS_H
#include "mat.h"
// Three semantic floats and one non-semantic padding word per rotation column.
// Only XYZ participates in multiplication. Each partial VU result has an
// unspecified, non-semantic fourth word. Padding is copied as object bytes;
// it is never read as an initialized fourth float, or promised zero/preserved.
struct ROTATION_COLUMN { float x,y,z; } __attribute__((aligned(16)));
struct ROTATION_MATRIX { ROTATION_COLUMN columns[3]; };
inline void MultiplyRotation(ROTATION_MATRIX *output,const ROTATION_MATRIX *left,const ROTATION_MATRIX *right) {
    ROTATION_MATRIX result;
    const qword *a=(const qword *)left,*b=(const qword *)right;
    qword *c=(qword *)&result;
    qword first,second,third;
    // VU ACC.xyz is overwritten before the first read in each atomic XYZ chain.
    // This compiler exposes no VU ACC clobber name; no ACC value crosses blocks.
    asm("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(first) : "j"(a[0]),"j"(a[1]),"j"(a[2]),"j"(b[0]));
    asm("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(second) : "j"(a[0]),"j"(a[1]),"j"(a[2]),"j"(b[1]));
    asm("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(third) : "j"(a[0]),"j"(a[1]),"j"(a[2]),"j"(b[2]));
    ((qword *)output)[0]=c[0]=first;
    ((qword *)output)[1]=c[1]=second;
    ((qword *)output)[2]=c[2]=third;
}
#endif
