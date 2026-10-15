// Recovered packed-vector angle query: atan2f(Y,X), with the EE lane ABI.
// SLY3_CFLAGS: -Os -fno-schedule-insns -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "vector_bits.h"
extern "C" float func_002A3EE8(float,float);
extern "C" float func_001205C8(qword value) {
    float y=VectorY(value);
    float x=VectorX(value);
    return func_002A3EE8(y,x);
}
