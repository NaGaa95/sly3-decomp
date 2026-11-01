// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTENT { short delta, pad; void *(*pfn)(void *, ...); };
struct LO { char pad[0xC]; VTENT *pvt; };
struct X134 { char pad[8]; float g; };
struct X113C { char pad[0x1C]; float g1C; char pad20[0x20]; float g40; };
struct X11B4 { char pad[0x4AC]; void *p4AC; };
struct X8 { char pad[0x30]; qword v; };
struct OW
{
    char pad0[0x134];
    X134 *p134;
    char pad138[0x1A0 - 0x138];
    qword v1A0;
    float g1B0[3];
    float g1BC;
    qword amat[3];
    char pad1F0[0x110C - 0x1F0];
    float g110C;
    char pad1110[0x113C - 0x1110];
    X113C *p113C;
    char pad1140[4];
    int n1144;
    char pad1148[0x11B4 - 0x1148];
    X11B4 *p11B4;
};
struct P
{
    OW *powner;
    void *p4;
    X8 *p8;
    int state;
    int pad10;
    int state2;
    float t18;
    char pad1C[0x44 - 0x1C];
    LO *p44;
    char pad48[0x60 - 0x48];
    qword v60;
    qword v70;
    qword v80;
    qword v90;
    qword vA0;
    float gB0;
};
struct POLY { float a, b, c; };
struct LM { float low, high; };
struct SMP { float a, b, c; };
struct CLOCK { float t, dt; };
extern "C" {
extern LM D_00341FF0;
extern qword D_00317560;
extern CLOCK g_clock;
int func_0017E810(P *p);
void func_0024E920(OW *p, void *pv);
void func_0024E878(OW *p, float g);
float func_0011E3B8(float g);
qword func_0011FD70(float rad, float r, float z);
void func_001C1550(OW *p, X8 *p8, void *p4);
qword func_0024F278(OW *p, X113C *px, float g);
float func_0011E598(float a, float b, float dt, const SMP *psmp, float *pdg);
qword func_0028BCD0(void *p, int n, qword pos);
qword func_001C9428(void *p, int n, qword q);
qword func_001C94E8(void *p, int n, qword q);
void func_00118558(float g0, float g1, float g2, qword a, qword b, qword c, qword d, qword *pa, qword *pb, int n);
}
float GLimitAbs(float g, float gMax);
extern "C" float D_0036BB9C;
static const POLY D_003217E0 __attribute__((aligned(16))) = {-1.0f, 2.0f, 0.0f};
static const POLY D_003217F0 __attribute__((aligned(16))) = {1.0f, 0.0f, 0.0f};
static const SMP D_00321800 __attribute__((aligned(16))) = {2000.0f, 500.0f, 0.1f};
union UQ { float f[4]; qword q; };
static const UQ D_00321810 = {{0.0f, 0.0f, -2275.0f, 0.0f}};
static inline float Evaluate(const POLY *p, float t) { return p->a + t * (p->b + t * p->c); }
static inline float Limit(float f, LM *p) { float low = p->low, high = p->high, r; if (f < low) r = low; else if (high < f) r = high; else r = f; return r; }
/* lane reads: the volatile one keeps the gB0 load ahead of it; GetXv differs only in text so CSE keeps two reads */
static inline float GetXvv(qword q) { float x; __asm__ __volatile__("qmfc2.ni %0, %1" : "=r"(x) : "j"(q)); return x; }
static inline float GetXv(qword q) { float x; __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(q)); return x; }
static inline float GetX(qword q) { float x; __asm__("qmfc2.ni %0, %1" : "=r"(x) : "j"(q)); return x; }
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } /* "r,m": the lw becomes a reload, as in the target */ VU_FLOAT(const float *pf) { __asm__("qmtc2.ni %1,%0" : "=j,!r"(q) : "r,m"(*(const int *)pf)); } };
static inline qword Scale(qword v, VU_FLOAT k) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(k.q)); return r; }
static inline qword MAdd(qword p, qword v, VU_FLOAT k) { qword r; __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p), "j"(v), "j"(k.q)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword Len2(qword v)
{
    qword d;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword ScaleX(qword v, qword k) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(k)); return r; }
static inline qword XfmT(const qword *am, qword v)
{
    qword r, one, t0, t1, t2;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
            "vadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\t"
            "vaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(r), "=&j"(one), "=&j"(t0), "=&j"(t1), "=&j"(t2) : "0"(am[0]), "j"(am[1]), "j"(am[2]), "j"(v));
    return r;
}
static inline qword DivLen(qword c, qword l) { qword t; __asm__ __volatile__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(t) : "j"(c), "j"(l)); return t; }
static inline void VNormalize(qword *pr, qword c, qword k)
{
    qword l;
    register qword t __asm__("vf1"); /* register pin (the only one): result reg of the normalize */
    float gl;
    l = Len(c);
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    if (gl < 1e-4f) {
        __asm__("" : "+r"(k));
        t = k;
    } else {
        __asm__ __volatile__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(t) : "j"(c), "j"(l));
    }
    *pr = t;
}
static inline qword Position(LO *o)
{
    VTENT *e = &o->pvt[36];
    return *(qword *)((char *)e->pfn((char *)o + e->delta) + 0x30);
}
extern "C" void func_0017EF78(P *p)
{
    switch (p->state)
    {
    case 1:
    case 4:
    {
        X134 *p134 = p->powner->p134;
        float gScale = Limit(Evaluate(&D_003217E0, p134->g), &D_00341FF0);
        if (func_0017E810(p))
        {
            func_0024E920(p->powner, p->powner->p11B4->p4AC);
        }
        else if (p134->g > 0.0f)
        {
            float gRate = Limit(Evaluate(&D_003217F0, p134->g), &D_00341FF0);
            float gd = func_0011E3B8(p->powner->g110C - p->powner->g1BC);
            float gMax = D_0036BB9C * 5.0f;
            float g = GLimitAbs(gd, gRate * gMax);
            func_0024E878(p->powner, p->powner->g1BC + g);
        }
        OW *powner = p->powner;
        powner->v1A0 = func_0011FD70(powner->g110C + 3.1415927f, gScale * GetX(Len2(p->p8->v)) * powner->p113C->g40, 0.0f);
        p->powner->v1A0 = XfmT(p->powner->amat, p->powner->v1A0);
        p->powner->n1144 = -1;
        func_001C1550(p->powner, p->p8, p->p4);
        break;
    }
    case 3:
    {
        OW *powner = p->powner;
        powner->v1A0 = Scale(func_0024F278(powner, powner->p113C, powner->p113C->g1C), VU_FLOAT(-1.0f));
        break;
    }
    }
    switch (p->state2)
    {
    case 0:
    {
        qword vel, pos;
        float dg;
        if (p->gB0 == 125.0f)
            dg = 0.0f;
        else
            p->gB0 = func_0011E598(p->gB0, 125.0f, D_0036BB9C, &D_00321800, &dg);
        qword vNew = MAdd(p->vA0, MAdd(D_00321810.q, p->vA0, VU_FLOAT(-2.5f)), VU_FLOAT(D_0036BB9C));
        float h = D_0036BB9C * 0.5f;
        vel = vNew;
        pos = MAdd(p->v80, Add(p->vA0, vel), VU_FLOAT(h));
        void *pv;
        {
            VTENT *e = &p->p44->pvt[37];
            pv = e->pfn((char *)p->p44 + e->delta, 0);
        }
        qword posObj = Position(p->p44);
        qword q = func_0028BCD0(pv, 0, posObj);
        qword d = Sub(pos, posObj);
        qword l = Len(d);
        const qword *pk = &D_00317560;
        p->v90 = d;
        if (GetXv(l) < 1e-4f)
            p->v90 = *pk;
        else
            p->v90 = DivLen(d, l);
        float gR = p->gB0;
        if (gR < GetXvv(l))
        {
            qword n = p->v90;
            VU_FLOAT fr(p->gB0);
            vel = Add(Sub(vNew, ScaleX(n, Dot(vNew, n))), ScaleX(n, Dot(q, n)));
            vel = MAdd(vel, n, VU_FLOAT(&dg));
            pos = MAdd(posObj, n, fr);
        }
        p->v80 = pos;
        p->vA0 = vel;
        break;
    }
    case 1:
    {
        X11B4 *psw = p->powner->p11B4;
        qword q1 = func_001C9428(psw->p4AC, 0, p->v60);
        qword q2 = func_001C94E8(psw->p4AC, 0, p->v70);
        func_00118558(0.35f - (g_clock.t - p->t18) + g_clock.dt, g_clock.dt, 1.0f, p->v80, p->vA0, q1, q2, &p->v80, &p->vA0, 0);
        VNormalize(&p->v90, p->vA0, p->v90);
        break;
    }
    }
}
