// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// New Sly 3 code: two-bone IK (law of cosines for the elbow, then aim the chain root at the target).
// MATRIX3 operator* is the Sly 2 one (src/hand/func_0021CB18.cpp: left rows in qword locals, VU_VECTOR4 row temps, NRV),
// which gives the target's double row stores; axis is a VECTOR so it takes the freed temp slot at 0x30.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3() {} M3(const M3 &m) { r[0] = m.r[0]; r[1] = m.r[1]; r[2] = m.r[2]; } M3 &operator=(const M3 &m) { r[0] = m.r[0]; r[1] = m.r[1]; r[2] = m.r[2]; return *this; } };
struct M4 { U r[4]; };
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
#define Q(v) (*(qword *)&(v))
struct VTE { short d; short pad; void *pfn; };
struct OBJ { VTE *pvt; };
struct LO { M4 mat; unsigned char pad40[0xA0 - 0x40]; LO *parent; int stamp; };
struct IK {
    int n0; LO *plo4; int pad8[2]; qword posRoot; qword q20; LO *plo30; float a; float b; float g3C; qword axis;
    M3 m50; LO *plo80; int pad84[3]; qword q90; float gA0; OBJ *pA4; float *pA8; int padAC; M3 mB0;
};
struct G { unsigned char pad[0x44F4]; int stamp; };
extern "C" {
extern G D_00475480;
qword func_0028E910(int n, LO *plo, qword q);
M3 func_0011C8C0(qword axis, float g);
float func_00120080(qword a, qword b, qword *paxis);
float func_002A3CE8(float g);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Transform(const M4 &m, qword v) { qword r; __asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w" : "=j"(r) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(v)); return r; }
struct VU_VECTOR4 { qword qw; };
inline M3 operator*(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.r[0].q;
    qword qwL1 = matL.r[1].q;
    qword qwL2 = matL.r[2].q;
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[0].q));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[1].q));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[2].q));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float GetX(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword Sqrt(qword v) { qword r; __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(r) : "j"(v)); return r; }
static inline float Len(qword v)
{
    return GetX(Sqrt(Dot(v, v)));
}
static inline qword Normalize(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "j"(d));
    __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
static inline void SetMat3(LO *plo, const M3 &m)
{
    plo->mat.r[0].q = m.r[0].q; plo->mat.r[1].q = m.r[1].q; plo->mat.r[2].q = m.r[2].q;
    plo->mat.r[0].i[3] = 0; plo->mat.r[1].i[3] = 0; plo->mat.r[2].i[3] = 0;
}
static inline float Clamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
extern "C" void func_001A5FF0(IK *p)
{
    qword posRoot = p->posRoot;
    LO *ploEnd = p->plo4->parent;
    qword d = Sub(func_0028E910(p->n0, ploEnd, p->q20), posRoot);
    float a = p->a, b = p->b;
    float len = Len(d);
    float c = Clamp((len * len - (a * a + b * b)) / (2.0f * a * b), -1.0f, 1.0f);
    float ang0 = func_002A3CE8(c) - p->g3C;
    M3 m = func_0011C8C0(p->axis, ang0);
    SetMat3(p->plo30, m * p->m50);
    qword q = p->q90;
    SetMat3(p->plo4, p->mB0);
    for (LO *plo = p->plo80; plo != ploEnd; plo = plo->parent)
        q = Transform(plo->mat, q);
    VECTOR axis;
    float ang = func_00120080(Sub(q, posRoot), d, &Q(axis));
    M3 mr = func_0011C8C0(Q(axis), ang);
    if (p->pA4)
        ((void (*)(void *, float *, int, float, float))p->pA4->pvt[2].pfn)((char *)p->pA4 + p->pA4->pvt[2].d, &p->gA0, 0, *p->pA8, 0.0f);
    M3 m3 = func_0011C8C0(Normalize(d), p->gA0);
    M3 m4 = m3 * mr * p->mB0;
    SetMat3(p->plo4, m4);
    int n = ++D_00475480.stamp;
    LO *p4 = p->plo4, *p30 = p->plo30;
    p4->stamp = n;
    p30->stamp = n;
}
