// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0022E148: sample a path at a time value like func_0022E380, but in the world frame of the path: the position and the
// direction are transformed by the path's virtual-slot-36 matrix (the matrix is copied first because the sampling calls
// run between its uses). Mode 0 is the polyline blend / segment vector, otherwise func_00118558 builds both outputs from the
// spline control points and tangents. The direction is rotated by the matrix and normalized in both arms (the shared tail
// of the original is the result of cross-jumping after allocation).
typedef int qword __attribute__((mode(TI)));
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct M4 { qword r[4]; };
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
static inline VV TransformPoint(const M4 &m, VV v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline VV Rotate(const M4 &m, VV v)
{
    qword r = v;
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z"
            : "+j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
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
extern "C" void func_0022E148(PATH *p, float g, qword *pos, qword *dir)
{
    float elapsed, duration;
    int i = func_0022F058(p, g, &elapsed, &duration);
    M4 m = *((M4 *(*)(void *))p->vt[36].fn)((char *)p + p->vt[36].delta);
    if (p->mode == 0) {
        if (pos) {
            float t = elapsed / duration;
            *pos = TransformPoint(m, VecCombo(VU_FLOAT(1.0f - t), p->points[i], VU_FLOAT(t), p->points[i + 1]));
        }
        if (!dir) return;
        *dir = Normalize(Rotate(m, Sub(p->points[i + 1], p->points[i])));
    } else {
        func_00118558(duration, elapsed, 1.0f, p->points[i], p->outgoing[i], p->points[i + 1], p->incoming[i + 1], pos, dir, 0);
        if (pos) *pos = TransformPoint(m, *pos);
        if (!dir) return;
        *dir = Normalize(Rotate(m, *dir));
    }
}
