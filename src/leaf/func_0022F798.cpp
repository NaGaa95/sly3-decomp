// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Bounds the transformed path points and, for curved segments, their two control points.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct Path {
    char pad00[0x90]; M4 mat; int mode; char padD4[4]; int count; float *times; float *dist; qword *points;
    char padE8[0x130 - 0xE8]; qword *incoming, *outgoing;
};
extern "C" void func_0028FFD8(Path *path);
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
static inline qword TransformPoint(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline qword Rotate(const M4 &m, qword v)
{
    qword r = v;
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
            : "+j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword FromPrevious(VU_FLOAT scale, qword base, qword v)
{
    qword r = base;
    __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(r) : "j"(v), "j"(scale.q));
    return r;
}
// Keep the transformed next point live for the bounds test by reusing the scale register.
static inline qword FromNext(VU_FLOAT scale, qword base, qword v)
{
    qword r = scale.q;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%0x" : "+j"(r) : "j"(base), "j"(v));
    return r;
}
static inline qword Max(qword a, qword b)
{
    __asm__("vmax.xyz %0,%0,%1" : "+j"(a) : "j"(b));
    return a;
}
static inline qword Min(qword a, qword b)
{
    __asm__("vmini.xyz %0,%0,%1" : "+j"(a) : "j"(b));
    return a;
}
static inline void Extend(qword &maximum, qword &minimum, qword v)
{
    __asm__("vmax.xyz %0,%0,%2\n\tvmini.xyz %1,%1,%2" : "+j"(maximum), "+j"(minimum) : "j"(v));
}

extern "C" void func_0022F798(Path *p, qword *lo, qword *hi)
{
    func_0028FFD8(p);
    qword maximum = TransformPoint(p->mat, p->points[0]);
    qword minimum = maximum;
    if (p->mode == 0) {
        for (int i = 1; i < p->count; i++) {
            minimum = Min(minimum, TransformPoint(p->mat, p->points[i]));
            maximum = Max(maximum, TransformPoint(p->mat, p->points[i]));
        }
    } else {
        qword previous = maximum;
        for (int i = 0; i < p->count - 1; i++) {
            qword base = previous;
            previous = TransformPoint(p->mat, p->points[i + 1]);
            float third = (p->times[i + 1] - p->times[i]) * 0.33333334f;
            float negative = (p->times[i + 1] - p->times[i]) * -0.33333334f;
            Extend(maximum, minimum, FromPrevious(VU_FLOAT(third), base, Rotate(p->mat, p->outgoing[i])));
            Extend(maximum, minimum, FromNext(VU_FLOAT(negative), previous, Rotate(p->mat, p->incoming[i + 1])));
            minimum = Min(minimum, previous);
            maximum = Max(maximum, previous);
        }
    }

    *lo = minimum;
    *hi = maximum;
}
