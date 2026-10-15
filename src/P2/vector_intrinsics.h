#ifndef SLY3_P2_VECTOR_INTRINSICS_H
#define SLY3_P2_VECTOR_INTRINSICS_H
#include "mat.h"

// Packed EE vector arguments contain X/Y/Z in the first three 32-bit words.
// These reusable hardware operations preserve their IEEE single bits. GCC's
// native TI intrinsics materialize a zero temporary and different TI/SF copies;
// they cannot express the scalar register lifetimes used by the original ABI.
inline float PackedVectorX(qword vector) {
    float scalar;
    asm("mtc1 %1,%0" : "=f"(scalar) : "r"(vector));
    return scalar;
}
inline float PackedVectorY(qword vector) {
    float scalar;
    asm("prot3w %0,%1" : "=r"(scalar) : "r"(vector));
    return scalar;
}
inline float PackedVectorZ(qword vector) {
    float scalar;
    asm("pextuw %0,$0,%1" : "=r"(scalar) : "r"(vector));
    return scalar;
}

// Pack three real FPU scalar inputs into one GPR vector. MFC1 sign-extends each
// 32-bit value into its low 64 bits. PEXTLW interleaves the defined X/Y words;
// PCPYLD joins that low XY pair with Z's low 64 bits. The fourth output word is
// therefore Z's sign extension (0 or 0xffffffff), not a fourth float component.
// The two early-clobber outputs are scratch registers written before all three
// inputs have been consumed. No work register, fence or memory side effect is
// imposed. This is the established Sly 2 XYZ packing hardware primitive.
inline qword PackVectorXYZ(float x,float y,float z) {
    qword vector,scratch;
    asm("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
        : "=&r"(vector),"=&r"(scratch) : "f"(x),"f"(y),"f"(z));
    return vector;
}
#endif
