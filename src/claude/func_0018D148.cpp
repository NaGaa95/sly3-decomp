// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 LoadGlobsetFromBrx, adapted from the Sly 2 decomp (func_00167320): two load filters, a slot remap table
// (aiMap, PvAllocSlot) for compact globsets, bounds-record reading inline, CTX scope object. C++ so the ALLOCREQ
// temporaries of the inline allocators share one stack slot (address kept in $s0).
typedef unsigned int uint;
typedef unsigned long ulong;
struct STREAM;
struct VECTOR;
struct REQUEST { int bytes, alignment; };
struct CTX { int a[4]; CTX(); ~CTX(); };
struct BND { int oid; int pad4; int ixf; char pad[0x50 - 0xC]; };
struct SUBGLOB { signed char bUnk00; signed char cbnd; char pad2; signed char type; float gUnk04; int pad8[3]; };
struct GLOB {
    int oid; void *pxf; int pad8;
    uint grfglobType : 3; uint iUnk0c3 : 5; uint unk : 3; uint fLimit : 1; uint fHide : 1; uint rest : 19;
    int pad10[2]; struct BND *abnd; int pad1C[3];
};
struct SUBGLOBX { float pos[3]; float sRadius; float gUnk10; uint grfUnk14; };
struct VTE { short d; short pad; void *(*pfn)(void *, int); };
struct SO { char pad[0xC]; struct VTE *pvt; };
struct GLOBSET {
    struct SO *pso; int pad4[3]; float posCenter[4]; float sRadius; int cpsaa; void **apsaa; int cnUnk2c; int *anUnk30;
    int nUnk34; int cglob; struct SUBGLOB *asubglob; struct GLOB *aglob; struct SUBGLOBX *asubglobx; int pad48[2];
    ulong unk50 : 32; ulong f32 : 1; ulong f33 : 1; ulong rest50 : 30;
};
extern "C" char D_0036B118[];
signed char func_00119128(struct STREAM *pbis) __asm__("S8Read__18CBinaryInputStream");
unsigned char func_00118FF8(struct STREAM *pbis) __asm__("U8Read__18CBinaryInputStream");
short func_00119178(struct STREAM *pbis) __asm__("S16Read__18CBinaryInputStream");
unsigned short U16Read(struct STREAM *pbis) __asm__("U16Read__18CBinaryInputStream");
int S32Read(struct STREAM *pbis) __asm__("S32Read__18CBinaryInputStream");
uint func_001190A8(struct STREAM *pbis) __asm__("U32Read__18CBinaryInputStream");
float func_00119260(struct STREAM *pbis) __asm__("F32Read__18CBinaryInputStream");
void func_001192D8(struct STREAM *pbis, void *pvec) __asm__("ReadVector__18CBinaryInputStreamP6VECTOR");
void func_00118DA0(struct STREAM *pbis, int cb, void *pv) __asm__("Read__18CBinaryInputStreamiPv");
void func_00118DF0(struct STREAM *pbis, int cb) __asm__("Skip__18CBinaryInputStreami");
extern "C" void *func_001D2538(struct REQUEST *preq);
extern "C++" void *PvAllocSlot(struct REQUEST *preq) __asm__("PvAllocSlot__FP8ALLOCREQ");
extern "C" void *memset(void *, int, unsigned int);
extern "C" void *func_00236EB0(int n, struct STREAM *pbis);
extern "C" int func_00151C98(int c, short *a);
extern "C" int func_00151D10(int c, int *a);
extern "C" void func_0018FD10(struct GLOBSET *pglobset, struct SUBGLOB *psubglob, struct GLOB *pglob, struct SUBGLOBX *psubglobx, int cSubExtra, struct STREAM *pbis, void *pheap);
extern "C" void func_0018D738(struct GLOBSET *pglobset, struct STREAM *pbis, int *aiMap);
static inline void *PvAllocSwClear(int cb) { REQUEST req; req.bytes = cb; req.alignment = 0x10; return func_001D2538(&req); }
static inline void *PvAllocSlotCb(int cb) { REQUEST req; req.bytes = cb; req.alignment = 0x10; return PvAllocSlot(&req); }
extern "C" void func_0018D148(struct GLOBSET *pglobset, struct SO *pso, struct STREAM *pbis)
{
    struct CTX ctx;
    int fCompact;
    int *aiMap;
    int i;
    int j;
    pglobset->pso = pso;
    fCompact = func_00119128(pbis);
    func_001192D8(pbis, pglobset->posCenter);
    pglobset->sRadius = func_00119260(pbis);
    pglobset->cpsaa = func_00119128(pbis);
    pglobset->apsaa = (void **)PvAllocSwClear(pglobset->cpsaa * 4);
    for (int k = 0; k < pglobset->cpsaa; k++)
        pglobset->apsaa[k] = func_00236EB0(1, pbis);
    pglobset->cnUnk2c = func_00118FF8(pbis);
    pglobset->anUnk30 = (int *)PvAllocSwClear(pglobset->cnUnk2c * 4);
    pglobset->nUnk34 = 0;
    for (int k = 0; k < pglobset->cnUnk2c; k++)
        pglobset->anUnk30[k] = S32Read(pbis);
    pglobset->cglob = func_00119178(pbis);
    pglobset->asubglob = (SUBGLOB *)PvAllocSwClear(pglobset->cglob * sizeof(struct SUBGLOB));
    pglobset->aglob = (GLOB *)PvAllocSwClear(pglobset->cglob * sizeof(struct GLOB));
    if (fCompact) {
        aiMap = (int *)PvAllocSlotCb(pglobset->cglob * 4);
        memset(aiMap, -1, pglobset->cglob * 4);
    } else {
        aiMap = 0;
    }
    if (!fCompact) {
        pglobset->asubglobx = (SUBGLOBX *)PvAllocSwClear(pglobset->cglob * sizeof(struct SUBGLOBX));
    }
    for (i = 0, j = 0; i < pglobset->cglob; i++, j++) {
        struct SUBGLOB *psubglob = &pglobset->asubglob[i];
        struct GLOB *pglob = &pglobset->aglob[i];
        struct SUBGLOBX *psubglobx = pglobset->asubglobx ? &pglobset->asubglobx[i] : 0;
        int cA = func_00118FF8(pbis);
        int cB = func_00118FF8(pbis);
        int cSubExtra;
        float g;
        int k;
        if (cA || cB) {
            short afilter[128];
            int aid[128];
            int cbSkip;
            func_00118DA0(pbis, cA * 2, afilter);
            func_00118DA0(pbis, cB * 4, aid);
            cbSkip = S32Read(pbis);
            if (!func_00151C98(cA, afilter) || !func_00151D10(cB, aid)) {
                func_00118DF0(pbis, cbSkip);
                i--;
                pglobset->cglob--;
                continue;
            }
        }
        psubglob->type = func_00119128(pbis);
        cSubExtra = U16Read(pbis);
        {
            VTE *e = &pso->pvt[55];
            pglob->pxf = e->pfn((char *)pso + e->d, func_00119178(pbis));
        }
        psubglob->bUnk00 = func_00119128(pbis);
        g = func_00119260(pbis);
        psubglob->gUnk04 = g;
        if (g != 3.4028235e+38f) {
            psubglob->gUnk04 = g * __builtin_fabsf(g);
            pglob->fLimit = 1;
        }
        pglob->oid = S32Read(pbis);
        pglob->fHide = func_00119128(pbis) & 1;
        if (!fCompact) {
            func_001192D8(pbis, psubglobx->pos);
            psubglobx->sRadius = func_00119260(pbis);
            psubglobx->grfUnk14 = func_001190A8(pbis);
            psubglobx->gUnk10 = func_00119260(pbis);
        }
        pglob->grfglobType = psubglob->type;
        pglob->iUnk0c3 = psubglob->bUnk00;
        psubglob->cbnd = func_00118FF8(pbis);
        pglob->abnd = (BND *)PvAllocSwClear(psubglob->cbnd * sizeof(struct BND));
        for (k = 0; k < psubglob->cbnd; k++) {
            struct BND *pbnd = &pglob->abnd[k];
            pbnd->oid = S32Read(pbis);
            pbnd->ixf = func_00119178(pbis);
        }
        if (psubglob->type == 2)
            pglobset->f33 = 1;
        if (func_00119128(pbis))
            pglob->fHide = 1;
        else
            func_0018FD10(pglobset, psubglob, pglob, psubglobx, cSubExtra, pbis, D_0036B118);
        if (aiMap) {
            for (int m = 0; m <= cSubExtra; m++)
                aiMap[j + m] = i + m;
        }
        i += cSubExtra;
        j += cSubExtra;
    }
    func_0018D738(pglobset, pbis, aiMap);
}
