// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Rebuilds a path's per-segment horizontal directions and cumulative lengths: every segment direction is the
// difference of two consecutive points with its vertical component removed, normalized; breaks[] holds the
// running length at each point and the last direction repeats the previous one.
#include "../P2/state_position_ops.h"
struct SegmentPath {
    unsigned char prefix[0x30];
    int count;
    int pad[3];
    qword start[16];
    qword delta[16];
    float breaks[16];
};
union Direction { qword q; float f[4]; };
extern qword D_00317550;
// X lane = x*x' + y*y' + z*z' of the first three lanes.
static inline qword Dot3(qword a, qword b)
{
    qword d, one;
    asm("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=&j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
// vector * scalar (X lane of s).
static inline qword MulX(qword a, qword s)
{
    qword r;
    asm("vmulx.xyzw %0,%2,%0x" : "=j"(r) : "0"(s), "j"(a));
    return r;
}
// X lane = sqrt of the X lane.
static inline qword SquareRootX(qword d)
{
    qword l;
    asm("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float LaneX(qword l)
{
    float g;
    asm("mtc1 %1,%0" : "=f"(g) : "r"(l));
    return g;
}
// v / (X lane of l).
static inline qword DivideByX(qword v, qword l)
{
    qword r;
    asm("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l));
    return r;
}
extern "C" void func_001EF608(SegmentPath *path)
{
    float total = 0.0f;
    int count = path->count;
    qword prev = path->start[0];
    path->breaks[0] = 0.0f;
    Direction dir;
    int i;
    for (i = 1; i < count; i++) {
        qword *pd = &path->delta[i - 1];
        qword *ps = &path->start[i];
        qword cur = *ps;
        qword d = PackedDifference(cur, prev);
        prev = cur;
        qword up = D_00317550;
        d = PackedDifference(d, MulX(up, Dot3(d, up)));
        *pd = d;
        dir.q = d;
        qword length = SquareRootX(Dot3(dir.q, dir.q));
        float len = LaneX(length);
        *pd = DivideByX(dir.q, length);
        total += len;
        path->breaks[i] = total;
    }
    int last = path->count * 16 + (int)path;
    *(qword *)(last + 0x130) = *(qword *)(last + 0x120);
}
