// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Projects a point onto a piecewise-linear path: after seeking the cursor at the hint time, the point is tested against the cached
// segment (fast path); otherwise neighbouring segments are walked forward or backward until the projection falls inside one or the
// path ends. Returns the nearest point, the segment delta and the path time of the projection.
#include "../P2/state_position_ops.h"
struct SegmentPath {
    int index;
    float low;
    float high;
    unsigned char gapC[4];
    qword valueA;
    qword valueB;
    int count;
    unsigned char gap34[0x40 - 0x34];
    qword start[16];
    qword delta[16];
    float breaks[1];
};
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { asm("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
extern "C" int func_001EF170(SegmentPath *path, float t);
static inline qword Dot3(qword a, qword b)
{
    qword d, one;
    asm("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float LaneX(qword l)
{
    float g;
    asm("mtc1 %1,%0" : "=f"(g) : "r"(l));
    return g;
}
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    asm("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
extern "C" void func_001EF2A8(SegmentPath *path, float time, qword pos, qword *point, qword *delta, float *outTime)
{
    int index = func_001EF170(path, time);
    qword b = path->valueB;
    qword a = path->valueA;
    float along = LaneX(Dot3(PackedDifference(pos, a), b));
    float length = path->high - path->low;
    if (0.0f <= along && along <= length) {
        *point = AddScaled(a, b, VU_FLOAT(along));
        *delta = b;
        *outTime = path->low + along;
        return;
    }
    int forward = 0;
    int backward = 0;
    qword *starts = path->start;
    int best = -1;
    int last = path->count - 2;
    float t;
    for (;;) {
        float d = LaneX(Dot3(PackedDifference(pos, starts[index]), *(qword *)((char *)path + index * 16 + 0x140)));
        t = path->breaks[index + 1] - path->breaks[index];
        if (d < 0.0f) {
            if (forward) {
                index = best;
                break;
            }
            backward = 1;
            if (index <= 0) {
                t = 0.0f;
                break;
            }
            index--;
            __asm__ volatile("");
            best = index;
        } else {
            if (!(t < d)) {
                t = d;
                break;
            }
            if (backward) {
                index = best;
                t = 0.0f;
                break;
            }
            if (!(index < last))
                break;
            index++;
            forward = 1;
            best = index;
        }
    }
    qword *pd = &path->delta[index];
    *point = AddScaled(starts[index], *(qword *)((char *)path + index * 16 + 0x140), VU_FLOAT(t));
    *delta = *pd;
    *outTime = path->breaks[index] + t;
}
