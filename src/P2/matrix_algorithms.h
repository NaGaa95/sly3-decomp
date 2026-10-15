#ifndef SLY3_P2_MATRIX_ALGORITHMS_H
#define SLY3_P2_MATRIX_ALGORITHMS_H
#include "mat.h"
// Only the three real rotation basis packets are consumed. Output words0..2
// hold radians; word3 is Z's sign-extension residue from the packed EE ABI.
extern "C" qword func_0011D3C0(const MATRIX3 *rotation);
// Six real scalar floats arriveF12..F17; the output matrix pointer arrivesA0.
extern "C" void func_0011D8A8(float rx,float ry,float dxOffset,float dyOffset,
                             float sFar,float sNear,MATRIX4 *output);
#endif
