#ifndef SLY3_STATE_POSITION_OPS_H
#define SLY3_STATE_POSITION_OPS_H
#include "vector_intrinsics.h"

// Full XYZW subtraction, with two real packed inputs and four real outputs.
// In-place output is safe: VSUB reads both operands before writing its result.
// The normal VU MAC/status effects are retained; ACC and Q are unchanged.
inline qword PackedDifference(qword left, qword right) {
    qword result;
    asm("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(left), "j"(right));
    return result;
}

// GCC 2.95 cannot transport a scalar SF value through its VU j register class.
// This native packed carrier promises only its low X scalar. Y contains the
// real product left.y*right.y; Z/W are nonsemantic physical register residue.
// The carrier is never stored or read as four initialized C++ float fields.
// Its only consumer below reads X. Native guards prove that arbitrary ambient
// upper-register bits cannot reach the observed scalar result.
typedef qword VUXScalarCarrier;

// Dot product of the real X/Y lanes. Output may alias either actual input,
// because VMUL reads both operands before writing, and VADDY then uses that
// product. This updates the usual VU MAC/status flags; ACC and Q are unchanged.
inline VUXScalarCarrier PackedHorizontalDot(qword left, qword right) {
    VUXScalarCarrier scalar;
    asm("vmul.xy %0,%1,%2\n\tvaddy.x %0,%0,%0y"
        : "=j"(scalar) : "j"(left), "j"(right));
    return scalar;
}

// Consume only the real X input and transfer the resulting low 32 bits into
// GCC's scalar float/GPR carrier; its generated MTC1 reaches the normal FPU.
// The tied VF operand expresses its true read/write lifetime. VSQRT overwrites
// Q and its normal status effects; VADDQ updates its normal MAC/status flags.
// ACC is unchanged. No arbitrary hardware register is pinned or fenced.
inline float PackedSquareRootX(VUXScalarCarrier scalar) {
    float result;
    asm("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q\n\tqmfc2 %0,%1"
        : "=r"(result), "=j"(scalar) : "1"(scalar));
    return result;
}

inline float PackedHorizontalLength(qword vector) {
    return PackedSquareRootX(PackedHorizontalDot(vector, vector));
}
#endif
