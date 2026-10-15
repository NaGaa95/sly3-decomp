#ifndef SLY3_P2_VECTOR_MATRIX_INTRINSICS_H
#define SLY3_P2_VECTOR_MATRIX_INTRINSICS_H
#include "mat.h"
// Each operation consumes real packed XYZ and matrix-column inputs. XYZ is
// replaced while the tied vector operand preserves its actual fourth word.
// VU ACC.xyz is scratch: every block overwrites it before its first read.
// Architectural VF0.w is the constant one used by affine point translation.
// Installed EE GCC exposes no VU ACC clobber register or native VU arithmetic
// builtin. The accepted accum/accum1 registers belong to scalar HI/LO hardware.
// Keep the complete accumulator chain in one assembly operation: no ACC value
// is carried between helpers or observed by C++. ACC.w is neither read nor
// modified. Actual matrix/vector inputs and the preserved-W output constrain
// the operation; there is no memory fence, invented output or pinned register.
inline qword TransformPackedPoint(const MATRIX4 *matrix,qword vector) {
    const qword *columns=(const qword *)matrix;
    asm("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddaz.xyz $ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "+j"(vector) : "j"(columns[0]),"j"(columns[1]),"j"(columns[2]),"j"(columns[3]));
    return vector;
}
inline qword TransformPackedDirection(const MATRIX3 *matrix,qword vector) {
    const qword *columns=(const qword *)matrix;
    asm("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
        : "+j"(vector) : "j"(columns[0]),"j"(columns[1]),"j"(columns[2]));
    return vector;
}
#endif
