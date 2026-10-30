// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
/* Port of Sly 2 src/hand/func_001428D8.cpp (HeroInteractDistance); owns the CLQ rodata 0x3205C0..0x3205FF. */
typedef int qword __attribute__((mode(TI)));
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct LO { char pad[0xC]; VT *pvt; };
struct POCTL { char pad[0x8]; float sLeft; };
struct STEPPLAYER { char pad[0xC]; VT *pvt; char pad1[0x134 - 0x10]; POCTL *pctl; char pad2[0x110C - 0x138]; float radLeft; };
struct VU_VECTOR4 { qword qw; };
static const CLQ s_clqBiasXY = { -200.0f, -0.2f, 0.0f, 0.0f };
static const CLQ s_clqBiasZ = { 0.0f, -0.2f, 0.0f, 0.0f };
static const CLQ s_clqAway = { 0.5f, -0.5f, 0.0f, 0.0f };
static const CLQ s_clqStick = { -500.0f, -0.5f, 0.0f, 0.0f };
extern "C" {
extern LM D_00341FF0;
qword func_0011FD70(float rad, float sXY, float sZ);
void func_00155380(STEPPLAYER *pstepplayer, LO *plo, LO **pploCur, float *psDist, float *pdz);
}
static inline qword PosLoWorld(void *p) { LO *plo = (LO *)p; return plo->pvt->e120.pfn((char *)plo + plo->pvt->e120.d)->r[3]; }
static inline float GEvaluateClq(const CLQ *pclq, float x) { return pclq->g0 + x * (pclq->g1 + x * pclq->g2); }
static inline qword QwSub(qword qw0, qword qw1) { qword qw; __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1)); return qw; }
static inline float GFromVf(qword qw) { float g; __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw)); return g; }
static inline qword QwDot(qword a, qword b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline float GZOfQw(qword qw) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(qw)); return z; }
static inline VU_VECTOR4 SubPos(qword a, qword b) { VU_VECTOR4 r; r.qw = QwSub(a, b); return r; }
static inline qword QwLengthXYTwice(qword v)
{
    qword qw;
    __asm__("vmul.xy %0, %1, %2\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GXOfQwVf(qword qw) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw), "j"(qw)); return x; }
static inline float GEvaluateClqLm(const CLQ *pclq, LM *plm, float x)
{
    float g = pclq->g0 + x * (pclq->g1 + x * pclq->g2);
    float gMin = plm->gMin;
    float gMax = plm->gMax;
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}

void func_00155380(STEPPLAYER *pstepplayer, LO *plo, LO **pploCur, float *psDist, float *pdz)
{
    float sBias = 0.0f;
    float zBias = 0.0f;
    qword posHero = PosLoWorld(pstepplayer);
    VU_VECTOR4 vecS = SubPos(posHero, PosLoWorld(plo));
    qword vec = vecS.qw;
    float dz = GZOfQw(vec);
    float sXY = GFromVf(QwLengthXYTwice(vec));
    if ((LO *)pstepplayer == *pploCur) {
        sBias = GEvaluateClq(&s_clqBiasXY, sXY);
        zBias = GEvaluateClq(&s_clqBiasZ, dz);
    }
    POCTL *pctl = pstepplayer->pctl;
    if (pctl != 0 && sXY > 0.0001f) {
        qword qwStick = func_0011FD70(pstepplayer->radLeft, pctl->sLeft, 0.0f);
        float rAway = GXOfQwVf(QwDot(qwStick, vec)) / sXY;
        sBias += GEvaluateClqLm(&s_clqAway, &D_00341FF0, rAway) * GEvaluateClq(&s_clqStick, sXY);
    }
    sXY += sBias;
    dz += zBias;
    if (psDist != 0)
        *psDist = sXY;
    if (pdz != 0)
        *pdz = dz;
}
