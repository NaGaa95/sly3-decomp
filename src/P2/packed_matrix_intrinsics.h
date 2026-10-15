#ifndef SLY3_P2_PACKED_MATRIX_INTRINSICS_H
#define SLY3_P2_PACKED_MATRIX_INTRINSICS_H
#include "mat.h"
// Transfer the real 128-bit GPR operand to a VU register. The low word is the
// scalar float bit pattern; no upper word is synthesized or assumed zero.
inline qword PackedScalarToVU(qword bits) {
    qword value;
    asm("qmtc2.ni %1,%0" : "=j"(value) : "r"(bits));
    return value;
}
// Multiply all four float lanes by the actual low float lane of scale. This
// operation defines XYZ and W, and neither reads nor modifies VU ACC or Q.
// VMUL performs its normal VU MAC/status flag updates. Those flags are not
// preserved or exposed as C++ values by this primitive.
inline qword ScalePackedMatrixRow(qword row,qword scale) {
    qword result;
    asm("vmulx.xyzw %0,%2,%1x" : "=j"(result) : "j"(scale),"j"(row));
    return result;
}
// Convert actual GPR scalar bits and multiply one real XYZW row.
// Both outputs are meaningful: factor is the complete bit transfer consumed
// by later rows; first is the scaled row. Early-clobber on factor prevents
// overwriting the row input before it is read by the multiply.
// The multiply updates normal MAC/status flags; ACC and Q remain unchanged.
inline void LoadScaleAndMultiply(qword bits,qword row,qword &factor,qword &first) {
    qword f,r;
    asm("qmtc2.ni %2,%0\n\tvmulx.xyzw %1,%3,%0x"
        : "=&j"(f),"=j"(r) : "r"(bits),"j"(row));
    factor=f;first=r;
}
#endif
