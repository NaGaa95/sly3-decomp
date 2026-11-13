// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned char uchar;
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX3 { VECTOR mat[3]; };
struct MATRIX4 { VECTOR mat[3]; VECTOR pos; };
struct VU_FLOAT { qword qw; };
struct RGBA
{
    uchar r, g, b, a;
    RGBA(uint bits) { *(uint *)this = bits; }
};
struct XF { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct LO { char pad[0xC]; VT *pvt; };
struct SO { char pad[0xC]; VT *pvt; char pad10[0x90 - 0x10]; float sRadius; };
struct TASK { char pad[0x60]; int idLabelName; };
struct ATTACH { char pad[0x6C]; TASK *ptask; };
struct ENT { LO *plo; int frame; float sHeight; };
struct WAYPT
{
    char pad[0xC]; VT *pvt; char pad10[0x140 - 0x10];
    ATTACH *pattach;        // 0x140
    char pad144[4];
    LO *ploSource;          // 0x148
    SO *psoMarker;          // 0x14C
    SO *psoBeam;            // 0x150
    SO *psoBase;            // 0x154
    char pad158[4];
    int cent;               // 0x15C
    ENT aent[4];            // 0x160
};
extern char D_00475480[];
extern qword D_00317550;
extern "C" {
void func_0023CC40(WAYPT *);
int func_00282750(WAYPT *);
void func_00281E70(WAYPT *);
void func_00281F98(WAYPT *);
int func_00282870(WAYPT *, LO *, float *, float *, float *);
void *func_00165B48(void *, LO *);
qword func_001C8548(void *);
void *func_00291E8C(void *, const void *, int);
VECTOR *func_002BA818(VECTOR *pv, qword qw);
void func_001C8248(SO *pso, qword q, MATRIX4 *pmat, float a, float b);
void func_001C8328(SO *pso, float s, qword q, float a, qword pos0, qword pos1);
char *func_00150630(void *, int id);
void func_002099A8(LO *plo, qword pos, float s, char *pchz, const RGBA *prgba0, const RGBA *prgba1);
}
static inline XF *XfOf(LO *p) { VTE *e = &p->pvt->e120; return (XF *)e->pfn((char *)p + e->d); }
static inline qword PosOfLo(LO *p) { return XfOf(p)->pos; }
static inline MATRIX3 *MatOf(SO *p) { VTE *e = &p->pvt->e120; return (MATRIX3 *)e->pfn((char *)p + e->d); }
static inline void DrawLabel(LO *plo, qword pos, RGBA rgba0, RGBA rgba1, int id, float s) { func_002099A8(plo, pos, s, func_00150630(D_00475480, id), &rgba0, &rgba1); }

static inline float GLimitG(float g, float gMin, float gMax)
{
    float gRet;
    if (g < gMin)
        gRet = gMin;
    else if (gMax < g)
        gRet = gMax;
    else
        gRet = g;
    return gRet;
}
static inline float GMax(float a, float b) { return a > b ? a : b; }
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline VU_FLOAT VuFloatFromMemWord(int n)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "rV"(n));
    return v;
}
static inline qword QwAddScaled(qword qwBase, qword qwVec, VU_FLOAT g)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(qwBase), "j"(qwVec), "j"(g.qw));
    return qw;
}
// The same sum with the scalar as the first asm input: the result then takes the dying scalar's vf register (name plate offset)
static inline qword QwAddScaledG(qword qwBase, qword qwVec, VU_FLOAT g)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %2, $vf0\n\tvmaddx.xyzw %0, %3, %1x" : "=j"(qw) : "j"(g.qw), "j"(qwBase), "j"(qwVec));
    return qw;
}
static inline qword QwMulX(qword qwRow, VU_FLOAT g)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(qw) : "j"(g.qw), "j"(qwRow));
    return qw;
}
inline MATRIX3 operator*(const MATRIX3 &mat, VU_FLOAT g) return matRes
{
    MATRIX3 matT;
    *(qword *)&matT.mat[0] = QwMulX(*(qword *)&mat.mat[0], g);
    *(qword *)&matT.mat[1] = QwMulX(*(qword *)&mat.mat[1], g);
    *(qword *)&matT.mat[2] = QwMulX(*(qword *)&mat.mat[2], g);
    matRes = matT;
}


extern "C" void func_00282B38(WAYPT *pwaypt)
{
    func_0023CC40(pwaypt);
    if (!func_00282750(pwaypt))
        return;
    func_00281E70(pwaypt);
    func_00281F98(pwaypt);
    for (int i = 0; i < pwaypt->cent; i++) {
        MATRIX4 mat;
        ENT *pent = &pwaypt->aent[i];
        LO *plo = pent->plo;
        float rScale, uShow, uLabel;
        if (!func_00282870(pwaypt, plo, &rScale, &uShow, &uLabel))
            continue;
        qword q = func_001C8548(func_00165B48(D_00475480, plo));
        qword pos = pwaypt->ploSource ? PosOfLo(pwaypt->ploSource) : PosOfLo((LO *)pwaypt);
        // the beam start is a memory copy of pos (sq at 0xC0); "r"(pos) keeps pos in a GPR
        qword posB = pos;
        __asm__("" : "+m"(posB) : "r"(pos));
        float h = pent->sHeight + rScale * 300.0f;
        // tie: the height reads the posB copy, so its store schedules before the D_00317550 load
        __asm__("" : "=f"(h) : "0"(h), "m"(posB));
        qword posEnd = QwAddScaled(pos, D_00317550, VuFloat(h));
        if (pwaypt->psoMarker)
        {
            MATRIX3 matScaled = *MatOf(pwaypt->psoMarker) * VuFloatFromMemWord(*(int *)&rScale);
            MATRIX4 *pmat = &mat;
            func_002BA818(&mat.pos, posEnd);
            *(MATRIX3 *)pmat = matScaled;
            mat.mat[2].w = 0.0f;
            mat.mat[1].w = 0.0f;
            mat.mat[0].w = 0.0f;
            pmat->pos.w = 1.0f;
            func_001C8248(pwaypt->psoMarker, q, pmat, uShow, uShow);
        }
        if (pwaypt->psoBeam)
            func_001C8328(pwaypt->psoBeam, rScale, q, uShow, posB, posEnd);
        if (pwaypt->psoBase)
        {
            MATRIX3 matScaled = *MatOf(pwaypt->psoBase) * VuFloatFromMemWord(*(int *)&rScale);
            MATRIX4 *pmat = &mat;
            func_002BA818(&mat.pos, pos);
            *(MATRIX3 *)pmat = matScaled;
            mat.mat[2].w = 0.0f;
            mat.mat[1].w = 0.0f;
            mat.mat[0].w = 0.0f;
            pmat->pos.w = 1.0f;
            func_001C8248(pwaypt->psoBase, q, pmat, uShow, uShow);
        }
        if (0.0f < uLabel && pwaypt->pattach && pwaypt->pattach->ptask && pwaypt->pattach->ptask->idLabelName != -1)
        {
            float dz = pwaypt->psoMarker ? rScale * pwaypt->psoMarker->sRadius : 0.0f;
            qword posLabel = QwAddScaledG(posEnd, D_00317550, VuFloat(dz));
            RGBA rgbaBack(0x80603030);
            RGBA rgbaText(0xFFC0C0C0);
            rgbaBack.a = (uchar)(int)(uLabel * rgbaBack.a);
            rgbaText.a = (uchar)(int)(uLabel * rgbaText.a);
            DrawLabel(plo, posLabel, rgbaBack, rgbaText, pwaypt->pattach->ptask->idLabelName, rScale);
        }
    }
}
