// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "vector_intrinsics.h"
struct CylinderLimits { float radius,lower,upper; };
static inline qword PackedToVU(qword value)
{
    qword result;
    __asm__("qmtc2.ni %1,%0" : "=j"(result) : "r"(value));
    return result;
}
static inline qword SquaredLengthXY(qword value)
{
    qword result;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y"
            : "=j"(result) : "j"(value));
    return result;
}
static inline qword SquareRootX(qword value)
{
    qword result;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q"
            : "=j"(result) : "j"(value));
    return result;
}
static inline float LowFloat(qword value)
{
    float result;
    __asm__("qmfc2.ni %0,%1" : "=r"(result) : "j"(value));
    return result;
}
extern "C" int func_0011FB88(const CylinderLimits *limits,qword point)
{
    qword value=PackedToVU(point);
    float radius=limits->radius;
    float distance=LowFloat(SquareRootX(SquaredLengthXY(value)));
    int outside=radius<distance;
    if(outside) return 0;
    float height=PackedVectorZ(value);
    if(height<limits->lower || limits->upper<height) return 0;
    return 1;
}
