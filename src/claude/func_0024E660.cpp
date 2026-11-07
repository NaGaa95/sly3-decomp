// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0024E660: a STEP's contact-velocity adjustment (vtable slot 56; Sly 1 has AdjustStepXpVelocity(STEP *, XP *, int)).
// After the base version (func_0023E128), for a kind-0xE contact: the closing speed along the contact normal is smoothed
// with GSmooth (GSmooth) toward two limits (SMPs D_002C3C98 / D_002C3CA8), the change is limited to dt * 9000 up and
// dt * -4500 down, and this side's velocity gets normal * -speed plus (matTarget * vUnk1A0 without its part along the
// normal) * gUnk190. Finally the contact distance moves by gUnk220 - gUnk268.
// Matched with one asm statement per VU0 operation, no register pins: the local pmat gives the target's pointer/row registers,
// the two smoothing outputs are separate address-taken floats (frame slots after the VU_FLOAT home at 0($sp)).
typedef int qword __attribute__((mode(TI)));

struct VU_FLOAT
{
    qword qw;
};

struct M3
{
    qword mat[3];
};

/* one side of a contact: 0x40 bytes, its velocity at +0x30 */
struct STEP;
struct XPD
{
    char pad0[0xC];
    struct STEP *pstep;
    qword pos;
    char pad20[0x10];
    qword v;
};
struct POSO { char pad[0x30]; qword pos; };

struct XP
{
    struct XPD axpd[2];
    qword normal;
    float gDist;
    int unk94[2];
    int xpk;
};

struct VTE { short delta; short pad; void *pfn; };
struct STEP
{
    char pad0[0xC];
    struct VTE *vt;
    char pad10[0x180];
    float gUnk190;
    char pad194[0xC];
    qword vUnk1A0;
    char pad1b0[0x10];
    struct M3 matTarget;
    char pad1f0[0x30];
    float gUnk220;
    char pad224[0x44];
    float gUnk268;
};

struct CLOCK
{
    float t;
    float dt;
};

extern "C" struct CLOCK g_clock;
// The unit's rodata: the two SMPs, then the next literal of the unit (FLT_MAX).
extern "C" {
extern const float D_00327240[3] __attribute__((aligned(16))) = { 3000.0f, 0.0f, 0.35f };
extern const float D_00327250[3] __attribute__((aligned(16))) = { 3000.0f, 0.0f, 0.5f };
extern const float D_0032725C = 3.40282346639e+38f;
}

extern "C" void func_0023E128(struct STEP *pstep, struct XP *pxp, int ixpd);
float GSmooth(float gCur, float gTarget, float dt, const float *psmp, float *pdgNext) asm("func_0011E598");

static inline qword QwSub(qword a, qword b)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}

static inline qword QwCross(qword a, qword b)
{
    qword qw;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwDot(qword a, qword b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}

static inline float FloatOfVf(qword qw)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(qw));
    return g;
}

static inline qword QwRotate(struct M3 *pmat, qword v)
{
    qword qw;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(qw) : "j"(v), "j"(pmat->mat[0]), "j"(pmat->mat[1]), "j"(pmat->mat[2]));
    return qw;
}

static inline qword QwScale(qword v, qword s)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(v), "j"(s));
    return qw;
}

static inline struct VU_FLOAT VuFloat(float g)
{
    struct VU_FLOAT vu;
    __asm__("qmtc2.ni %1, %0" : "=j"(vu.qw) : "r"(g));
    return vu;
}

static inline struct VU_FLOAT VuFloatFromMemWord(int n)
{
    struct VU_FLOAT vu;
    __asm__("qmtc2.ni %1, %0" : "=j"(vu.qw) : "rV"(n));
    return vu;
}

static inline qword QwAddScaled2(qword v, qword a, qword sa, qword b, qword sb)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
            : "=j"(qw) : "j"(v), "j"(a), "j"(sa), "j"(b), "j"(sb));
    return qw;
}

extern "C" void func_0024E660(struct STEP *pstep, struct XP *pxp, int ixpd)
{
    func_0023E128(pstep, pxp, ixpd);
    if (pxp->xpk != 0xE)
        return;
    struct XPD *pxpd = &pxp->axpd[ixpd];
    {
        if (pxpd->pstep == pstep)
        {
            qword v = pxpd->v;
            struct VTE *e = &pstep->vt[0x27];
            qword w = ((qword (*)(void *))e->pfn)((char *)pstep + e->delta);
            qword pos = pxpd->pos;
            e = &pstep->vt[0x24];
            struct POSO *pposo = ((struct POSO *(*)(void *))e->pfn)((char *)pstep + e->delta);
            pxpd->v = QwSub(v, QwCross(w, QwSub(pos, pposo->pos)));
        }
    }

    float gVn = FloatOfVf(QwDot(QwSub(pxp->axpd[0].v, pxp->axpd[1].v), pxp->normal));
    float gVnMin;
    float gVnTarget;
    GSmooth(pxp->gDist, pstep->gUnk220, g_clock.dt, D_00327240, &gVnMin);
    GSmooth(pxp->gDist, 0.0f, g_clock.dt, D_00327250, &gVnTarget);
    gVn = gVn > gVnMin ? gVn : gVnMin;
    if (gVn < gVnTarget)
    {
        float dg = gVnTarget - gVn;
        float dgMax = g_clock.dt * 9000.0f;
        gVn += dg < dgMax ? dg : dgMax;
    }
    else
    {
        float dg = gVnTarget - gVn;
        float dgMin = g_clock.dt * -4500.0f;
        gVn += dg > dgMin ? dg : dgMin;
    }

    struct M3 *pmat = &pstep->matTarget;
    qword v = QwRotate(pmat, pstep->vUnk1A0);
    qword normal = pxp->normal;
    qword vT = QwSub(v, QwScale(normal, QwDot(v, normal)));
    struct VU_FLOAT vuVn = VuFloat(-gVn);
    struct VU_FLOAT vuK = VuFloatFromMemWord(*(int *)&pstep->gUnk190);
    pxpd->v = QwAddScaled2(pxpd->v, normal, vuVn.qw, vT, vuK.qw);
    pxp->gDist += pstep->gUnk220 - pstep->gUnk268;
}
