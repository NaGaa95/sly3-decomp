// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001AACD8: hero lean update (cf. Sly 2 UpdateJtLean, func_00189618).
typedef int qword __attribute__((mode(TI)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
struct M4 { qword r[4]; };
struct XF;
struct LO;
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE eMat; VTE eXf; VTE eVel; };
struct LO { char pad[0xC]; VT *pvt; };
struct SHAPE : LO { char pad1[0xD4 - 0x10]; int fClosed; char pad2[0x1CC - 0xD8]; int nUnk1cc; };
struct XP { char pad[0x4C]; LO *psoLeaf; };
struct ACT;
struct ACT1;
struct ACTV { char pad[0x28]; float g28; };
struct ASEGBL;
struct BL { float gWeight; int pad[2]; };
struct SMPA { float svFast, svSlow, dtFast, sdvMax; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct CLOCK { float t; float dt; };
struct JT {
    char pad0[0x1C0];
    MATRIX3 matTarget;  /* 0x1C0 */
    char pad1[0x218 - 0x1F0];
    XP *pxpFloor;       /* 0x218 */
    char pad2[0x240 - 0x21C];
    qword posCur;       /* 0x240 */
    char pad3[0x508 - 0x250];
    int nState;         /* 0x508 */
    int nKind;          /* 0x50C */
    int pad510;
    LO *plo;            /* 0x514 */
    int pad518;
    float uParam;       /* 0x51C */
    float sParam;       /* 0x520 */
    int fFlip;          /* 0x524 */
    char pad4[0x7F0 - 0x528];
    BL ablC[3];         /* 0x7F0 */
    ASEGBL *pasegblC;   /* 0x814 */
    float gLean;        /* 0x818 */
    float dgLean;       /* 0x81C */
    char pad5[0x10D4 - 0x820];
    int jtas;           /* 0x10D4 */
    char pad6[0x19E0 - 0x10D8];
    int jts;            /* 0x19E0 */
    char pad7[0x1AEC - 0x19E4];
    ACT *pact19e4;      /* 0x1AEC */
    ACT *pact19e8;      /* 0x1AF0 */
    ACT *pact19ec;      /* 0x1AF4 */
    ACTV *pact19f0;     /* 0x1AF8 */
    ACTV *pact19f4;     /* 0x1AFC */
};
extern "C" {
extern qword D_00317560;
extern qword D_00317550;
extern float D_003456BC, D_003456C0, D_003456C4, D_003456C8, D_003456CC, D_003456E0;
extern CLQ D_003456F0;
extern SMPA D_00322460;
extern CLQ D_00322470;
extern LM D_00341FF0;
extern CLOCK g_clock;
int func_0012F448(ACT *pact);
int func_00156998(JT *pjt);
void func_0012FE90(ACT *pact, qword qwNew);
void func_0022E148(SHAPE *pshape, float u, qword *ppos, qword *pdir);
float func_0022DFD8(SHAPE *pshape);
float func_0011EDB8(float a, float b);
float func_0022DFB0(SHAPE *pshape);
void func_0022E330(SHAPE *pshape, float s, qword *ppos, qword *pdir);
float func_0011FE60(qword qwVec, qword qwOnto, qword *pqwAlong, qword *pqwAcross);
float func_0011E730(float gCur, float dgCur, float gTarget, float dt, SMPA *psmpa, float *pdgNext);
void func_00148938(ASEGBL *pasegbl);
qword func_0028BCD0(XF *pxfFrom, XF *pxfTo, qword qwPos);
}
static inline M4 *Matrix(LO *p) { VTE *e = &p->pvt->eMat; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline XF *PxfLocal(LO *p, void *pm) { VTE *e = &p->pvt->eXf; return ((XF *(*)(void *, void *))e->pfn)((char *)p + e->d, pm); }
static inline qword GetVelocity(LO *p) { VTE *e = &p->pvt->eVel; return ((qword (*)(void *))e->pfn)((char *)p + e->d); }
static inline float GEvaluateClq(CLQ *pclq, float x) { return pclq->g0 + x * (pclq->g1 + x * pclq->g2); }
struct VU_FLOAT { qword qw; };
// Float held in a GPR (from qmfc2) copied into a qword GPR: VU_FLOAT register-class move helper.
static inline VU_FLOAT VuFloatI(float g) { VU_FLOAT v; __asm__("daddu %0, %1, $0" : "=r"(v.qw) : "r"(g)); return v; }
static inline VU_FLOAT VuFloatR(float g) { VU_FLOAT v; __asm__("" : "=r"(v.qw) : "0"(g)); return v; }
static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g)); return v; }
static inline VU_FLOAT VuFloatFromMemWord(int n) { VU_FLOAT v; __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "rV"(n)); return v; }
static inline qword QwSub(qword qw0, qword qw1) { qword qw; __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1)); return qw; }
static inline float GFromVf(qword qw) { float g; __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw)); return g; }
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwLengthXY(qword v)
{
    qword qw;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GLengthXY(qword v) { return GFromVf(QwLengthXY(v)); }
static inline qword QwDot(qword a, qword b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwLengthDot(qword v)
{
    qword qw = QwDot(v, v);
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwNormalizeDot(qword v)
{
    qword qw = QwLengthDot(v);
    qword qwNormal;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qwNormal) : "j"(qw), "j"(v));
    return qwNormal;
}
static inline qword QwNormalize(qword v)
{
    qword qw = QwLength(v);
    qword qwNormal;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qwNormal) : "j"(qw), "j"(v));
    return qwNormal;
}
static inline qword QwCross(qword a, qword b)
{
    qword qw;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline float GMaxOf(float a, float b) { return (a > b) ? a : b; }
static inline float GMinOf(float a, float b) { return (a < b) ? a : b; }
static inline float GLimitG(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static inline qword QwScale(qword qwVec, VU_FLOAT gScale)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(qw) : "j"(gScale.qw), "j"(qwVec));
    return qw;
}
static inline qword QwDotRowsMatP(MATRIX3 *pmat, qword qwV)
{
    qword qwLocal;
    qword qwTmp0, qwTmp1, qwTmp2, qwOnes;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\tvadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(qwLocal), "=&j"(qwOnes), "=&j"(qwTmp0), "=&j"(qwTmp1), "=&j"(qwTmp2)
            : "j"(*(qword *)pmat->mat[0]), "j"(*(qword *)pmat->mat[1]), "j"(*(qword *)pmat->mat[2]), "j"(qwV));
    return qwLocal;
}
static inline qword QwFromXyzV(float gX, float gY, float gZ)
{
    qword qwXYZ;
    int iTmp;
    __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
            : "=&r"(qwXYZ), "=&r"(iTmp) : "f"(gX), "f"(gY), "f"(gZ));
    VECTOR4 vecXyz;
    *(qword *)&vecXyz = qwXYZ;
    return *(qword *)&vecXyz;
}
extern "C" void func_001AACD8(JT *pjt)
{
    VECTOR4 vecDv;
    VECTOR4 vecPos;
    VECTOR4 vecDir;
    VECTOR4 vecLean;
    VECTOR4 vecLocal;
    *(qword *)&vecDv = D_00317560;
    LO *plo = 0;
    if (!pjt->pact19e4)
        return;
    if (!func_0012F448(pjt->pact19e4))
        return;
    if (func_00156998(pjt))
    {
        func_0012FE90(pjt->pact19e4, D_00317560);
        func_0012FE90(pjt->pact19e8, D_00317560);
        func_0012FE90(pjt->pact19ec, D_00317560);
        return;
    }
    switch (pjt->jts)
    {
    case 0:
        if (pjt->pxpFloor)
        {
            plo = pjt->pxpFloor->psoLeaf;
            *(qword *)&vecPos = pjt->posCur;
        }
        break;
    case 8:
        if (pjt->nKind == 0)
        {
            switch (pjt->nState)
            {
            case 4:
                plo = pjt->plo;
                *(qword *)&vecPos = Matrix(plo)->r[3];
                break;
            case 3:
            {
                SHAPE *pshape = (SHAPE *)pjt->plo;
                func_0022E148(pshape, pjt->uParam, (qword *)&vecPos, (qword *)&vecDir);
                plo = pshape;
                if (((SHAPE *)plo)->nUnk1cc)
                {
                    *(qword *)&vecDir = QwNormalizeDot(*(qword *)&vecDir);
                    qword qwVel = GetVelocity((LO *)pjt);
                    float gSpeed = GFromVf(QwDot(qwVel, *(qword *)&vecDir));
                    *(qword *)&vecLean = QwScale(*(qword *)&vecDir, VuFloatI(gSpeed));
                    float sAhead = pjt->sParam + gSpeed * D_003456BC;
                    float sMax = func_0022DFD8((SHAPE *)plo);
                    if (((SHAPE *)plo)->fClosed)
                    {
                        sAhead = func_0011EDB8(sAhead, sMax);
                    }
                    else
                    {
                        float sMin = func_0022DFB0((SHAPE *)plo);
                        if (sAhead < sMin)
                            sAhead = sMin;
                        else if (sMax < sAhead)
                            sAhead = sMax;
                    }
                    func_0022E330(pshape, sAhead, 0, (qword *)&vecDir);
                    *(qword *)&vecLocal = QwScale(QwNormalize(*(qword *)&vecDir), VuFloatI(gSpeed));
                    *(qword *)&vecDv = QwSub(*(qword *)&vecLocal, *(qword *)&vecLean);
                    if (pjt->pasegblC)
                    {
                        VECTOR4 vecAcross;
                        *(qword *)&vecAcross = QwNormalizeDot(QwCross(D_00317550, *(qword *)&vecDir));
                        float gAcross = func_0011FE60(*(qword *)&vecDv, *(qword *)&vecAcross, 0, (qword *)&vecDv);
                        float g = GLimitG(gAcross / D_003456C0, -1.0f, 1.0f);
                        if (pjt->fFlip)
                            g = -g;
                        float gLean = func_0011E730(pjt->gLean, pjt->dgLean, g * (2.0f - __builtin_fabsf(g)), g_clock.dt, &D_00322460, &pjt->dgLean);
                        pjt->gLean = gLean;
                        float gZero = 0.0f;
                        float gOne = 1.0f;
                        pjt->ablC[0].gWeight = GMaxOf(gZero, gLean);
                        pjt->ablC[2].gWeight = GMaxOf(gZero, -gLean);
                        pjt->ablC[1].gWeight = (gOne - pjt->ablC[0].gWeight) - pjt->ablC[2].gWeight;
                        func_00148938(pjt->pasegblC);
                    }
                }
                break;
            }
            }
        }
        break;
    }
    if (!plo)
        return;
    *(qword *)&vecDir = func_0028BCD0(PxfLocal(plo, 0), 0, *(qword *)&vecPos);
    *(qword *)&vecLocal = QwDotRowsMatP(&pjt->matTarget, *(qword *)&vecDir);
    float gLen = GLengthXY(*(qword *)&vecLocal);
    if (gLen > 0.0001f)
    {
        float k = GEvaluateClq(&D_003456F0, GMinOf(gLen / D_003456E0, 1.0f));
        float gMin = D_00341FF0.gMin, gMax = D_00341FF0.gMax;
        if (k < gMin)
            k = gMin;
        else if (gMax < k)
            k = gMax;
        float gX = vecLocal.x * D_003456C4 * k / gLen;
        float gY = vecLocal.y * D_003456C4 * k / gLen;
        float gZ = D_003456C8 * k * k;
        vecLean.x = gX;
        vecLean.y = gY;
        vecLean.z = gZ;
    }
    else
    {
        vecLean.z = 0.0f;
        vecLean.y = 0.0f;
        vecLean.x = 0.0f;
    }
    float gFootL = GEvaluateClq(&D_00322470, pjt->pact19f0->g28);
    float gFootR = GEvaluateClq(&D_00322470, pjt->pact19f4->g28);
    float gZ = vecLean.z;
    if (gZ < gFootL && gZ < gFootR)
        gFootR = gZ;
    else if (gFootL < gFootR)
        gFootR = gFootL;
    func_0012FE90(pjt->pact19e4, QwFromXyzV(vecLean.x, vecLean.y, gFootR));
    qword qwHalf = QwScale(*(qword *)&vecLean, VuFloatFromMemWord(*(int *)&D_003456CC));
    if (pjt->jtas == -1)
    {
        func_0012FE90(pjt->pact19ec, qwHalf);
        func_0012FE90(pjt->pact19e8, qwHalf);
    }
    else
    {
        func_0012FE90(pjt->pact19ec, D_00317560);
        func_0012FE90(pjt->pact19e8, D_00317560);
    }
}
