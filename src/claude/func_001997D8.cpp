// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_00173F18): choose a free spawn selector near pos.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword row[3]; };
struct VU_FLOAT { qword qw; };
struct VTE { short d; short pad; unsigned char *(*fn)(void *); };
struct LO {
    char pad0[0xC]; VTE *vt; char pad10[0x28 - 0x10];
    unsigned long padbits : 56, flagbits : 8;
    char pad30[4]; float sRadius;
};
struct POINT { qword pos; qword dir; };
struct SEL { int kind; int unk4; LO *plo; char padC[8]; int cpoint; POINT *apoint; int fBusy; float tUntil; };
struct SET {
    char pad0[0x40]; int csel; SEL *asel; char pad48[0x38];
    int cplo; LO **aplo; int cpos; qword *apos;
};
struct CLOCK { float t, dt; };
struct FRAME { int unk[4]; };
extern "C" {
extern CLOCK g_clock;
FRAME *FrameCtor(FRAME *) __asm__("__3CTX");
void FrameDtor(FRAME *, int) __asm__("_$_3CTX");
extern unsigned char D_00475480[];
extern qword D_00317550;
void func_001DC7E0(int *, void ***);
int func_00198ED8(SET *, qword, int, void **, float);
LO *func_00165B28(void *);
float func_001205C8(qword);
M3 func_0011C8C0(float, qword);
SEL *func_001997D8(SET *pset, qword pos, qword *pposOut, M3 *pmatOut, int *pfFlip);
}
static inline unsigned char *Matrix(LO *plo)
{
    VTE *e = &plo->vt[36];
    return e->fn((char *)plo + e->d);
}
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline qword QwSubFrom(const qword &qw0, qword qw1)
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
    __asm__("qmfc2.ni %0, %1" : "=r"(x) : "j"(qw));
    return x;
}
static inline qword QwScaleX(qword qwVec, const VU_FLOAT &g)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(qwVec), "j"(g.qw));
    return qw;
}
static inline qword QwRotateVecAt(M3 *pmat, qword *pqwVec)
{
    qword qwResult;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(qwResult)
            : "j"(*pqwVec), "j"(pmat->row[0]), "j"(pmat->row[1]), "j"(pmat->row[2]));
    return qwResult;
}
static inline float SLengthXY(qword qw)
{
    qword qwT;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qwT) : "j"(qw));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwT) : "j"(qwT));
    return GXOfQw(qwT);
}

extern "C" SEL *func_001997D8(SET *pset, qword pos, qword *pposOut, M3 *pmatOut, int *pfFlip)
{
    FRAME frame;
    union { struct VECTOR4 { float x, y, z, w; } v; qword q; } posBest;
    M3 matBest;
    int cplo;
    void **aplo;

    float sRadiusMin = 3.40282347e+38f;
    for (int i = 0; i < pset->cplo; i++)
    {
        float s = pset->aplo[i]->sRadius;
        sRadiusMin = sRadiusMin < s ? sRadiusMin : s;
    }
    SEL *pselBest;
    int fFlip = 0;
    FrameCtor(&frame);
    func_001DC7E0(&cplo, &aplo);
    pselBest = 0;
    float sBest = 3.40282347e+38f;

    for (int i = 0; i < pset->csel; i++)
    {
        SEL *psel = &pset->asel[i];
        LO *plo;
        if (psel->fBusy)
            goto next;
        if (g_clock.t < psel->tUntil)
            goto next;
        plo = psel->plo;
        if (!plo)
            goto next;
        {
            int fEnabled = (int)(*(unsigned long *)((char *)plo + 0x28) >> 56) & 1;
            if (!fEnabled)
                goto next;
        }
        switch (psel->kind)
        {
        case 0:
        case 2:
        {
            float sRadius;
            qword posObj;
            M3 mat;
            switch (psel->kind)
            {
            case 0:
                posObj = *(qword *)(Matrix(psel->plo) + 0x30);
                mat = *(M3 *)Matrix(psel->plo);
                sRadius = psel->plo->sRadius;
                break;
            case 2:
                sRadius = sRadiusMin;
                posObj = *(qword *)(Matrix(psel->plo) + 0x30);
                mat = *(M3 *)Matrix(psel->plo);
                break;
            }
            float sDist = SLengthXY(QwSubFrom(pos, posObj));
            if (sDist < 1500.0f || sBest < sDist)
                goto next;
            for (int j = 0; j < pset->cpos; j++)
            {
                if (!func_00198ED8(pset, QwAdd(posObj, QwRotateVecAt(&mat, &pset->apos[j])), cplo, aplo, sRadius))
                    goto next;
            }
            sBest = sDist;
            pselBest = psel;
            posBest.q = posObj;
            matBest = mat;
            break;
        }
        case 1:
        {
            qword dirCam = *(qword *)Matrix(func_00165B28(D_00475480));
            for (int k = 0; k < psel->cpoint; k++)
            {
                POINT *ppoint = &psel->apoint[k];
                qword posCurve = ppoint->pos;
                float sDist = SLengthXY(QwSubFrom(pos, posCurve));
                if (sDist < 1500.0f || sBest < sDist)
                    continue;
                qword dirCurve = ppoint->dir;
                int fFlipT = GXOfQw(QwDot(dirCam, dirCurve)) < 0.0f;
                if (!fFlipT)
                {
                    VU_FLOAT gNeg = VuFloat(-1.0f);
                    dirCurve = QwScaleX(dirCurve, gNeg);
                }
                M3 matCurve = func_0011C8C0(func_001205C8(dirCurve), D_00317550);
                int j;
                for (j = 0; j < pset->cpos; j++)
                {
                    if (!func_00198ED8(pset, QwAdd(posCurve, QwRotateVecAt(&matCurve, &pset->apos[j])), cplo, aplo, sRadiusMin))
                        goto fail;
                }
                fail:
                if (j >= pset->cpos)
                {
                    sBest = sDist;
                    fFlip = fFlipT;
                    pselBest = psel;
                    posBest.q = posCurve;
                    matBest = matCurve;
                }
            }
            break;
        }
        }
    next:;
    }
    *pposOut = posBest.q;
    *pmatOut = matBest;
    *pfFlip = fFlip;
    FrameDtor(&frame, 2);
    return pselBest;
}
