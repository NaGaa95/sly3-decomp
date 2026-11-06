// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Hand curve setup: builds the frame chain of the hand object, then for each hand with a clip two sampled curves (hand frame and chain frame)
// through the clip, and finally the two-hand blend.
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct MATRIX4 { qword r[4]; } __attribute__((aligned(16)));
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x48]; VTE remove; char pad2[0x128 - 0x50]; VTE xfLocal; };
struct XF { MATRIX4 mat; char pad[0x94 - 0x40]; int xfk; char pad2[0xA0 - 0x98]; XF *pxfParent; };
struct SO { char pad0[0x50]; XF *pxfRoot; };
struct ASEG { char pad0[0x64]; float tMax; };
struct SHAPE {
    char pad0[0xC]; VT *pvt;
    char pad10[0xD0 - 0x10];
    int crvk; char padD4[4]; int ccv; float *mpicvu; float *mpicvs; qword *mpicvpos;
};
struct LO { char pad0[0xC]; VT *pvt; };
struct HAND { float uWeight; ASEG *paseg; int unk8; SHAPE *pshapeA; SHAPE *pshapeB; };
struct JTHANDS {
    SO *pso;
    void **ppasega;
    HAND abl[2];
    void *pasegbl;
    LO *ploHand;
    XF *pxf;
    int unk3c;
    MATRIX4 matChain;
    char pad80[0xAC - 0x80];
    void *unkAC;
};
struct SWALLOC { int cb; int cbAlign; };
extern "C" {
SHAPE *func_00150690(int cid, SO *pso, int oid, int isplice);
void *func_001D2470(SWALLOC *p);
void func_00137070(float t, float svt, ASEG *paseg, SO *pso, XF *pxfEffect, XF *pxfRef, MATRIX4 *pmatOut, int f);
void *func_00292034(void *p, int v, int n);
void func_0022DB08(SHAPE *pshape);
void func_00147E08(SO *palo, int cbBl, int cbl, void *abl, int cmrsgc, int *a, int *b, void **ppasegbl);
MATRIX4 func_0011D558(const MATRIX4 &a, const MATRIX4 &b);
}
inline void SetIdentity(MATRIX4 *pmat)
{
    func_00292034(pmat, 0, sizeof(MATRIX4));
    ((float *)pmat)[15] = 1.0f;
    ((float *)pmat)[10] = 1.0f;
    ((float *)pmat)[5] = 1.0f;
    ((float *)pmat)[0] = 1.0f;
}
inline void *PvAllocSw(int cb, int cbAlign)
{
    SWALLOC swalloc;
    swalloc.cb = cb;
    SWALLOC *pswalloc = &swalloc;
    pswalloc->cbAlign = cbAlign;
    return func_001D2470(pswalloc);
}
inline qword Transform(const MATRIX4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
extern "C" void func_002086B0(JTHANDS *phands, SO *pso, void **ppasega)
{
    phands->pso = pso;
    phands->ppasega = ppasega ? ppasega : &phands->unkAC;
    if (!phands->ploHand)
        return;
    MATRIX4 matHand;
    XF *pxfHand = ((XF *(*)(void *, MATRIX4 *))phands->ploHand->pvt->xfLocal.pfn)((char *)phands->ploHand + phands->ploHand->pvt->xfLocal.d, &matHand);
    phands->matChain = matHand;
    phands->pxf = pxfHand;
    while (phands->pxf->xfk != 6) {
        phands->matChain = func_0011D558(phands->pxf->mat, phands->matChain);
        phands->pxf = phands->pxf->pxfParent;
    }
    int cHands = 0;
    for (int i = 0; i < 2; i++) {
        ASEG *paseg = phands->abl[i].paseg;
        if (!paseg)
            continue;
        cHands++;
        for (int j = 0; j < 2; j++) {
            SHAPE *pshape = func_00150690(9, phands->pso, 0xE2, -1);
            pshape->crvk = 0;
            pshape->ccv = 9;
            pshape->mpicvu = (float *)PvAllocSw(9 << 2, 16);
            pshape->mpicvs = (float *)PvAllocSw(9 << 2, 16);
            pshape->mpicvpos = (qword *)PvAllocSw(9 << 4, 16);
            MATRIX4 matSample;
            XF *pxfEffect;
            if (j == 0) {
                matSample = matHand;
                pxfEffect = pxfHand;
            } else {
                pxfEffect = phands->pxf;
                SetIdentity(&matSample);
            }
            for (int k = 0; k < 9; k++) {
                MATRIX4 matOut;
                float u = (float)k / (float)(9 - 1);
                func_00137070(u * paseg->tMax, 0.0f, paseg, phands->pso, pxfEffect, phands->pso->pxfRoot, &matOut, 0);
                pshape->mpicvu[k] = u;
                pshape->mpicvpos[k] = Transform(matOut, matSample.r[3]);
            }
            ((void (*)(void *))pshape->pvt->remove.pfn)((char *)pshape + pshape->pvt->remove.d);
            func_0022DB08(pshape);
            if (j == 0)
                phands->abl[i].pshapeA = pshape;
            else
                phands->abl[i].pshapeB = pshape;
        }
    }
    if (cHands == 2) {
        phands->abl[0].uWeight = 1.0f;
        func_00147E08(phands->pso, 0x14, 2, phands->abl, 0, 0, 0, &phands->pasegbl);
    }
}
