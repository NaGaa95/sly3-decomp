// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Path velocity apply: sample the path position/tangent for the source's parameter, scale the tangent by the source's
// speed word and store it as the target's velocity.
// Same routine as Sly 2 func_0019EA00 (offsets and callee differ in Sly 3).
#include "../P2/mat.h"
struct PathVelocitySource {
    unsigned char opaque00[0xC];
    void *path;
    float parameter;
    int speed;
};
struct PathVelocityTarget {
    unsigned char opaque00[0x10];
    qword velocity;
    unsigned char opaque20[0x54 - 0x20];
    int word54;
    unsigned char opaque58[0x6C - 0x58];
    int flags;
};
union PathVelocityVector { qword q; float f[4]; };
static inline qword ScalarToVU(int value)
{
    qword result;
    asm("qmtc2.ni %1,%0" : "=j"(result) : "r"(value));
    return result;
}
static inline qword ScaleRow(qword row, qword scale)
{
    qword result;
    asm("vmulx.xyzw %0,%2,%1x" : "=j"(result) : "j"(scale), "j"(row));
    return result;
}
extern "C" void func_0022E330(void *path, float parameter, void *position, qword *tangent);
extern "C" void func_001BFA18(PathVelocitySource *source, PathVelocityTarget *target)
{
    PathVelocityVector direction;
    PathVelocityVector factor;
    func_0022E330(source->path, source->parameter, target, &direction.q);
    // The speed word takes over the source pointer's variable once the path call has used it.
    source = (PathVelocitySource *)source->speed;
    factor.q = ScalarToVU((int)source);
    target->velocity = ScaleRow(direction.q, factor.q);
    target->word54 = 0;
    target->flags &= ~4;
}
