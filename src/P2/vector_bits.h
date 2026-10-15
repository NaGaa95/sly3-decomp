#ifndef SLY3_P2_VECTOR_BITS_H
#define SLY3_P2_VECTOR_BITS_H
#include "mat.h"
// EE GCC models packed128-bit vector arguments in general registers. It has
// native lane permutation intrinsics but no TI-to-SF bitcast intrinsic. Tying
// the same physical register across modes reinterprets its low32 bits as one
// IEEE single; the compiler emits required register-file transfers normally.
// The constraint consumes the actual input and defines its actual low lane.
// There is no instruction template, fixed register, clobber or memory barrier.
inline float VectorX(qword vector) {
    float scalar;
    asm("" : "=r"(scalar) : "0"(vector));
    return scalar;
}
inline float VectorY(qword vector) {
    return VectorX(__builtin_prot3w(vector));
}
#endif
