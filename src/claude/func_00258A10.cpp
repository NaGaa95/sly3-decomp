// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00258A10: gait post-load (cf. Sly 2 PostJtLoadGait, src/P2/jt.c), Sly 3 layout.
typedef unsigned int uint;
typedef int qword __attribute__((mode(TI)));

struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));

struct XF;
struct KEY
{
    virtual void Load(void *pbis);
};
struct VECKEY : public KEY
{
    virtual void CacheSeg(XF *pxf);
    virtual void GetValue(float t, float svt, qword *ppos, qword *pv);
};
struct BLEND
{
    void *vtbl;
    void *pasegbl;
    void *amrsgc;
};
struct CHN
{
    int oid : 20;
    int ixf : 10;
    uint fStripped : 1;
    uint fScalar : 1;
    KEY *pkey;
};
struct MRSGC { int ib; int cmrsg; void *amrsg; };
struct ASEG
{
    char pad0[0x4C];
    int cchn;
    CHN *achn;
    char pad54[0x10];
    float tMax;
};
struct ASEGBL
{
    char pad0[0x4C];
    int cchn;
    CHN *achn;
    char pad54[0x50];
    int fUnkA4;
    char padA8[0x18];
    MRSGC *amrsgc;
};
struct XFX { char pad[0x9C]; int oid; };
struct BLGAIT
{
    float gWeight;
    ASEG *paseg;
    char ab08[8];
    qword vRoot;
    char ab20[0x20];
};
struct GAIT
{
    void *pstepplayer;
    ASEGBL *pasegbl;
    char ab08[8];
    BLGAIT abl[2];
    char ab90[0x14];
    int fLoaded;
};
struct VU_FLOAT { qword qw; };
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwDivVu(qword qw, VU_FLOAT g)
{
    qword qwRet;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qwRet) : "j"(g.qw), "j"(qw));
    return qwRet;
}
extern int D_00349928[2];
extern int D_00349930[2];
void FillBlAmrsg(int cbBl, int cbl, void *abl, int ibMrsg, int coid, int *aoid) __asm__("func_00148468");
CHN *PchnFindAseg(ASEG *paseg, void *palo, int xfk, int fStripped) __asm__("func_00136EE0");
void FindAsegChannelTarget(ASEGBL *paseg, void *paloRoot, CHN *pchn, void **ppso, XFX **ppxf) __asm__("func_00136E28");
void ReblendAsegbl(ASEGBL *pasegbl) __asm__("func_00148938");
void func_00147FD0(ASEGBL *pasegbl, void *p) __asm__("func_00147FD0");

void PostLoadGait(GAIT *pgait, void *p) __asm__("func_00258A10");
void PostLoadGait(GAIT *pgait, void *p)
{
    if (pgait->fLoaded != 0)
        return;
    pgait->fLoaded = 1;
    FillBlAmrsg(0x40, 2, pgait->abl, 0x20, 2, D_00349928);
    FillBlAmrsg(0x40, 2, pgait->abl, 0x30, 2, D_00349930);
    if (pgait->pasegbl->fUnkA4)
        func_00147FD0(pgait->pasegbl, p);
    for (uint ibl = 0; ibl < 2; ibl++)
    {
        BLGAIT *pblgait = &pgait->abl[ibl];
        ASEG *paseg = pblgait->paseg;
        if (paseg != 0)
        {
            CHN *pchn = PchnFindAseg(paseg, pgait->pstepplayer, 1, 1);
            VECTOR4 vStart, vEnd;
            ((VECKEY *)pchn->pkey)->GetValue(0.0f, 1.0f, (qword *)&vStart, 0);
            ((VECKEY *)pchn->pkey)->GetValue(paseg->tMax, 1.0f, (qword *)&vEnd, 0);
            qword qwDiff = QwSub(*(qword *)&vEnd, *(qword *)&vStart);
            VU_FLOAT vuT;
            __asm__("qmtc2 %1, %0" : "=j"(vuT.qw) : "rV"(*(int *)&paseg->tMax));
            pblgait->vRoot = QwDivVu(qwDiff, vuT);
        }
    }
    for (int ichn = 0; ichn < pgait->pasegbl->cchn; ichn++)
    {
        CHN *pchn = &pgait->pasegbl->achn[ichn];
        BLEND *pvkblend;
        BLEND *pskblend;
        if (pchn->fScalar)
        {
            pvkblend = 0;
            pskblend = (BLEND *)pchn->pkey;
        }
        else
        {
            pvkblend = (BLEND *)pchn->pkey;
            pskblend = 0;
        }
        void *pso;
        XFX *pxf;
        FindAsegChannelTarget(pgait->pasegbl, pgait->pstepplayer, pchn, &pso, &pxf);
        if (pxf != 0)
        {
            switch (pxf->oid)
            {
            case 0x28:
            case 0x2A:
            case 0x2C:
                if (pvkblend != 0)
                    pvkblend->amrsgc = &pgait->pasegbl->amrsgc[1];
                if (pskblend != 0)
                    pskblend->amrsgc = &pgait->pasegbl->amrsgc[1];
                continue;
            case 0x29:
            case 0x2B:
            case 0x2D:
                continue;
            }
        }
        if (pvkblend != 0)
            pvkblend->amrsgc = 0;
        if (pskblend != 0)
            pskblend->amrsgc = 0;
    }
    ReblendAsegbl(pgait->pasegbl);
}
// The unit's next rodata literals (after the jump table).
extern const float D_003274C8 = -3.40282346639e+38f;
extern const float D_003274CC = 3.40282346639e+38f;
