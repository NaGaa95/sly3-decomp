// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0022E380: sample a path at a time value. func_0022F058 turns the time into a segment index plus the elapsed and
// duration of that segment. For a plain polyline (mode 0) the position is the blend of the two control points around the
// segment and the direction is the normalized segment vector; a spline path hands both outputs to func_00118558 (control
// points, outgoing/incoming tangents) and only normalizes the direction it produced.
// The normalize is written in both arms: the shared tail of the original is the result of cross-jumping after allocation.
typedef int qword __attribute__((mode(TI)));
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct VTE { short delta, pad; void *fn; };
struct PATH {
    char padC[0xC]; VTE *vt; char pad10[0xC0];
    int mode; int padD4, padD8, padDC, padE0; qword *points;
    char padE8[0x130 - 0xE8]; qword *incoming, *outgoing;
};
extern "C" {
int func_0022F058(PATH *, float, float *, float *);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, qword *);
}
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
static inline VV Sub(VV a, VV b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline VV VecCombo(VU_FLOAT f1, VV v1, VU_FLOAT f2, VV v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1), "j"(f2.q), "j"(v2));
    return r;
}
static inline VV Dot(VV a, VV b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline VV Root(VV a)
{
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(a));
    return a;
}
static inline VV Normalize(VV a)
{
    qword length = Root(Dot(a, a));
    __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "+j"(length) : "j"(a));
    return length;
}
extern "C" void func_0022E380(PATH *p, float g, qword *pos, qword *dir)
{
    float elapsed, duration;
    int i = func_0022F058(p, g, &elapsed, &duration);
    if (p->mode == 0) {
        if (pos) {
            float t = elapsed / duration;
            *pos = VecCombo(VU_FLOAT(1.0f - t), p->points[i], VU_FLOAT(t), p->points[i + 1]);
        }
        if (!dir) return;
        *dir = Normalize(Sub(p->points[i + 1], p->points[i]));
    } else {
        func_00118558(duration, elapsed, 1.0f, p->points[i], p->outgoing[i], p->points[i + 1], p->incoming[i + 1], pos, dir, 0);
        if (!dir) return;
        *dir = Normalize(*dir);
    }
}
