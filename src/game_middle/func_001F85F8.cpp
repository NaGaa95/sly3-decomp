// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001F85F8: spray up to cRequested objects of a kind around posSeed (port of the Sly 2 relative func_001C6FD8).
// Allocation notes: Add uses the g++ named return value, so the vadd writes straight into posTrial (no copy that gcse
// copy propagation could fold into the asm temp); posTrial keeps its own pseudo, numbered before the PosAt base
// temp, which gives the original spill slots (posTrial 0x80, base 0x90). posBase is the by-reference VV copy whose
// early load (lqc2 vf6 before the vsqrt) the original shows.
typedef int qword __attribute__((mode(TI)));
union VECTOR4 { qword q; float f[4]; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
class FRAME;
struct ALLOCREQ { int cb, cbAlign; ALLOCREQ(int c, int a) { cb = c; cbAlign = a; } };
struct REGION;
struct LINK { char pad0[0x10]; REGION *pregion; };
struct EXT { char pad0[0xDC]; LINK *plink; };
struct VTE { short delta, pad; void *fn; };
struct PLAT { char pad0[0x10]; PLAT *parent; char pad14[0x50 - 0x14]; void *pxf; char pad54[0x128 - 0x54]; unsigned long flags; };
struct CANDIDATE;
struct LO { char pad0[0xC]; VTE *vt; char pad10[0xD8 - 0x10]; EXT *pext; char padDC[0x17C - 0xDC]; float sRadius; };
extern char D_00475480[];
extern qword D_00317530, D_00317550, D_00317570, D_00346FD0;
extern float D_00325598, D_0032559C;
extern CLQ D_00325580;
extern LM D_00325590;
extern "C" {
int func_001F83D8(float, float, float, qword, int, CANDIDATE **, qword *);
LO *func_001F4AD0(void *, int);
PLAT *func_001C7D60(void *);
REGION *func_001ED678(qword, int);
int func_001ED190(REGION *, qword, qword *, int);
int func_001ED1D0(REGION *, qword, qword, int);
void func_001D2770(FRAME *);
void func_001D2798(FRAME *, int);
void *func_001D25B0(ALLOCREQ *);
int func_001F8280(void *, int, int, LO **);
int func_001F69F8(void *, CANDIDATE *);
void func_0025CF18(void *, qword, qword, int (*)(void *, CANDIDATE *), void *, int *, CANDIDATE ***);
float func_0011E940(float, float);
float func_0011E3B8(float);
qword func_0011FD70(float, float, float);
float func_001B83F0(qword, qword, float, float, float, float);
void func_001F8138(LO *, qword, qword, float, float);
qword func_0028BCD0(void *, int, qword);
}
struct FRAME { int pad[4]; };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
static inline void *PvAllocFrame(int cb, int cbAlign) { ALLOCREQ req(cb, cbAlign); return func_001D25B0(&req); }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float GFromVf(qword v) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(v)); return g; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Length(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword LengthXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Div(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
static inline qword Normalize(qword v)
{
    qword fallback = D_00317530;
    qword l = Length(v);
    if (GFromVf(l) < 0.0001f)
        l = fallback;
    else
        l = Div(v, l);
    return l;
}
static inline qword Scale(qword g, qword v) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(g), "j"(v)); return r; }
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
static inline qword AddScaled(VV base, VU_FLOAT g, qword v)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base.q), "j"(v), "j"(g.q));
    return r;
}
static inline qword Combine(qword a, VU_FLOAT ga, qword b, VU_FLOAT gb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(ga.q), "j"(b), "j"(gb.q));
    return r;
}
static inline float GFromClq(const CLQ &clq, float g) { return clq.g0 + g * (clq.g1 + g * clq.g2); }
static inline float GClampR(float g, float gMin, float gMax) { if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
static inline float GClamp(float g, const LM &lm) { return GClampR(g, lm.gMin, lm.gMax); }
static inline REGION *PregionFromLo(LO *plo)
{
    EXT *pext = plo->pext;
    LINK *plink = pext ? pext->plink : 0;
    return plink ? plink->pregion : 0;
}
static inline qword Position(LO *plo) { VTE *e = &plo->vt[36]; return ((qword *(*)(void *))e->fn)((char *)plo + e->delta)[3]; }
static inline void SetState(LO *plo, int state) { VTE *e = &plo->vt[80]; ((void (*)(void *, int))e->fn)((char *)plo + e->delta, state); }
static inline qword Add(qword a, qword b) return r { __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); }
static inline qword PosAt(qword base, float angle, float radius) { return Add(base, func_0011FD70(angle, radius, 0.0f)); }

extern "C" void func_001F85F8(void *pworld, int kind, qword posSeed, void *owner, int cRequested)
{
    VECTOR4 posOrig;
    if (!func_001F83D8(0.0f, 300.0f, D_00325598, posSeed, 0, 0, &posOrig.q))
        return;
    PLAT *pplat = func_001C7D60(owner);
    for (; pplat; pplat = pplat->parent)
        if (pplat->flags & 0x80)
            break;
    LO *plo = func_001F4AD0(pworld, 0);
    REGION *pregion = 0;
    if (plo)
        pregion = PregionFromLo(plo);
    if (!pregion)
        pregion = func_001ED678(posOrig.q, 1);
    VECTOR4 posSnap;
    if (func_001ED190(pregion, posOrig.q, &posSnap.q, 1))
        posSnap.f[2] = posOrig.f[2];
    else {
        qword pos = Position(plo);
        if (!func_001ED190(pregion, pos, &posSnap.q, 1))
            return;
        posSnap.f[2] = GetZ(pos);
    }
    if (2000.0f < GFromVf(LengthXY(Sub(posOrig.q, posSnap.q))))
        return;
    if (!func_001F83D8(-250.0f, 1500.0f, D_00325598, posSnap.q, 0, 0, &posSnap.q))
        return;
    FRAME frame;
    func_001D2770(&frame);
    LO **aplo = (LO **)PvAllocFrame(cRequested * sizeof(LO *), 0x10);
    int clo = func_001F8280(pworld, kind, cRequested, aplo);
    if (!clo) {
        func_001D2798(&frame, 2);
        return;
    }
    VECTOR4 posMin, posMax;
    posMin.q = AddScaled(posSnap.q, VU_FLOAT(-300.0f), D_00317570);
    posMax.q = AddScaled(posSnap.q, VU_FLOAT(300.0f), D_00317570);
    int ccand;
    CANDIDATE **apcand;
    func_0025CF18(D_00475480, posMin.q, posMax.q, func_001F69F8, 0, &ccand, &apcand);
    int cLaunched = 0;
    float gAngle = func_0011E940(-3.1415927f, 3.1415927f);
    float gRadius = 100.0f;
    for (int iAttempt = 0; cLaunched < clo;) {
        float g = GClamp(GFromClq(D_00325580, iAttempt * 0.02f), D_00325590);
        qword posTrial = PosAt(posSnap.q, gAngle, gRadius);
        qword dpos = Sub(posTrial, posOrig.q);
        qword dposPerp = Sub(dpos, Scale(Dot(dpos, D_00317550), D_00317550));
        qword posBase = posTrial;
        qword posAdjust = AddScaled(posBase, VU_FLOAT(g), Normalize(dposPerp));
        int fBlocked = !func_001ED1D0(pregion, posSnap.q, posTrial, 0) && !func_001ED1D0(pregion, posTrial, posAdjust, 0);
        VECTOR4 posLand;
        if (fBlocked && func_001F83D8(-300.0f, 300.0f, 0.7f, posTrial, ccand, apcand, &posLand.q)) {
            qword posTarget = AddScaled(posLand.q, VU_FLOAT(aplo[cLaunched]->sRadius - 1.0f), D_00317550);
            float t = func_001B83F0(Sub(posTarget, posOrig.q), D_00346FD0, 850.0f, -850.0f, 1.0f, 1.0f);
            t += cLaunched * 0.075f;
            qword v = Combine(Sub(posTarget, posOrig.q), VU_FLOAT(1.0f / t), D_00346FD0, VU_FLOAT(-0.5f * t));
            if (pplat) {
                qword shift = func_0028BCD0(pplat->pxf, 0, posOrig.q);
                v = AddScaled(v, VU_FLOAT(t), shift);
            }
            LO *ploLaunch = aplo[cLaunched++];
            func_001F8138(ploLaunch, posOrig.q, v, cLaunched * 0.1f, D_0032559C);
        }
        gAngle = func_0011E3B8(gAngle + 1.8f);
        gRadius += 23.0f;
        if (gRadius > 300.0f)
            gRadius -= 275.0f;
        if (++iAttempt >= 50)
            break;
    }
    for (; cLaunched < clo; cLaunched++)
        SetState(aplo[cLaunched], -1);
    func_001D2798(&frame, 2);
}
