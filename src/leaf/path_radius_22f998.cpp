// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0022F998: bounding radius of a path measured from its origin. mode 0 transforms every control point by the path's
// own basis (rotation only) and keeps the largest squared length; the spline mode also measures the two bezier handles
// (outgoing/incoming tangent scaled by a third of the segment time) of every segment.
// Matching notes: LengthSquared reads the dot with `mtc1 %1,%0 : "r"(d), "j"(d)` (allocation-only "j" input keeps the dot a VU
// pseudo, so the qmfc2 is a round-robin reload copy: $v0, $v0, $v1 as in the original). The loop-carried `previous` is copied out of `next` by the VU helper Move()
// (vmove): a plain `previous = next` is canonicalised by cse (previous has the lower pseudo number) so the second AddScaled would read vf4 instead of vf8.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M4 { qword a, b, c, d; };
struct PATH {
    char pad00[0x90]; M4 matrix;
    int mode, cyclic, count; float *times, *values; qword *points;
    char padE8[0x130 - 0xE8]; qword *incoming, *outgoing;
};
extern "C" {
void func_0028FFD8(PATH *);
}
static inline qword Rotate(const M4 &m, qword v)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(v) : "j"(m.a), "j"(m.b), "j"(m.c));
    return v;
}
static inline qword Dot(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline int Bits(qword v) { int b; __asm__("qmfc2.ni %0,%1" : "=r"(b) : "j"(v)); return b; }
static inline float FromBits(int b) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(b)); return f; }
static inline float LengthSquared(qword v) { qword d = Dot(v, v); float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d), "j"(d)); return f; }
static inline qword Scalar(float f)
{
    qword q;
    __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f));
    return q;
}
static inline qword RotateTo(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r) : "j"(m.a), "j"(m.b), "j"(m.c), "j"(v));
    return r;
}
static inline qword AddScaled(qword base, qword dir, qword k)
{
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%0,%2x" : "+j"(dir) : "j"(base), "j"(k));
    return dir;
}
static inline qword Move(qword a) { qword r; __asm__("vmove.xyzw %0,%1" : "=j"(r) : "j"(a)); return r; }
extern "C" float func_0022F998(PATH *p)
{
    U scalar;
    func_0028FFD8(p);
    float squared = 0.0f;
    if (p->mode == 0) {
        for (int i = 0; i < p->count; i++) {
            float length = LengthSquared(Rotate(p->matrix, p->points[i]));
            if (squared < length) squared = length;
        }
    } else {
        qword previous = RotateTo(p->matrix, p->points[0]);
        squared = LengthSquared(previous);
        for (int i = 0; i < p->count - 1; i++) {
            M4 *m = &p->matrix;
            qword old = previous;
            float interval = p->times[i + 1] - p->times[i];
            qword next = RotateTo(*m, p->points[i + 1]);
            previous = Move(next);
            qword k1 = Scalar(interval * (1.0f / 3.0f));
            scalar.q = k1;
            float l1 = LengthSquared(AddScaled(old, Rotate(*m, p->outgoing[i]), k1));
            if (squared < l1) squared = l1;
            qword k2 = Scalar(interval * (-1.0f / 3.0f));
            scalar.q = k2;
            float l2 = LengthSquared(AddScaled(next, Rotate(*m, p->incoming[i + 1]), k2));
            if (squared < l2) squared = l2;
            float l3 = LengthSquared(previous);
            if (squared < l3) squared = l3;
        }
    }
    return __builtin_sqrtf(squared);
}
