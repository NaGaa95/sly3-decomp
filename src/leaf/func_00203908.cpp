// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Picks a random launch point and direction in a cone around the surface normal of an object: the normal is sampled
// (func_0022E330), a side axis is built from it and the up axis, a random squared offset angle tilts the direction and a
// random distance along it gives the displaced position. Both results are optional.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword a, b, c; };
struct S;
extern "C" {
extern qword D_00317550, D_00317530;
float func_0022FC20(S *, float, float);
void func_0022E330(S *, qword *, qword *, float);
float func_0011E940(float, float);
qword func_0011FD70(float, float, float);
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
// quadword load that always reads the object again (the caller's memory may have changed)
static inline qword Reload(const qword &m)
{
    qword r;
    __asm__("lqc2 %0,%1" : "=j"(r) : "m"(m));
    return r;
}
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword Unit(qword v, qword len)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(len));
    return r;
}
static inline qword Normalize(qword v, qword fallback)
{
    qword len = Length(v);
    if (X(len) < 0.0001f)
        return fallback;
    return Unit(v, len);
}
static inline qword Combine(const M3 &m, qword v)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(v) : "j"(m.a), "j"(m.b), "j"(m.c));
    return v;
}
static inline qword ScalarToVU(float f)
{
    qword q;
    __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f));
    return q;
}
// a + b * s.x; "jV": a single-use load of b is folded into the asm by local-alloc, so reload emits it right before the asm
static inline qword AddScaled(qword a, qword b, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "jV"(b), "j"(s));
    return r;
}
extern "C" void func_00203908(S *self, qword *posOut, qword *dirOut, float g)
{
    U pos;
    M3 basis;
    U scalar, out;
    float x = func_0022FC20(self, g, 250.0f);
    func_0022E330(self, &pos.q, &basis.c, x);
    qword right = Normalize(Cross(basis.c, D_00317550), D_00317530);
    basis.a = Cross(right, Reload(basis.c));
    basis.b = right;
    float r = func_0011E940(-1.0f, 1.0f);
    float ar = __builtin_fabsf(r);
    qword dir = Combine(basis, func_0011FD70(r * ar * 1.8f, 1.0f, 0.0f));
    out.q = dir;
    if (posOut) {
        qword start = pos.q;
        float distance = ar * func_0011E940(0.0f, 25.0f);
        scalar.q = ScalarToVU(distance);
        *posOut = AddScaled(start, out.q, scalar.q);
    }
    if (dirOut)
        *dirOut = dir;
}
