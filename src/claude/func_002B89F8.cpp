// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002B89F8: the unlimited twin of func_002B8E08 (ClsgClipEdgeToBsp): no pbspLimit test (the 2nd arg is ignored; the
// caller func_00119BE8 passes 0). Port of the Sly 2 match func_00118668
// (decomp src/hand/func_00118668.cpp, see its notes for the algorithm); Sly 3 changes: -Os, ceb.pbsp is set between the two
// memsets and pceb = aceb right before the second one; VU_QWORD() is the out-of-line func_002BA000.
typedef unsigned  size_t;
typedef unsigned short   uint16_t;
typedef unsigned int     uint32_t;
typedef uint16_t    ushort;
typedef uint32_t    uint;
typedef unsigned long long qword __attribute__((mode(TI)));
struct VECTOR
{
    float x, y, z;
};
extern "C" {
void* memset(void* ptr, int value, size_t num);
}
struct EDGE
{
    ushort aipos[2];
    ushort aisurf[2];
    EDGE *pedgeNext;
    EDGE *pedgeOtherNext;
};
struct SURF
{
    VECTOR normal;
    float gDot;
    EDGE *pedge;
    EDGE *pedgeOther;
    uint grf;
    int ipos;
};
enum LSGK
{
};
struct BSP
{
    BSP *pbspNeg;
    BSP *pbspPos;
    SURF *psurf;
};
struct VU_QWORD
{
    qword qw;
    VU_QWORD() __asm__("func_002BA000");
};
struct LSG
{
      qword apos[2];
      qword anormal[2];
      float au[2];
      LSGK lsgk;
      SURF *apsurf[2];
      EDGE *pedge;
      int iiposSwap;
      LSG *plsgNext;
};
struct CEB
{
      BSP *pbsp;
      BSP *pbspNeg;
      float g;
      SURF *psurf;
      qword normal;
};
struct VU_FLOAT
{
    qword qw;
};
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline qword QwMix(VU_FLOAT g1, qword qw1, VU_FLOAT g2, qword qw2)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %4x" : "=j"(qw) : "j"(qw1), "j"(qw2), "j"(g1.qw), "j"(g2.qw));
    return qw;
}
int ClsgClipEdgeToBsp(BSP *pbspRoot, BSP *pbspLimit, qword pos1, qword pos2, int clsgMax, LSG *alsg) __asm__("func_002B89F8");
int ClsgClipEdgeToBsp(BSP *pbspRoot, BSP *pbspLimit, qword pos1, qword pos2, int clsgMax, LSG *alsg)
{
    CEB ceb;
    CEB aceb[32];
    CEB *pceb;
    LSG *plsgLast;
    LSG *plsgOut;
    plsgLast = 0;
    plsgOut = alsg;
    memset(&ceb, 0, sizeof(CEB));
    ceb.pbsp = pbspRoot;
    pceb = aceb;
    memset(pceb, 0, sizeof(CEB));
    pceb->g = 1.0f;
    while (1)
    {
        while (ceb.pbsp == 0)
        {
            if (ceb.pbspNeg != 0)
            {
                if (plsgLast != 0 && ceb.g == plsgLast->au[1])
                {
                    plsgLast->apos[1] = QwMix(VuFloat(1.0f - pceb->g), pos1, VuFloat(pceb->g), pos2);
                    plsgLast->anormal[1] = pceb->normal;
                    plsgLast->au[1] = pceb->g;
                    plsgLast->apsurf[1] = pceb->psurf;
                }
                else
                {
                    if (plsgOut - alsg >= clsgMax)
                    {
                        return clsgMax;
                    }
                    plsgLast = plsgOut;
                    plsgOut++;
                    memset(plsgLast, 0, sizeof(LSG));
                    plsgLast->apos[0] = QwMix(VuFloat(1.0f - ceb.g), pos1, VuFloat(ceb.g), pos2);
                    plsgLast->apos[1] = QwMix(VuFloat(1.0f - pceb->g), pos1, VuFloat(pceb->g), pos2);
                    plsgLast->anormal[0] = ceb.normal;
                    plsgLast->anormal[1] = pceb->normal;
                    plsgLast->au[0] = ceb.g;
                    plsgLast->au[1] = pceb->g;
                    plsgLast->apsurf[0] = ceb.psurf;
                    plsgLast->apsurf[1] = pceb->psurf;
                }
            }
            if (pceb <= aceb)
            {
                return plsgOut - alsg;
            }
            ceb = *pceb;
            pceb--;
        }
        qword plane = *(qword *)ceb.pbsp->psurf;
        VU_QWORD dot1;
        VU_QWORD vfOne1;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w"
                : "=j"(dot1), "=j"(vfOne1) : "j"(plane), "j"(pos1));
        float g1 = GFromVf(dot1.qw);
        VU_QWORD dot2;
        VU_QWORD vfOne2;
        float g2;
        int iScratch;
        __asm__("vmul.xyz %1, %4, %5\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %4w\n\tqmfc2 %3, %1\n\tmtc1 %3, %2"
                : "=j"(vfOne2), "=j"(dot2), "=f"(g2), "=&r"(iScratch) : "j"(plane), "j"(pos2));
        if (g1 <= 0.0f && g2 <= 0.0f)
        {
            ceb.pbspNeg = ceb.pbsp;
            ceb.pbsp = ceb.pbsp->pbspNeg;
        }
        else if (g1 > 0.0f && g2 > 0.0f)
        {
            ceb.pbspNeg = 0;
            ceb.pbsp = ceb.pbsp->pbspPos;
        }
        else
        {
            float t = g1 / (g1 - g2);
            float gMid = g2 * ceb.g + (1.0f - ceb.g) * g1;
            float gTop = g2 * pceb->g + (1.0f - pceb->g) * g1;
            if (ceb.g < t && t < pceb->g)
            {
                pceb++;
                pceb->g = t;
                pceb->normal = plane;
                pceb->psurf = ceb.pbsp->psurf;
                if (gMid <= 0.0f)
                {
                    pceb->pbspNeg = 0;
                    pceb->pbsp = ceb.pbsp->pbspPos;
                }
                else
                {
                    pceb->pbspNeg = ceb.pbsp;
                    pceb->pbsp = ceb.pbsp->pbspNeg;
                }
            }
            if (gMid < 0.0f || (gMid == 0.0f && gTop <= 0.0f))
            {
                ceb.pbspNeg = ceb.pbsp;
                ceb.pbsp = ceb.pbsp->pbspNeg;
            }
            else
            {
                ceb.pbspNeg = 0;
                ceb.pbsp = ceb.pbsp->pbspPos;
            }
        }
    }
}
