// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00274AC0: the follow camera policy's update (Sly 2 CMPART2::Update 0x221DD8, src/hand/func_00221DD8.cpp in the
// Sly 2 decomp, with Sly 3's zones in place of tunnels; SafeHouse sly3/cmfollow3.cpp documents it).
// Keys: address-taken float out-params as scalars; radStick test as `else if (> 1.309) {dradPan=0; fLeft=1}
// else {fLeft=1; fArrived=1}` (cross-jumped B8 store); D_00329108 const (unchanging mem: no anti-deps, fixes the smpPull
// schedule); the uRate length read through an mtc1 asm so gcc emits the qmfc2 itself (mov.s into the bc1f slot).
typedef int qword __attribute__((mode(TI)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX4 { qword mat[4]; };
struct LM { float gMin, gMax; };
struct CLQ { float g0, g1, g2, gUnused; };
struct SMP { float svFast, svSlow, dtFast; };
struct VTE { short d; short pad; void *pfn; };
struct VT { VTE ae[40]; };
struct CM {
    char pad0[0xC]; VT *pvt;
    char pad10[0x138 - 0x10]; float gTanHalfX; float gTanHalfY; int pad140; float sNearClip;
    char pad148[0x2F4 - 0x148]; int nCut; float radCutPan; float radCutTilt;
};
struct LO { char pad0[0xC]; VT *pvt; };
struct PLAYER {
    char pad0[0x508]; int n508; int n50C; char pad510[0x568 - 0x510]; struct ZONE *pzone;
};
struct HERO { char pad0[0x1520]; int n1520; };
struct SHAPE { char pad0[0xD0]; int nD0; int padD4; int nD8; };
struct ZRET {
    int fPullEnter; float dtPullEnter; float gPullEnter;
    int fPullIdle; float dtPullIdle; float gPullIdle;
    int fTiltEnter; float dtTiltEnter; float gTiltEnter;
    int fTiltIdle; float dtTiltIdle; float gTiltIdle;
};
struct ZONE {
    char pad0[0xC]; VT *pvt;
    char pad10[0x108 - 0x10]; SHAPE *pshape; char pad10C[0x11C - 0x10C]; int fCylind;
    char pad120[0x128 - 0x120]; float radPanLimit; int grftnm; ZRET *pzret; int nTurnAxis;
    char pad138[0x140 - 0x138]; int fNoCamClip; LO *ploPull; char pad148[0x150 - 0x148]; CLQ clqPull; LM lmPull;
    char pad168[0x19C - 0x168]; int n19C;
};
struct CME {
    int cid; float dsOffset; char pad8[0x10 - 0x8]; CLQ aclqOffset[3]; LM almOffset[3]; float uFrameX; float uFrameY;
    int pad60; float uTunnel; float gTurn; char pad6C[0x80 - 0x6C]; float kDist; float cDist; LM lmTilt;
};
struct CPDEFI {
    qword posBase; qword vBase; qword q20; qword dposFocus;
    float dTilt, dDist; int grfcpd; float radHome; float tMoveLast; int nTurnAxis; int pad58[2];
};
struct JOY { float dxLeft, dyLeft, pad8, dxRight, dyRight, sRight; };
struct CPF {
    CM *pcm; char pad4[0x20 - 0x4]; ZONE *pzone; CME *pcme; char pad28[0x30 - 0x28]; char rec[0xA0 - 0x30];
    float radPan, radTilt, sDist, uFrameY; int nMode; int fArrived; int fLeft; float dradPan, dradTilt; float tManual;
    float uProgress; float radPanCrv; float radPanFwd, radTiltFwd, radPanRev, radTiltRev; float tMoveLast; float tEnter;
    int fEntered; int fReset; float uTunnel; float dsDist, duFrameY; int padFC; qword posEye; int pad110; float tClear;
    float radPanLook, radTiltLook, dradPanLook, dradTiltLook;
};
struct CLOCK { float t; float dt; float pad8, padC; float dtCm; float tCm; };
struct GAME { int pad0; float tCmTurned; };
extern CLOCK g_clock;
extern float D_0036BB9C;
extern GAME D_0036C700;
extern LM D_00341FF0;
extern LM D_003290E8;
extern ZRET D_0034A040;
extern LO *D_0038AE90;
extern int D_00349FA0;
extern qword D_00317530;
extern qword D_00317550;
extern qword D_00317560;
extern CLQ D_003290D0;
extern CLQ D_003290F0;
extern LM D_00329100;
extern const SMP D_00329108;
extern CLQ D_00329120;
extern SMP D_00329130;
extern SMP D_00329140;
float GLimitAbs(float g, float absLimit);
extern "C" {
ZONE *func_001662A8(CM *pcm);
void func_002747D0(CPF *p);
LO *func_00166540(CM *pcm);
JOY *func_00169EB0(CPF *p);
void func_001F3ED8(LO *plo, int fCut, void *prec, CPDEFI *pcpdefi);
int func_0013B500(LO *plo, int cid);
void func_00276510(CPF *p, CPDEFI *pcpdefi);
void func_00274A50(CPF *p, CPDEFI *pcpdefi);
void func_00273AB0(CME *pcme, CPDEFI *pcpdefi, qword *ppos, CPF *p);
float func_0011E598(float gCur, float gTarget, float dt, SMP *psmp, float *pdgNext);
void func_00274270(CPF *p, qword qwPos, VECTOR4 *pdposCrv, VECTOR4 *pvecTangent);
void func_00120B00(qword v, float *prad, float *psXY, float *pz);
float func_0011E3B8(float rad);
void func_00274390(ZONE *pzone, float *ag, float sBase, float dsOffset, CLQ *aclq, LM *alm, int ftnd, qword *ppos);
void func_00120BA8(qword v, float *prad, float *pradTilt, float *psLen);
float func_002A3160(float x);
float func_0011EE68(LM *plm, float g);
void *func_002459F8(int sfxid);
void func_00244F08(void *psnd, LO *plo);
void func_001A7B38(JOY *pjoy, int n, float *pdx, float *pdy);
float atan2f(float y, float x);
void func_001854C8(GAME *pgame, int nEvent, LO *plo);
qword func_001C94E8(ZONE *pzone, LO *plo, qword qwVec);
float func_0011E840(float radCur, float radTarget, float dt, SMP *psmp, float *pdradNext);
qword func_0011FDD8(float radPan, float radTilt, float s);
void func_00276900(CPF *p, qword posFocus, qword posEye, qword *pposOut);
qword func_00167660(CM *pcm, qword posFrom, qword posTo, int *pfBlocked);
void func_0011D048(MATRIX4 *pmat, float *pradPan, float *pradTilt);
void func_00166E48(CM *pcm, qword posEye, qword posCenter, float radPan, float radTilt);
void func_00274AC0(CPF *p);
}
#define VCALL(T, o, i) ((T)(o)->pvt->ae[i].pfn)((char *)(o) + (o)->pvt->ae[i].d)
static inline MATRIX4 *PmatCm(CM *pcm) { return VCALL(MATRIX4 *(*)(void *), pcm, 36); }
static inline MATRIX4 *PmatLo(LO *plo) { return VCALL(MATRIX4 *(*)(void *), plo, 36); }
struct VU_FLOAT { qword qw; };
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwAdd(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
// Same lane read with different asm text, so cse keeps the target's second qmfc2 of the length.
static inline float GFromVfM(qword qw)
{
    float g;
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(qw));
    return g;
}
static inline float GFromVfAgain(qword qw)
{
    float g;
    __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(qw));
    return g;
}
static inline qword QwLengthUntied(qword v)
{
    qword qwSq;
    qword vfOne;
    qword qwLen;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qwSq), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLen) : "j"(qwSq));
    return qwLen;
}
static inline qword QwLengthXY(qword v)
{
    qword qw;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
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
static inline float GXOfQw(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw));
    return x;
}
static inline qword QwCross(qword a, qword b)
{
    qword qw;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwToVu(qword qw)
{
    qword qwOut;
    __asm__("qmtc2.ni %1, %0" : "=j"(qwOut) : "r"(qw));
    return qwOut;
}
static inline qword QwMulX(qword qwRow, VU_FLOAT gScale)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(qwRow), "j"(gScale.qw));
    return qw;
}
static inline float GZOfQw(qword q)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q));
    return z;
}
static inline float GEvaluateClq(CLQ *pclq, float x)
{
    return pclq->g0 + x * (pclq->g1 + x * pclq->g2);
}
static inline float GEvaluateClqLm(CLQ *pclq, LM *plm, float x)
{
    float g = GEvaluateClq(pclq, x);
    float gMin = plm->gMin;
    float gMax = plm->gMax;
    if (g < gMin)
        g = gMin;
    else if (gMax < g)
        g = gMax;
    return g;
}
static inline float GLimitRange(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static inline float GMin(float a, float b)
{
    return a < b ? a : b;
}
static inline float GSmoothStep(float u)
{
    return u * u * (3.0f - (u + u));
}

void func_00274AC0(CPF *p)
{
    CPDEFI cpdefi;
    CM *pcm = p->pcm;
    float dt = g_clock.dtCm;
    ZONE *pzone = func_001662A8(pcm);
    if (p->fReset != 0 || p->pzone != pzone)
        func_002747D0(p);
    LO *plo = func_00166540(pcm);
    LO *ploPlayer = 0;
    JOY *pjoy = func_00169EB0(p);
    func_001F3ED8(plo, p->pcm->nCut != 0, p->rec, &cpdefi);
    if (func_0013B500(plo, 0x33))
        ploPlayer = plo;
    func_00276510(p, &cpdefi);
    int grftnm;
    ZRET *pzret;
    if (pzone != 0)
    {
        grftnm = pzone->grftnm;
        pzret = pzone->pzret;
    }
    else
    {
        grftnm = 4;
        pzret = &D_0034A040;
    }
    func_00274A50(p, &cpdefi);
    VECTOR4 posFocus;
    func_00273AB0(p->pcme, &cpdefi, (qword *)&posFocus, p);
    VECTOR4 posHang;
    *(qword *)&posHang = QwAdd(*(qword *)&posFocus, cpdefi.dposFocus);
    if (pzone != 0 && pzone->ploPull != 0)
        cpdefi.grfcpd &= ~1;
    float uTunnelWant;
    if ((cpdefi.grfcpd & 1) == 0)
        uTunnelWant = p->pcme->uTunnel;
    else
        uTunnelWant = 0.0f;
    p->uTunnel = func_0011E598(p->uTunnel, uTunnelWant, g_clock.dt, &D_00329130, 0);
    p->tMoveLast = p->tMoveLast > cpdefi.tMoveLast ? p->tMoveLast : cpdefi.tMoveLast;
    float radPanFwdNew = 0.0f;
    float radTiltFwdNew = 0.0f;
    float sDistFwd;
    float radPanRevNew = 0.0f;
    float radTiltRevNew = 0.0f;
    float sDistRev;
    VECTOR4 vecTangent;
    if (pzone != 0 && (grftnm & 3) != 0)
    {
        VECTOR4 dposCrv;
        func_00274270(p, *(qword *)&posFocus, &dposCrv, &vecTangent);
        if (pzone->fCylind)
        {
            func_00120B00(*(qword *)&dposCrv, &dposCrv.x, &dposCrv.y, &dposCrv.z);
            if (!p->fEntered)
                dposCrv.x += GLimitAbs(func_0011E3B8(p->radPanCrv - dposCrv.x), pzone->radPanLimit);
            p->radPanCrv = dposCrv.x;
        }
        if (grftnm & 1)
        {
            VECTOR4 posView;
            CME *pcme = p->pcme;
            func_00274390(pzone, &dposCrv.x, p->uProgress, pcme->dsOffset, pcme->aclqOffset, pcme->almOffset, 1, (qword *)&posView);
            func_00120BA8(QwSub(*(qword *)&posView, *(qword *)&posHang), &radPanFwdNew, &radTiltFwdNew, &sDistFwd);
            sDistFwd += cpdefi.dDist;
            radTiltFwdNew += cpdefi.dTilt;
        }
        if (grftnm & 2)
        {
            VECTOR4 posView;
            CME *pcme = p->pcme;
            func_00274390(pzone, &dposCrv.x, p->uProgress, pcme->dsOffset, pcme->aclqOffset, pcme->almOffset, 2, (qword *)&posView);
            func_00120BA8(QwSub(*(qword *)&posView, *(qword *)&posHang), &radPanRevNew, &radTiltRevNew, &sDistRev);
            sDistRev += cpdefi.dDist;
            radTiltRevNew += cpdefi.dTilt;
        }
    }
    if (p->fEntered)
        p->nMode = 4;
    CM *pcmCut = p->pcm;
    if (pcmCut->nCut != 0)
    {
        if (pcmCut->nCut == 2)
        {
            p->nMode = 4;
            p->radPan = pcmCut->radCutPan;
            float radTiltCut = p->pcm->radCutTilt - func_002A3160(p->pcme->uFrameY * pcmCut->gTanHalfY);
            p->radTilt = func_0011EE68(&D_003290E8, radTiltCut);
        }
        else if ((grftnm & 3) == 0)
        {
            p->nMode = 4;
            p->radPan = cpdefi.radHome;
            p->radTilt = p->pcme->lmTilt.gMin * 0.5f + p->pcme->lmTilt.gMax * 0.5f;
        }
        else if ((grftnm & 2) == 0)
        {
            p->nMode = 1;
        }
        else if ((grftnm & 1) == 0)
        {
            p->nMode = 2;
        }
        else
        {
            float dradFwd = func_0011E3B8(radPanFwdNew - cpdefi.radHome);
            float dradRev = func_0011E3B8(radPanRevNew - cpdefi.radHome);
            if (__builtin_fabsf(dradFwd) < __builtin_fabsf(dradRev))
                p->nMode = 1;
            else
                p->nMode = 2;
        }
        p->tMoveLast = g_clock.t;
        p->tManual = g_clock.t - 10.0f;
    }
    if ((p->nMode & grftnm) == 0 && p->nMode > 0 && p->nMode < 3)
        p->nMode = 4;
    VECTOR4 vFocus;
    if (pzone != 0 && pzone->ploPull != 0)
    {
        VECTOR4 dpos;
        *(qword *)&dpos = QwSub(PmatLo(pzone->ploPull)->mat[3], cpdefi.posBase);
        dpos.z = 0.0f;
        qword *pqwFallback = &D_00317560;
        qword qwDir = QwToVu(*(qword *)&dpos);
        qword qwLen = QwLengthUntied(qwDir);
        if (GFromVf(qwLen) < 0.0001f)
        {
            *(qword *)&dpos = *pqwFallback;
        }
        else
        {
            __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLen));
            qword qwNormal;
            __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qwNormal) : "j"(qwDir));
            *(qword *)&dpos = qwNormal;
        }
        float gPull = GEvaluateClqLm(&pzone->clqPull, &pzone->lmPull, GXOfQw(qwLen));
        *(qword *)&vFocus = QwMulX(*(qword *)&dpos, VuFloat(gPull));
    }
    else
    {
        *(qword *)&vFocus = cpdefi.vBase;
    }
    float radPanNew = p->radPan;
    float radTiltNew = p->radTilt;
    if ((grftnm & 4) != 0 && (cpdefi.grfcpd & 8) == 0 && (pjoy->sRight > 0.0f || p->dradPan != 0.0f || p->dradTilt != 0.0f))
    {
        if (p->nMode != 4)
            func_00244F08(func_002459F8(3), 0);
        float dradPanWant;
        float dradTiltWant;
        func_001A7B38(pjoy, pzone ? pzone->n19C : 0, &dradPanWant, &dradTiltWant);
        float dradMax = dt * 15.0f;
        p->dradPan = GLimitRange(dradPanWant, p->dradPan - dradMax, p->dradPan + dradMax);
        p->dradTilt = GLimitRange(dradTiltWant, p->dradTilt - dradMax, p->dradTilt + dradMax);
        float radStick = atan2f(__builtin_fabsf(pjoy->dyRight), __builtin_fabsf(pjoy->dxRight));
        if (radStick < 0.2617994f)
        {
            p->dradTilt = 0.0f;
            p->fArrived = 1;
        }
        else if (radStick > 1.3089969f)
        {
            p->dradPan = 0.0f;
            p->fLeft = 1;
        }
        else
        {
            p->fLeft = 1;
            p->fArrived = 1;
        }
        radPanNew = func_0011E3B8(radPanNew + p->dradPan * dt);
        radTiltNew = func_0011E3B8(radTiltNew + p->dradTilt * dt);
        radTiltNew = func_0011EE68(&D_003290E8, radTiltNew);
        if (g_clock.tCm - D_0036C700.tCmTurned > 5.0f)
        {
            D_0036C700.tCmTurned = g_clock.tCm;
            func_001854C8(&D_0036C700, 1, 0);
        }
        p->nMode = 4;
        p->tManual = g_clock.t;
    }
    else if (p->nMode == 4)
    {
        VECTOR4 vecStick;
        if (cpdefi.grfcpd & 8)
        {
            *(qword *)&vecStick = D_00317530;
        }
        else
        {
            float dx = pjoy->dxLeft;
            float dy = pjoy->dyLeft;
            vecStick.x = dx;
            vecStick.y = dy;
            vecStick.z = 0.0f;
            qword qwFallbackStick = D_00317530;
            qword qwStickRaw = *(qword *)&vecStick;
            qword qwLenStick = QwLengthUntied(qwStickRaw);
            qword qwStick;
            if (GFromVf(qwLenStick) < 0.0001f)
            {
                qwStick = qwFallbackStick;
            }
            else
            {
                __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLenStick));
                __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qwStick) : "j"(qwStickRaw));
            }
            *(qword *)&vecStick = qwStick;
        }
        VECTOR4 vecView;
        qword qwHang = *(qword *)&posHang;
        *(qword *)&vecView = QwSub(qwHang, PmatCm(p->pcm)->mat[3]);
        qword *pqwFallbackView = &D_00317530;
        vecView.z *= 0.3f;
        qword qwView = QwToVu(*(qword *)&vecView);
        qword qwLenView = QwLengthUntied(qwView);
        if (GFromVf(qwLenView) < 0.0001f)
        {
            *(qword *)&vecView = *pqwFallbackView;
        }
        else
        {
            __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLenView));
            qword qwNormal;
            __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qwNormal) : "j"(qwView));
            *(qword *)&vecView = qwNormal;
        }
        float sView = GFromVfAgain(qwLenView);
        int nTurnAxis;
        if (pzone != 0 && pzone->nTurnAxis != -1)
            nTurnAxis = pzone->nTurnAxis;
        else
            nTurnAxis = cpdefi.nTurnAxis;
        VECTOR4 vecAxis;
        switch (nTurnAxis)
        {
        case 0:
            *(qword *)&vecAxis = QwCross(D_00317550, *(qword *)&vecView);
            break;
        case 1:
            vecAxis = vecView;
            break;
        }
        qword qwFallbackAxis = D_00317530;
        qword qwAxis = *(qword *)&vecAxis;
        qword qwLenAxis = QwLengthUntied(qwAxis);
        if (GFromVf(qwLenAxis) < 0.0001f)
        {
            qwAxis = qwFallbackAxis;
        }
        else
        {
            __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLenAxis));
            __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qwAxis) : "j"(qwAxis));
        }
        *(qword *)&vecAxis = qwAxis;
        float gTurn = GLimitAbs(GFromVf(QwDot(*(qword *)&vFocus, qwAxis)) / sView, 2.5f);
        float dradPanFree = gTurn * p->uTunnel;
        dradPanFree *= GEvaluateClqLm(&D_003290F0, &D_00329100, vecStick.y);
        dradPanFree *= GLimitRange(GEvaluateClq(&D_00329120, g_clock.t - p->tManual), D_00341FF0.gMin, D_00341FF0.gMax);
        int grf3 = grftnm & 3;
        float radPanFree = func_0011E3B8(radPanNew + dradPanFree * g_clock.dt);
        float gBlend;
        float radPanPull;
        float radTiltView;
        if (grf3 == 0)
        {
            gBlend = 0.0f;
            radPanPull = radPanFree;
            radTiltView = func_0011EE68(&p->pcme->lmTilt, radTiltNew) + cpdefi.dTilt;
        }
        else
        {
            float gPull;
            float radPanView;
            if (pzone->pshape == 0 || p->nMode == 1)
            {
                gBlend = 1.0f;
                radPanView = radPanFwdNew;
                gPull = gBlend;
                radTiltView = radTiltFwdNew;
            }
            else if (ploPlayer != 0 && pzone == ((PLAYER *)ploPlayer)->pzone)
            {
                gPull = 3.0f;
                gBlend = 1.0f;
                radPanView = radPanFwdNew;
                radTiltView = radTiltFwdNew;
            }
            else if (p->nMode == 2)
            {
                gBlend = 1.0f;
                radPanView = radPanRevNew;
                gPull = gBlend;
                radTiltView = radTiltRevNew;
            }
            else
            {
                VECTOR4 vecHeading;
                if (plo == D_0038AE90 && ((HERO *)plo)->n1520 == 0x16)
                    *(qword *)&vecHeading = VCALL(qword (*)(void *), plo, 38);
                else
                    *(qword *)&vecHeading = PmatLo(plo)->mat[0];
                vecHeading.z = 0.0f;
                qword qwFallbackHeading = D_00317530;
                qword qwHeadingRaw = *(qword *)&vecHeading;
                qword qwLenHeading = QwLengthUntied(qwHeadingRaw);
                qword qwHeading;
                if (GFromVf(qwLenHeading) < 0.0001f)
                {
                    qwHeading = qwFallbackHeading;
                }
                else
                {
                    __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLenHeading));
                    __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qwHeading) : "j"(qwHeadingRaw));
                }
                *(qword *)&vecHeading = qwHeading;
                *(qword *)&vecTangent = func_001C94E8(pzone, 0, *(qword *)&vecTangent);
                float gAlong = GFromVf(QwDot(*(qword *)&vecHeading, *(qword *)&vecTangent));
                gBlend = gAlong * gAlong * (3.0f - (__builtin_fabsf(gAlong) + __builtin_fabsf(gAlong)));
                gPull = gBlend;
                if ((grftnm & 2) == 0 || 0.0f < gAlong)
                {
                    radPanView = radPanFwdNew;
                    radTiltView = radTiltFwdNew;
                }
                else
                {
                    radPanView = radPanRevNew;
                    radTiltView = radTiltRevNew;
                }
            }
            if (ploPlayer != 0)
            {
                if (((PLAYER *)ploPlayer)->n50C != -1 && ((PLAYER *)ploPlayer)->n508 == 0)
                    gPull *= GMin(GFromVf(QwLengthXY(*(qword *)&vFocus)) * 0.005f, 1.0f);
                else
                    gPull *= GMin(GFromVf(QwLengthXY(*(qword *)&vFocus)) * 0.0016666667f, 1.0f);
            }
            else
            {
                gPull = 0.0f;
            }
            gPull *= p->pcme->gTurn;
            if (pzret->fPullIdle)
            {
                float dtIdle = g_clock.t - (p->tMoveLast + 0.75f);
                float dtQuiet = g_clock.t - (p->tManual + 10.0f);
                float gRamp = pzret->gPullIdle;
                if (pzret->dtPullIdle > 0.0f)
                    gRamp *= func_0011EE68(&D_00341FF0, dtIdle / pzret->dtPullIdle) * func_0011EE68(&D_00341FF0, dtQuiet / pzret->dtPullIdle);
                else if (dtIdle <= 0.0f || dtQuiet <= 0.0f)
                    gRamp = 0.0f;
                if (gPull < gRamp)
                {
                    gBlend = 1.0f;
                    gPull = gRamp;
                }
            }
            if (pzret->fPullEnter && p->fArrived == 0)
            {
                float gEnter = pzret->gPullEnter;
                if (pzret->dtPullEnter > 0.0f)
                    gEnter *= func_0011EE68(&D_00341FF0, (g_clock.t - p->tEnter) / pzret->dtPullEnter);
                if (gPull < gEnter)
                {
                    gBlend = 1.0f;
                    gPull = gEnter;
                }
            }
            float gExtra = __builtin_fabsf(GZOfQw(VCALL(qword (*)(void *), pzone, 39)));
            SMP smpPull;
            smpPull.svFast = D_00329108.svFast * gPull + gExtra;
            smpPull.svSlow = D_00329108.svSlow * gPull + gExtra;
            smpPull.dtFast = D_00329108.dtFast;
            radPanPull = func_0011E840(radPanNew, func_0011E3B8(radPanNew + func_0011E3B8(radPanView - radPanNew)), D_0036BB9C, &smpPull, 0);
            if (__builtin_fabsf(func_0011E3B8(radPanView - radPanPull)) > __builtin_fabsf(func_0011E3B8(radPanView - radPanFree)))
                radPanPull = radPanFree;
        }
        radPanNew = func_0011E3B8(radPanNew + (1.0f - gBlend) * func_0011E3B8(radPanFree - radPanNew) + gBlend * func_0011E3B8(radPanPull - radPanNew));
        float uRate = GLimitRange(GEvaluateClq(&D_003290D0, GFromVfM(QwLengthXY(*(qword *)&vFocus))), D_00341FF0.gMin, D_00341FF0.gMax);
        float uTilt = uRate;
        if (pzret->fTiltIdle)
        {
            float dtIdle = g_clock.t - (p->tMoveLast + 0.75f);
            float dtQuiet = g_clock.t - (p->tManual + 10.0f);
            float gRamp = pzret->gTiltIdle;
            if (pzret->dtTiltIdle > 0.0f)
                gRamp *= func_0011EE68(&D_00341FF0, dtIdle / pzret->dtTiltIdle) * func_0011EE68(&D_00341FF0, dtQuiet / pzret->dtTiltIdle);
            else if (dtIdle <= 0.0f || dtQuiet <= 0.0f)
                gRamp = 0.0f;
            if (uRate < gRamp)
                uTilt = gRamp;
        }
        if (pzret->fTiltEnter && p->fLeft == 0)
        {
            float gEnter = pzret->gTiltEnter;
            if (pzret->dtTiltEnter > 0.0f)
                gEnter *= func_0011EE68(&D_00341FF0, (g_clock.t - p->tEnter) / pzret->dtTiltEnter);
            if (uTilt < gEnter)
                uTilt = gEnter;
        }
        SMP smpTilt;
        smpTilt.svFast = D_00329140.svFast * uTilt;
        smpTilt.svSlow = D_00329140.svSlow * uTilt;
        smpTilt.dtFast = D_00329140.dtFast;
        radTiltNew = func_0011E840(radTiltNew, radTiltView, D_0036BB9C, &smpTilt, 0);
        if (grf3 != 0 && !p->fEntered && !(p->pzone->pshape != 0 && p->pzone->pshape->nD0 == 0 && p->pzone->pshape->nD8 > 2))
        {
            if ((grftnm & 1) != 0 &&
                (func_0011E3B8(p->radPan - p->radPanFwd) * func_0011E3B8(radPanNew - radPanFwdNew) <= 0.0f || __builtin_fabsf(func_0011E3B8(radPanNew - radPanFwdNew)) < 0.0001f) &&
                __builtin_fabsf(func_0011E3B8(radPanNew - radPanFwdNew)) < 1.5707964f &&
                (func_0011E3B8(p->radTilt - p->radTiltFwd) * func_0011E3B8(radTiltNew - radTiltFwdNew) <= 0.0f || __builtin_fabsf(func_0011E3B8(radTiltNew - radTiltFwdNew)) < 0.0001f) &&
                __builtin_fabsf(func_0011E3B8(radTiltNew - radTiltFwdNew)) < 1.5707964f)
            {
                p->nMode = 1;
                p->fLeft = 1;
                p->fArrived = 1;
            }
            else if ((grftnm & 2) != 0 &&
                     (func_0011E3B8(p->radPan - p->radPanRev) * func_0011E3B8(radPanNew - radPanRevNew) <= 0.0f || __builtin_fabsf(func_0011E3B8(radPanNew - radPanRevNew)) < 0.0001f) &&
                     __builtin_fabsf(func_0011E3B8(radPanNew - radPanRevNew)) < 1.5707964f &&
                     (func_0011E3B8(p->radTilt - p->radTiltRev) * func_0011E3B8(radTiltNew - radTiltRevNew) <= 0.0f || __builtin_fabsf(func_0011E3B8(radTiltNew - radTiltRevNew)) < 0.0001f) &&
                     __builtin_fabsf(func_0011E3B8(radTiltNew - radTiltRevNew)) < 1.5707964f)
            {
                p->fLeft = 1;
                p->nMode = 2;
                p->fArrived = 1;
            }
        }
    }
    VECTOR4 avecUnused[6];
    float radPanOut;
    float radTiltOut;
    float sDistOut;
    float uFrameYWant;
    float uFrameXWant;
    switch (p->nMode)
    {
    case 1:
        radPanOut = radPanFwdNew;
        radTiltOut = radTiltFwdNew;
        sDistOut = sDistFwd;
        uFrameXWant = p->pcme->uFrameX;
        uFrameYWant = p->pcme->uFrameY;
        break;
    case 2:
        radPanOut = radPanRevNew;
        radTiltOut = radTiltRevNew;
        sDistOut = sDistRev;
        uFrameXWant = -p->pcme->uFrameX;
        uFrameYWant = p->pcme->uFrameY;
        break;
    case 4:
        radPanOut = radPanNew;
        radTiltOut = radTiltNew;
        if ((grftnm & 3) == 0)
        {
            uFrameYWant = p->pcme->uFrameY;
            uFrameXWant = p->pcme->uFrameX;
            sDistOut = __builtin_fabsf(p->pcme->dsOffset) + cpdefi.dDist;
        }
        else
        {
            float u;
            if ((grftnm & 2) == 0)
            {
                u = 1.0f;
            }
            else if ((grftnm & 1) == 0)
            {
                u = 0.0f;
            }
            else
            {
                if (radPanFwdNew > p->radPan && radPanRevNew > p->radPan)
                {
                    if (radPanRevNew < radPanFwdNew)
                        radPanFwdNew -= 6.2831855f;
                    else
                        radPanRevNew -= 6.2831855f;
                }
                else if (radPanFwdNew < p->radPan && radPanRevNew < p->radPan)
                {
                    if (radPanFwdNew < radPanRevNew)
                        radPanFwdNew += 6.2831855f;
                    else
                        radPanRevNew += 6.2831855f;
                }
                u = (p->radPan - radPanRevNew) / (radPanFwdNew - radPanRevNew);
                u = GSmoothStep(u);
            }
            uFrameYWant = p->pcme->uFrameY;
            sDistOut = u * sDistFwd + (1.0f - u) * sDistRev;
            uFrameXWant = u * p->pcme->uFrameX + (1.0f - u) * -p->pcme->uFrameX;
        }
        break;
    }
    int fFar = 0;
    if (p->pcm->nCut != 0)
    {
        p->dsDist = p->duFrameY = 0.0f;
    }
    else
    {
        if (p->sDist - sDistOut > 400.0f)
            fFar = 1;
        float dtc = g_clock.dt * -8.0f;
        float dtk = g_clock.dt * 15.0f;
        float c = p->pcme->cDist * dtc + 1.0f;
        float k = p->pcme->kDist * dtk;
        p->dsDist = c * p->dsDist + (sDistOut - p->sDist) * k;
        sDistOut = p->sDist + p->dsDist * g_clock.dt;
        p->duFrameY = c * p->duFrameY + (uFrameYWant - p->uFrameY) * k;
        uFrameYWant = p->uFrameY + p->duFrameY * g_clock.dt;
    }
    VECTOR4 dposEye;
    *(qword *)&dposEye = func_0011FDD8(radPanOut, radTiltOut, sDistOut);
    int fBlocked = 0;
    VECTOR4 posEyeWant;
    *(qword *)&posEyeWant = QwAdd(*(qword *)&posHang, *(qword *)&dposEye);
    if (pzone == 0 || pzone->fNoCamClip == 0)
    {
        if (p->pcm->nCut != 0)
            func_00276900(p, *(qword *)&posHang, *(qword *)&posEyeWant, (qword *)&posEyeWant);
        else if (D_00349FA0 == 0)
            *(qword *)&posEyeWant = func_00167660(p->pcm, p->posEye, *(qword *)&posEyeWant, &fBlocked);
    }
    if (!fBlocked || !fFar)
        p->tClear = g_clock.t;
    *(qword *)&dposEye = QwSub(*(qword *)&posEyeWant, *(qword *)&posHang);
    func_00120BA8(*(qword *)&dposEye, &radPanOut, &radTiltOut, &sDistOut);
    p->posEye = *(qword *)&posEyeWant;
    CM *pcmClip = p->pcm;
    *(qword *)&posEyeWant = QwAdd(*(qword *)&posHang, QwMulX(*(qword *)&dposEye, VuFloat((sDistOut + pcmClip->sNearClip) / sDistOut)));
    float radLookX = func_002A3160(uFrameXWant * pcmClip->gTanHalfX);
    float radLookY = -func_002A3160(uFrameYWant * p->pcm->gTanHalfY);
    if (p->fEntered)
    {
        if (p->pcm->nCut != 0)
        {
            p->radPanLook = p->radTiltLook = 0.0f;
        }
        else
        {
            float sXY;
            float z;
            func_00120B00(*(qword *)&dposEye, 0, &sXY, &z);
            float radPanCm;
            float radTiltCm;
            func_0011D048(PmatCm(p->pcm), &radPanCm, &radTiltCm);
            float radPanView = func_0011E3B8(radPanOut + 3.1415927f + radLookX);
            float radTiltView = func_0011E3B8(atan2f(-z, sXY) + radLookY);
            p->radPanLook = func_0011E3B8(radPanCm - radPanView);
            p->radTiltLook = func_0011E3B8(radTiltCm - radTiltView);
        }
        p->dradPanLook = p->dradTiltLook = 0.0f;
    }
    else
    {
        p->dradPanLook += (p->radPanLook * -10.0f + p->dradPanLook * -5.0f) * g_clock.dt;
        p->dradTiltLook += (p->radTiltLook * -10.0f + p->dradTiltLook * -5.0f) * g_clock.dt;
        p->radPanLook += p->dradPanLook * g_clock.dt;
        p->radTiltLook += p->dradTiltLook * g_clock.dt;
    }
    func_00166E48(p->pcm, *(qword *)&posEyeWant, *(qword *)&posHang, radLookX + p->radPanLook, radLookY + p->radTiltLook);
    p->uFrameY = uFrameYWant;
    p->radPan = radPanOut;
    p->radTilt = radTiltOut;
    p->sDist = sDistOut;
    p->radPanFwd = radPanFwdNew;
    p->radTiltFwd = radTiltFwdNew;
    p->radPanRev = radPanRevNew;
    p->radTiltRev = radTiltRevNew;
    p->fReset = 0;
    p->fEntered = 0;
}
