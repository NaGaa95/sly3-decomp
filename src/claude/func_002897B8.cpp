// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002897B8 (agent A69): Sly 3 form of Sly 1's UpdateWrStateVectors / Sly 2 func_0022B7D8, per warp group: (WR *pwr, WRBG *pwrbg).
// The envelope space is the inverse of weki.dmat with the unused axes' columns zeroed per WEK (jump table) and scaled by 1/16;
// the world matrix (glob XF, times the glob's extra matrix, optionally relative to the WR's LO position) is scaled by 1/16 too.
// Vertex positions are integer vectors (cvt.s.w). Per vertex: weight u (linear CLQ of the distance, limited to the LM), then for
// every warp entry whose stamp is newer than the group's: u == 0 -> both state floats 0; circle -> cos/sin of the wave phase * u;
// bend -> 1. The group then takes the WR's stamp. Struct names follow the Sly 2 source.
// Matching notes: the packed vertex is a VU_VECTOR pseudo with a dead VECTOR home store (sqc2 0xA0); posWorld is a plain qword
// (reload spill 0x1110); the relative-position update is an inline taking &matWorld (pointer s-regs before the vtable call);
// GFromVu is a single mtc1 asm with an "r" qword input so gcc emits the qmfc2 (sched order of the rScale multiply).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;

struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct IVECTOR { int x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
struct VU_FLOAT { qword q; VU_FLOAT(float g) { __asm__("mfc1 %0,%1" : "=r"(q) : "f"(g)); } };
struct VU_VECTOR
{
    qword q;
    VU_VECTOR() {}
    VU_VECTOR(qword qw) { q = qw; }
    VU_VECTOR(const VECTOR &vec) { q = *(const qword *)&vec; }
};
struct CLQ { float g0, g1, g2, g3; };
struct LM { float gMin, gMax; };
struct XF { MATRIX4 mat; MATRIX4 matWorld; };
struct GLOB { int oid; XF *pxf; MATRIX4 *pmat; };
struct WEKI { int wek; float sInner; float uInner; float sOuter; float uOuter; int unk14[3]; MATRIX4 dmat; };
struct WARPVTX { float ag[4]; };
struct WRBGBATCH { int cvtx; IVECTOR *apos; WARPVTX *apwarpvtx[4]; WRBGBATCH *pwrbgbatchNext; };
struct WRBG { void *pso; GLOB *pglob; int unk08[5]; int fRelative; int unk20[4]; WEKI weki; WRBGBATCH *pwrbgbatchFirst; int unk94[2]; int stamp; };
struct WRE { int wrek; int imat; int column; int stamp; int unk10[4]; VECTOR axis; int unk30[16]; float spatialFrequency; int unk74[3]; };
struct VTE { short delta, pad; MATRIX4 *(*pfn)(void *); };
struct LO { char pad0[0xC]; VTE *vt; };
struct WR { char pad0[0x44]; int cwre; int unk48; int stamp; char pad50[0x10]; WRE awre[12]; char pad660[0x688 - 0x660]; LO *plo; };

extern "C" {
MATRIX4 func_0011D768(const MATRIX4 *);
MATRIX4 func_0011D558(const MATRIX4 &, const MATRIX4 &);
qword *func_002BA818(qword *, qword);
void CopyAb(void *pvDst, const void *pvSrc, uint cb);
float func_0011E3B8(float);
void func_0011EB28(float g, float *ps, float *pc);
}
MATRIX4 operator*(const MATRIX4 &m, VU_FLOAT s) __asm__("func_0011D518");

static inline MATRIX4 *GetMatrix(LO *p) { return p->vt[36].pfn((char *)p + p->vt[36].delta); }
static inline qword QwTransformPos(const MATRIX4 &mat, qword qwPos)
{
    qword qw;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(qw)
            : "j"(*(qword *)mat.mat[0]), "j"(*(qword *)mat.mat[1]), "j"(*(qword *)mat.mat[2]), "j"(*(qword *)mat.mat[3]), "j"(qwPos));
    return qw;
}
static inline float GFromVf(qword qw)
{
    float g;
    int n;
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(qw));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(n));
    return g;
}
static inline qword QwLength(qword v)
{
    qword qw, vfOne;
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=&j"(vfOne) : "0"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GMin(float g0, float g1) { return g0 < g1 ? g0 : g1; }
static inline float GMax(float g0, float g1) { return g0 > g1 ? g0 : g1; }
static inline float GLimit(float g, float gMin, float gMax)
{
    if (g < gMin)
        g = gMin;
    else if (gMax < g)
        g = gMax;
    return g;
}
static inline void SetLm(LM *plm, const float &g0, const float &g1)
{
    plm->gMin = GMin(g0, g1);
    plm->gMax = GMax(g0, g1);
}
static inline void FitLinearClq(CLQ *pclq, const float &s0, const float &u0, const float &s1, const float &u1)
{
    pclq->g1 = (u0 - u1) / (s0 - s1);
    pclq->g0 = u0 - pclq->g1 * s0;
    pclq->g2 = 0.0f;
}
static inline VU_VECTOR operator*(const MATRIX4 &mat, VU_VECTOR pos)
{
    qword qw;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(qw)
            : "j"(VU_VECTOR(*(VECTOR *)mat.mat[0]).q), "j"(VU_VECTOR(*(VECTOR *)mat.mat[1]).q),
              "j"(VU_VECTOR(*(VECTOR *)mat.mat[2]).q), "j"(VU_VECTOR(*(VECTOR *)mat.mat[3]).q), "j"(pos.q));
    return VU_VECTOR(qw);
}
static inline VU_VECTOR operator-(VU_VECTOR vec0, VU_VECTOR vec1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(vec0.q), "j"(vec1.q));
    return VU_VECTOR(qw);
}
struct VU_DOT { qword q; };
static inline VU_DOT VuDot(VU_VECTOR vec0, VU_VECTOR vec1)
{
    VU_DOT g;
    qword qw, vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(vec0.q), "j"(vec1.q));
    g.q = qw;
    return g;
}
static inline VU_VECTOR Normalize(VU_VECTOR vec)
{
    qword qwLength = VuDot(vec, vec).q, qwNormal;
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLength) : "0"(qwLength));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qwNormal) : "j"(qwLength), "j"(vec.q));
    return VU_VECTOR(qwNormal);
}
static inline float GFromVu(VU_DOT g)
{
    float gResult;
    __asm__("mtc1 %1, %0" : "=f"(gResult) : "r"(g.q));
    return gResult;
}
static inline qword ToVf(qword q) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(q)); return r; }
static inline qword Pack(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}

static inline void SubPos(MATRIX4 *pmat, LO *plo)
{
    qword pos = *(qword *)pmat->mat[3];
    func_002BA818((qword *)pmat->mat[3], (VU_VECTOR(pos) - VU_VECTOR(*(VECTOR *)GetMatrix(plo)->mat[3])).q);
    pmat->mat[3][3] = 1.0f;
}
extern "C" void func_002897B8(WR *pwr, WRBG *pwrbg)
{
    MATRIX4 dmat;
    CLQ clq;
    LM lm;
    if (pwrbg->weki.wek != -1) {
        dmat = func_0011D768(&pwrbg->weki.dmat);
        SetLm(&lm, pwrbg->weki.uInner, pwrbg->weki.uOuter);
        FitLinearClq(&clq, pwrbg->weki.sInner, pwrbg->weki.uInner, pwrbg->weki.sOuter, pwrbg->weki.uOuter);
        switch (pwrbg->weki.wek) {
        case 0:
            break;
        case 1:
            dmat.mat[0][2] = dmat.mat[1][2] = dmat.mat[2][2] = dmat.mat[3][2] = 0.0f;
            break;
        case 2:
            dmat.mat[0][1] = dmat.mat[1][1] = dmat.mat[2][1] = dmat.mat[3][1] = 0.0f;
            break;
        case 3:
            dmat.mat[0][0] = dmat.mat[1][0] = dmat.mat[2][0] = dmat.mat[3][0] = 0.0f;
            break;
        case 4:
            dmat.mat[0][1] = dmat.mat[1][1] = dmat.mat[2][1] = dmat.mat[3][1] = 0.0f;
            dmat.mat[0][2] = dmat.mat[1][2] = dmat.mat[2][2] = dmat.mat[3][2] = 0.0f;
            break;
        case 5:
            dmat.mat[0][0] = dmat.mat[1][0] = dmat.mat[2][0] = dmat.mat[3][0] = 0.0f;
            dmat.mat[0][2] = dmat.mat[1][2] = dmat.mat[2][2] = dmat.mat[3][2] = 0.0f;
            break;
        case 6:
            dmat.mat[0][0] = dmat.mat[1][0] = dmat.mat[2][0] = dmat.mat[3][0] = 0.0f;
            dmat.mat[0][1] = dmat.mat[1][1] = dmat.mat[2][1] = dmat.mat[3][1] = 0.0f;
            break;
        }
        dmat = dmat * VU_FLOAT(0.0625f);
    }
    MATRIX4 matWorld = pwrbg->pglob->pxf->matWorld;
    if (pwrbg->pglob->pmat)
        matWorld = func_0011D558(matWorld, *pwrbg->pglob->pmat);
    if (pwrbg->fRelative) {
        SubPos(&matWorld, pwr->plo);
    }
    matWorld = matWorld * VU_FLOAT(0.0625f);

    for (WRBGBATCH *pwrbgbatch = pwrbg->pwrbgbatchFirst; pwrbgbatch; pwrbgbatch = pwrbgbatch->pwrbgbatchNext) {
        IVECTOR apos[256];
        CopyAb(apos, pwrbgbatch->apos, pwrbgbatch->cvtx * sizeof(IVECTOR));
        for (int ivtx = 0; ivtx < pwrbgbatch->cvtx; ivtx++) {
            IVECTOR *pipos = &apos[ivtx];
            VU_VECTOR v(Pack((float)pipos->x, (float)pipos->y, (float)pipos->z));
            VECTOR pos;
            *(VU_VECTOR *)&pos = v;
            float u;
            if (pwrbg->weki.wek == -1)
                u = 1.0f;
            else {
                float s = GFromVf(QwLength(QwTransformPos(dmat, v.q)));
                u = GLimit(clq.g0 + s * (clq.g1 + s * clq.g2), lm.gMin, lm.gMax);
            }
            qword posWorld = (matWorld * v).q;
            for (int iwre = 0; iwre < pwr->cwre; iwre++) {
                WRE *pwre = &pwr->awre[iwre];
                if (pwre->wrek == -1)
                    continue;
                if (pwre->stamp <= pwrbg->stamp)
                    continue;
                WARPVTX *pwarpvtx = &pwrbgbatch->apwarpvtx[pwre->imat][ivtx];
                if (u == 0.0f) {
                    pwarpvtx->ag[pwre->column] = 0.0f;
                    pwarpvtx->ag[pwre->column + 1] = 0.0f;
                } else
                    switch (pwre->wrek) {
                    case 0: {
                        float gSin, gCos;
                        VU_DOT gDot = VuDot(VU_VECTOR(posWorld), Normalize(VU_VECTOR(pwre->axis)));
                        float rScale = pwre->spatialFrequency * 6.2831855f;
                        float rad = GFromVu(gDot) * rScale;
                        func_0011EB28(func_0011E3B8(rad), &gSin, &gCos);
                        pwarpvtx->ag[pwre->column] = gCos * u;
                        pwarpvtx->ag[pwre->column + 1] = gSin * u;
                        break;
                    }
                    case 1:
                        pwarpvtx->ag[pwre->column] = 1.0f;
                        break;
                    }
            }
        }
    }
    pwrbg->stamp = pwr->stamp;
}
