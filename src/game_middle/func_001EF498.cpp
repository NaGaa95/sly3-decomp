// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
// Evaluates a piecewise-linear segment path: finds the segment containing the parameter (func_001EF170), clamps the
// local offset into the segment and returns start + delta * fraction and/or the segment's delta vector.
// The segment addresses go through int values, which keeps the VU temporary store ordered between the two loads.
struct SegmentPath {
    unsigned char prefix[0x40];
    qword start[16];
    qword delta[16];
    float breaks[1];
};
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { asm("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
extern "C" int func_001EF170(SegmentPath *path, float t);
static inline qword AddScaled(qword a, const qword &b, float s)
{
    qword r;
    VU_FLOAT t(s);
    asm("vadda.xyzw $ACC,%1,$vf0
	vmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(t.q));
    return r;
}
extern "C" void func_001EF498(SegmentPath *path, float parameter, qword *point, qword *delta)
{
    int index = func_001EF170(path, parameter);
    int next = index + 1;
    int breaks = (int)path->breaks;
    float base = *(float *)(breaks + (index << 2));
    float local = parameter - base;
    float span = *(float *)(breaks + (next << 2)) - base;
    if (local < 0.0f)
        local = 0.0f;
    else if (span < local)
        local = span;
    float fraction = local / span;
    if (point) {
        int ps = (int)&path->start[index];
        *point = AddScaled(*(qword *)ps, *(qword *)(int)&path->delta[index], fraction);
    }
    if (delta) {
        qword *pd = &path->delta[index];
        *delta = *pd;
    }
}
