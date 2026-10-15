#ifndef SLY3_P2_MATRIX_POINT_SCALE_INTRINSICS_H
#define SLY3_P2_MATRIX_POINT_SCALE_INTRINSICS_H
#include "mat.h"
// Low float lane is semantic; other carrier words are non-semantic register
// residue, not zero or initialized floats. MFC1 sign-extends the low word into
// the GPR's low64 bits; its upper64 bits are preserved from that real register.
// QMTC2 copies that complete physical carrier. No C++ arithmetic interprets
// its higher words; copying their object bits retains native padding.
union MATRIX_SCALAR_CARRIER { qword carrier;float scalar; };
inline void MatrixScalarFromFloat(float value,MATRIX_SCALAR_CARRIER &scale) {
    qword bits,carrier;
    asm("mfc1 %1,%2\n\tqmtc2.ni %1,%0"
        : "=j"(carrier),"=&r"(bits) : "f"(value));
    scale.carrier=carrier;
}
// XYZ is affine point transformation; real inputW is multiplied by scale.x.
// VF0.w is architectural1. ACC.xyz is overwritten before use; ACC.w and Q
// are untouched. Arithmetic updates normal VU MAC/status flags, including
// the last W multiply. There is no claim to preserve all hardware flags.
// The tied real point operand retainsW until the final multiply defines it.
// Early-clobber keeps scale separate because XYZ is overwritten before the
// final scale.x read, even if point and factor have identical incoming bits.
inline qword TransformPackedPointScaleW(const MATRIX4 *matrix,qword value,qword scale) {
    const qword *columns=(const qword *)matrix;
    asm("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddaz.xyz $ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w\n\tvmulx.w %0,%0,%5x"
        : "+&j"(value) : "j"(columns[0]),"j"(columns[1]),"j"(columns[2]),"j"(columns[3]),"j"(scale));
    return value;
}
#endif
