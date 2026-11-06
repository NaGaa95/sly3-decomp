// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Chooses the jump target of the player (Sly 3 version of Sly 2 func_0019B110). Up to nine candidate lists are scanned, each
// enabled by a bit of the player's target-flag virtual (slot 106): every candidate is scored with the func_0011EF00 minimizer over
// the func_001BB6D0/B730/B7B0/B830/B860 callbacks, biased by func_001BBC00 and checked for a clear path with func_001BB918 unless it
// is the forced target. The best one is published in pstepplayer->pxf (+0xA8 landing time, +0xC0 position, +0xD0 velocity) and
// func_001B77F8 starts the jump of that kind (10..17 and 19, the partner's target).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
#define FLT_MAX 3.40282347e+38f

union VECTOR { qword q; float f[4]; int i[4]; };
struct M4 { VECTOR r[4]; };
struct VTE { short d; short pad; void *fn; };
struct VU_VECTOR
{
    qword q;
    VU_VECTOR() {}
    VU_VECTOR(qword a) { q = a; }
    VU_VECTOR(const VECTOR &v) { q = v.q; }
};

struct SOPHYS { char pad0[0x80]; VECTOR dvGravity; };
struct XF { char pad0[0xA8]; float tGoal; char padAC[0xC0 - 0xAC]; qword posGoal; qword vGoal; };

struct LO { char pad0[0xC]; VTE *vt; };
struct STEPPLAYER : LO
{
    char pad10[0x48 - 0x10];
    XF *pxf;                    // 0x48
    char pad4C[0xD8 - 0x4C];
    SOPHYS *psophys;            // 0xD8
    void *psoCollide;           // 0xDC
    char padE0[0x164 - 0xE0];
    uint grfTarget;             // 0x164
    char pad168[0x260 - 0x168];
    qword qwOffset;             // 0x260
    char pad270[0x320 - 0x270];
    char jtair[0x500 - 0x320];  // 0x320
    char jtcontrol[0x1130 - 0x500];   // 0x500
    float sClearance;           // 0x1130
    char pad1134[0x1520 - 0x1134];
    int nPartnerState;          // 0x1520
    char pad1524[0x18E4 - 0x1524];
    int fPartnerBusy;           // 0x18E4
    char pad18E8[4];
    LO *ploPartnerTarget;       // 0x18EC
    STEPPLAYER *pstepplayerOther;   // 0x18F0
};

struct JTAIR
{
    STEPPLAYER *pstepplayer;
    char pad4[0x10 - 0x4];
    float uTarget;              // 0x10
    float sTarget;              // 0x14
};

class TARGET
{
public:
    int pad0, pad4;
    float sHeight;              // 0x08
    int padC[5];
    uint grf;                   // 0x20
    virtual void V01(); virtual void V02();
    virtual void GetPoint(STEPPLAYER *pstepplayer, qword *ppos, void *pv, float u);
};
class PAD_D0 : public LO { public: char ab[0xD0 - sizeof(LO)]; };
class PAD_180 { public: char ab[0x180]; };
struct SHAPE : PAD_D0, TARGET { char padF8[0x114 - 0xF8]; SHAPE *pshapeNext; int pad118; float rAngle; };
struct CURVE : PAD_180, TARGET { char pad1A8[0x1C4 - 0x1A8]; CURVE *pcurveNext; };
struct HOOK : LO
{
    char pad10[0xF4 - 0x10];
    float sHeight;              // 0xF4
    char padF8[0x10C - 0xF8];
    uint grf;                   // 0x10C
    char pad110[0x140 - 0x110];
    HOOK *phookNext;            // 0x140
    char pad144[4];
    int nType;                  // 0x148
    char pad14C[0x16C - 0x14C];
    float gBias;                // 0x16C
};
class PAD_130 { public: char ab[0x130]; };
struct SHAPE2 : PAD_130, TARGET { char pad158[0x170 - 0x158]; SHAPE2 *pshapeNext; };

struct CURVECTX { void *pjtcontrol; void *pjtair; CURVE *pcurve; int pad; qword v; };
struct OBJCTX { JTAIR *pjtair; void *plo; int pad[2]; qword v; };
struct HITCTX { JTAIR *pjtair; void *plo; float sRadius; qword *pplane; VECTOR v; };
struct PAIR { JTAIR *pjtair; void *plo; };
struct SOLIST { int cpso; void **apso; };
struct CLOCK { float t, dt; };
typedef float (*PFNSCORE)(void *, float);

extern "C" {
extern SHAPE *D_00479AFC, *D_00479B20, *D_00479B2C;
extern SHAPE2 *D_00479BA4;
extern CURVE *D_00479AF0, *D_00479AE4, *D_00479B14;
extern HOOK *D_00479B44;
extern STEPPLAYER *D_0038AE90;      // the partner
extern CLOCK D_0036BB98;            // g_clock
extern qword D_00317560;            // zero vector
extern qword D_003457D0;
extern float D_003457C0;

qword func_001BB4E8(JTAIR *pjtair, int nKind);
void func_001BB228(JTAIR *pjtair, VU_VECTOR v, void *plo, VU_VECTOR pos, VU_VECTOR dpos, float *pt, float *pg,
                   VECTOR *ppos, VECTOR *pv);
float func_001BBC00(JTAIR *pjtair, void *plo, float g, float dg);
int func_001BB918(JTAIR *pjtair, void *pfnFilter, void *pvFilter, float t, qword pos, qword v, qword posEnd, qword vEnd,
                  qword *ppos);
int func_0025CDD0(void *, void *);
int func_001BBC28(void *, void *);
int func_002496C8(void *);
int func_001A29B0(void *);
qword func_00250600(void *);
void func_0022EA88(CURVE *pcurve, qword pos, void *pv, VECTOR *ppos, VECTOR *pdir, float *pu, float *ps);
void func_0022EF30(CURVE *pcurve, PFNSCORE pfn, void *pv, int a, int b, float *pg, float *pgOut);
float func_0022F3F8(CURVE *pcurve);
float func_0022DE50(CURVE *pcurve, float s);
float func_0022DFD8(CURVE *pcurve);
float func_0022DD48(CURVE *pcurve, float u);
void func_0011EF00(PFNSCORE pfn, void *pv, float g0, float g1, float gMin, float gMax, float tol, float *px, float *pg);
float func_001BB6D0(void *pv, float u);
float func_001BB730(void *pv, float u);
float func_001BB7B0(void *pv, float u);
float func_001BB830(void *pv, float u);
float func_001BB860(void *pv, float u);
void func_001B5370(void *pjtcontrol, CURVE *pcurve, VECTOR *ppos, VECTOR *pv, float u);
void func_001BCFF8(JTAIR *pjtair, void *pctx, float *pg, VECTOR *ppos, VECTOR *pv, float t);
void func_0022E330(CURVE *pcurve, float s, VECTOR *ppos, VECTOR *pnormal);
qword func_001C9428(void *pvFrom, void *pvTo, qword pos);
float func_001205C8(qword v);
void func_0028F730(void *, void *, float, float *, float *);
void func_001B77F8(JTAIR *pjtair, int nKind, void *plo);
}

static inline qword Position(LO *p) { VTE &v = p->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.d)->r[3].q; }
static inline qword Velocity(LO *p) { VTE &v = p->vt[38]; return ((qword (*)(void *))v.fn)((char *)p + v.d); }
static inline uint Flags(LO *p) { VTE &v = p->vt[106]; return ((uint (*)(void *))v.fn)((char *)p + v.d); }
static inline void *GetSpace(LO *p, M4 *out) { VTE &v = p->vt[37]; return ((void *(*)(void *, M4 *))v.fn)((char *)p + v.d, out); }

static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float LengthSquared(qword v)
{
    qword l, one; float r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(l), "=&j"(one) : "0"(v));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(l));
    return r;
}
static inline float Length(qword v)
{
    qword l, one; float r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(l), "=&j"(one) : "0"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "0"(l));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(l));
    return r;
}
static inline float GMinOf(float a, float b) { return a < b ? a : b; }

extern "C" void func_001BBCA8(JTAIR *pjtair, void *ploForce)
{
    void *ploBest = 0;
    int nKind = -1;
    float sBest = 0.0f, uBest = 0.0f;
    VECTOR pos, v, posHit, posBest, vHit, vBest;
    VECTOR vLaunch, posTarget;
    float t, g;

    pos.q = Position(pjtair->pstepplayer);
    v.q = Velocity(pjtair->pstepplayer);
    uint grf = pjtair->pstepplayer->grfTarget;
    uint flags = Flags(pjtair->pstepplayer);
    float gBest = ploForce ? -FLT_MAX : FLT_MAX;
    vLaunch.q = func_001BB4E8(pjtair, 4);
    float tBest = 0.0f;

    if (flags & 0x400) {
        for (SHAPE *pshape = D_00479AFC; pshape; pshape = pshape->pshapeNext) {
            if (!(pshape->grf & grf))
                continue;
            if (func_002496C8(pshape))
                continue;
            pshape->GetPoint(pjtair->pstepplayer, &posTarget.q, 0, 0.0f);
            if (pshape != ploForce && pshape->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            func_001BB228(pjtair, vLaunch, pshape, posTarget, D_00317560, &t, &g, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pshape != ploForce) {
                if (g >= 2500.0f)
                    continue;
                g = func_001BBC00(pjtair, pshape, g, -250.0f);
                if (gBest <= g)
                    continue;
                if (func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, vLaunch.q,
                                  posHit.q, vHit.q, 0))
                    continue;
            }
            posBest = posHit;
            vBest = vHit;
            nKind = 10;
            ploBest = pshape;
            gBest = GMinOf(g, gBest);
            tBest = t;
        }
    }

    if (flags & 0x200) {
        for (CURVE *pcurve = D_00479AF0; pcurve; pcurve = pcurve->pcurveNext) {
            if (!(pcurve->grf & grf))
                continue;
            if (pcurve != ploForce) {
                func_0022EA88(pcurve, func_00250600(pjtair->pstepplayer), 0, &posTarget, 0, 0, 0);
                if (pcurve->sHeight < pos.f[2] - posTarget.f[2])
                    continue;
            }
            CURVECTX ctx;
            float uStart, u;
            ctx.pjtcontrol = pjtair->pstepplayer->jtcontrol;
            ctx.pjtair = pjtair->pstepplayer->jtair;
            ctx.pcurve = pcurve;
            ctx.v = vLaunch.q;
            func_0022EF30(pcurve, func_001BB6D0, &ctx, 0, 0, &uStart, 0);
            float step = func_0022F3F8(pcurve);
            float tol = step * 0.1f;
            func_0011EF00(func_001BB6D0, &ctx, uStart, step, func_0022DE50(pcurve, 50.0f),
                          func_0022DE50(pcurve, func_0022DFD8(pcurve) - 50.0f), tol, &u, &g);
            if (pcurve != ploForce) {
                if (g >= 2500.0f)
                    continue;
                g = func_001BBC00(pjtair, pcurve, g, 0.0f);
                if (gBest <= g)
                    continue;
            }
            VECTOR dpos;
            func_001B5370(ctx.pjtcontrol, pcurve, &posTarget, &dpos, u);
            func_001BB228(pjtair, vLaunch, pcurve, posTarget, dpos, &t, 0, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pcurve != ploForce &&
                func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, vLaunch.q,
                              posHit.q, vHit.q, 0))
                continue;
            ploBest = pcurve;
            gBest = GMinOf(g, gBest);
            nKind = 11;
            posBest = posHit;
            vBest = vHit;
            uBest = u;
            tBest = t;
            sBest = func_0022DD48(pcurve, uBest);
        }
    }

    if (flags & 0x1) {
        for (HOOK *phook = D_00479B44; phook; phook = phook->phookNext) {
            if (phook != ploForce) {
                if (ploForce)
                    continue;
            }
            if (!(phook->grf & grf))
                continue;
            qword posHook = Position(phook);
            posTarget.q = posHook;
            if (phook != ploForce) {
                if (phook->sHeight < pos.f[2] - posTarget.f[2])
                    continue;
                if (1000000.0f < LengthSquared(Sub(posHook, pos.q)))
                    continue;
            }
            HITCTX ctx;
            ctx.pjtair = pjtair;
            ctx.plo = phook;
            ctx.pplane = phook->nType == 3 ? &D_003457D0 : 0;
            ctx.sRadius = pjtair->pstepplayer->sClearance;
            ctx.v.i[0] = ctx.v.i[1] = ctx.v.i[2] = 0;
            func_0011EF00(func_001BB830, &ctx, 0.5f, 0.25f, 0.25f, 3.0f, 0.1f, &t, &g);
            g = g + phook->gBias;
            func_001BCFF8(ctx.pjtair, &ctx, 0, &posHit, &vHit, t);
            if (phook != ploForce) {
                if (g >= 2500.0f)
                    continue;
                g = func_001BBC00(pjtair, phook, g, 0.0f);
                if (gBest <= g)
                    continue;
                M4 frame;
                M4 *pf = &frame;
                func_0028F730(GetSpace(phook, pf), 0, t, (float *)pf, 0);
                if (func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, v.q,
                                  posHit.q, vHit.q, &frame.r[3].q))
                    continue;
            }
            nKind = 15;
            ploBest = phook;
            posBest.q = Add(posHit.q, pjtair->pstepplayer->qwOffset);
            vBest = vHit;
            gBest = GMinOf(gBest, g);
            tBest = t;
        }
    }

    if (flags & 0x800) {
        if (D_0038AE90 && D_0038AE90->nPartnerState == 16 && !D_0038AE90->fPartnerBusy &&
            D_0038AE90->pstepplayerOther == pjtair->pstepplayer) {
            posTarget.q = Position(D_0038AE90->ploPartnerTarget);
            func_001BB228(pjtair, vLaunch, D_0038AE90->ploPartnerTarget, posTarget, D_00317560, &t, &g, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (D_0038AE90->ploPartnerTarget != ploForce) {
                if (g >= 2500.0f)
                    goto LPartnerDone;
                if (650.0f < pos.f[2] - posTarget.f[2])
                    goto LPartnerDone;
                g = func_001BBC00(pjtair, D_0038AE90, g, -500.0f);
                if (gBest <= g)
                    goto LPartnerDone;
                void *apso[2];
                SOLIST solist;
                apso[0] = pjtair->pstepplayer->psoCollide;
                apso[1] = D_0038AE90->psoCollide;
                solist.cpso = 2;
                solist.apso = apso;
                if (func_001BB918(pjtair, (void *)func_001BBC28, &solist, t, pos.q, vLaunch.q, posHit.q, vHit.q, 0))
                    goto LPartnerDone;
            }
            posBest = posHit;
            vBest = vHit;
            nKind = 19;
            ploBest = D_0038AE90->ploPartnerTarget;
            tBest = t;
            gBest = GMinOf(g, gBest);
        }
    }
LPartnerDone:

    if (flags & 0x2) {
        for (CURVE *pcurve = D_00479AE4; pcurve; pcurve = pcurve->pcurveNext) {
            if (!(pcurve->grf & pjtair->pstepplayer->grfTarget))
                continue;
            float sCur;
            func_0022EA88(pcurve, pos.q, 0, &posTarget, 0, 0, &sCur);
            if (pcurve != ploForce) {
                if (pcurve->sHeight < pos.f[2] - posTarget.f[2])
                    continue;
                if (1000.0f < Length(Sub(posTarget.q, pos.q)))
                    continue;
            }
            PAIR pair;
            float s, gCurve;
            pair.pjtair = pjtair;
            pair.plo = pcurve;
            func_0011EF00(func_001BB860, &pair, sCur, 100.0f, 100.0f, func_0022DFD8(pcurve) - 100.0f, 5.0f, &s, &gCurve);
            if (pcurve != ploForce) {
                if (2500.0f <= gCurve)
                    continue;
                gCurve = func_001BBC00(pjtair, pcurve, gCurve, 1250.0f);
                if (gBest <= gCurve)
                    continue;
            }
            HITCTX ctx;
            ctx.pjtair = pjtair;
            ctx.plo = pcurve;
            ctx.sRadius = pjtair->pstepplayer->sClearance;
            ctx.pplane = 0;
            func_0022E330(pcurve, s, &posTarget, 0);
            ctx.v.q = func_001C9428(0, pcurve, posTarget.q);
            func_0011EF00(func_001BB830, &ctx, 0.5f, 0.25f, 0.25f, 3.0f, 0.1f, &t, 0);
            func_001BCFF8(ctx.pjtair, &ctx, 0, &posHit, &vHit, t);
            if (pcurve != ploForce &&
                func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                              vHit.q, &posTarget.q))
                continue;
            nKind = 16;
            ploBest = pcurve;
            posBest.q = Add(posHit.q, pjtair->pstepplayer->qwOffset);
            vBest = vHit;
            gBest = GMinOf(gBest, gCurve);
            tBest = t;
            sBest = s;
        }
    }

    if (flags & 0x10) {
        for (SHAPE *pshape = D_00479B20; pshape; pshape = pshape->pshapeNext) {
            if (!(pshape->grf & grf))
                continue;
            qword posShape = Position(pshape);
            posTarget.q = posShape;
            if (pshape->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            OBJCTX ctx;
            VECTOR dpos;
            float u;
            ctx.v = v.q;
            ctx.pjtair = pjtair;
            ctx.plo = pshape;
            dpos.q = Sub(pos.q, posShape);
            func_0011EF00(func_001BB730, &ctx, func_001205C8(dpos.q) * pshape->rAngle, 100.0f, -FLT_MAX, FLT_MAX, 5.0f, &u, &g);
            g = g * D_003457C0;
            if (pshape != ploForce) {
                if (g >= 2500.0f)
                    continue;
                g = func_001BBC00(pjtair, pshape, g, 500.0f);
                if (gBest <= g)
                    continue;
            }
            VECTOR posPoint;
            pshape->GetPoint(pjtair->pstepplayer, &posPoint.q, 0, u);
            func_001BB228(pjtair, v, pshape, posPoint, D_00317560, &t, 0, &posHit, &vHit);
            vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pshape != ploForce &&
                func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                              vHit.q, 0))
                continue;
            nKind = 13;
            ploBest = pshape;
            posBest = posHit;
            vBest = vHit;
            gBest = GMinOf(gBest, g);
            tBest = t;
            sBest = u;
        }
    }

    if (flags & 0x8) {
        for (CURVE *pcurve = D_00479B14; pcurve; pcurve = pcurve->pcurveNext) {
            if (!(pcurve->grf & grf))
                continue;
            float sCur;
            func_0022EA88(pcurve, pos.q, 0, &posTarget, 0, 0, &sCur);
            if (pcurve->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            OBJCTX ctx;
            float u;
            ctx.v = v.q;
            ctx.pjtair = pjtair;
            ctx.plo = pcurve;
            func_0011EF00(func_001BB7B0, &ctx, sCur, 100.0f, 30.0f, func_0022DFD8(pcurve) - 30.0f, 5.0f, &u, &g);
            g = g * D_003457C0;
            if (pcurve != ploForce) {
                if (g >= 2500.0f)
                    continue;
                g = func_001BBC00(pjtair, pcurve, g, 500.0f);
                if (gBest <= g)
                    continue;
            }
            VECTOR posPoint;
            pcurve->GetPoint(pjtair->pstepplayer, &posPoint.q, 0, u);
            func_001BB228(pjtair, v, pcurve, posPoint, D_00317560, &t, 0, &posHit, &vHit);
            vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pcurve != ploForce &&
                func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                              vHit.q, 0))
                continue;
            nKind = 12;
            ploBest = pcurve;
            posBest = posHit;
            vBest = vHit;
            gBest = GMinOf(gBest, g);
            tBest = t;
            sBest = u;
        }
    }

    if (flags & 0x20) {
        for (SHAPE *pshape = D_00479B2C; pshape; pshape = pshape->pshapeNext) {
            if (!(pshape->grf & grf))
                continue;
            pshape->GetPoint(pjtair->pstepplayer, &posTarget.q, 0, 0.0f);
            if (pshape != ploForce && pshape->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            func_001BB228(pjtair, v, pshape, posTarget, D_00317560, &t, &g, &posHit, &vHit);
            vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pshape != ploForce) {
                if (g >= 2500.0f)
                    continue;
                g = func_001BBC00(pjtair, pshape, g, -250.0f);
                if (gBest <= g)
                    continue;
                if (func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                                  vHit.q, 0))
                    continue;
            }
            nKind = 14;
            ploBest = pshape;
            gBest = GMinOf(g, gBest);
            posBest = posHit;
            vBest = vHit;
            tBest = t;
        }
    }

    if (flags & 0x1000) {
        for (SHAPE2 *pshape = D_00479BA4; pshape; pshape = pshape->pshapeNext) {
            if (!(pshape->grf & grf))
                continue;
            if (func_001A29B0(pshape))
                continue;
            pshape->GetPoint(pjtair->pstepplayer, &posTarget.q, 0, 0.0f);
            if (pshape != ploForce && pshape->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            func_001BB228(pjtair, vLaunch, pshape, posTarget, D_00317560, &t, &g, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pshape != ploForce) {
                if (g >= 2500.0f)
                    continue;
                g = func_001BBC00(pjtair, pshape, g, -250.0f);
                if (gBest <= g)
                    continue;
                if (func_001BB918(pjtair, (void *)func_0025CDD0, pjtair->pstepplayer->psoCollide, t, pos.q, vLaunch.q,
                                  posHit.q, vHit.q, 0))
                    continue;
            }
            nKind = 17;
            ploBest = pshape;
            gBest = GMinOf(g, gBest);
            posBest = posHit;
            vBest = vHit;
            tBest = t;
        }
    }

    if (nKind != -1) {
        XF *pxf = pjtair->pstepplayer->pxf;
        pxf->tGoal = D_0036BB98.t + tBest;
        pxf->posGoal = Sub(posBest.q, pjtair->pstepplayer->qwOffset);
        pxf->vGoal = vBest.q;
        pjtair->uTarget = uBest;
        pjtair->sTarget = sBest;
        func_001B77F8(pjtair, nKind, ploBest);
    }
}
