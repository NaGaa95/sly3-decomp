// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0018FF98: load a type-0 subglob (lit/baked mesh batches) from a BRX stream into VIF packets.
// Ported from the Sly 2 decomp (func_0016A000 = LoadSubglobType0FromBrx) with Sly 3 layouts and callees.
typedef unsigned int size_t;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long qword __attribute__((mode(TI)));
struct SO;
struct SAA;
struct HEAP;
struct WR;
struct RGBA
{
    uchar bRed;
    uchar bGreen;
    uchar bBlue;
    uchar bAlpha;
};
struct VECTOR
{
    float x, y, z;
};
struct VECTOR4
{
    float x, y, z, w;
} __attribute__((aligned(16)));
union QW
{
    VECTOR vec;
    VECTOR4 vec4;
    ulong aul[2];
    uint aun[4];
    float ag[4];
};
union U
{
    qword q;
    float f[4];
};
struct MATRIX4
{
    float mat[4][4];
} __attribute__((aligned(16)));
class DMAS
{
public:
    uchar *m_pbMax;
    uchar *m_ab;
    QW *m_pqwCnt;
    uchar *m_pb;
    int m_fPad;
    int m_fEndPrim;
    void AllocSw(int cqw);
    void DetachCopySw(HEAP *pheap, int *pcqw, QW **paqw, QW **paqwCopy);
    void AddDmaCnt();
    void AddDmaRefs(int cqw, QW *aqw);
    void AddDmaRet();
    void EndDmaCnt();
    virtual void EndPrim(int fEOP);
};
inline void AddDmaInt(DMAS *pdmas, int val)
{
    *(int *)pdmas->m_pb = val;
    pdmas->m_pb += 4;
}
enum UPK
{
    UPK_S16 = 1,
    UPK_S8 = 2,
    UPK_V3_32 = 8,
    UPK_V4_32 = 12,
    UPK_V4_8 = 14,
    UPK_V4_5 = 15,
};
class VIFS : public DMAS
{
public:
    uint m_unMask;
    VIFS();
    void Align(int iun);
    void AddVifMscal(void *pv);
    void AddVifStcycl(int wl, int cl);
    void AddVifStrow(QW *pqw);
    void AddVifStmask(uint unMask);
    void UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun);
    void AddVifUnpack(UPK upk, int c, void *pvSrc, int iqw);
};
struct FRAME
{
    char b;
    FRAME();
    ~FRAME();
};
struct SL
{
    void *head;
    void *tail;
    int ibSle;
};
class CBinaryInputStream
{
public:
    void Read(int cb, void *pv);
    uchar U8Read();
    char S8Read();
    short S16Read();
    int S32Read();
    float F32Read();
    void ReadVector(VECTOR *pvec);
    void ReadMatrix4(MATRIX4 *pmat);
    void ReadCb12(void *pv);
    void ReadCb8(void *pv);
};
struct SHD
{
    int oid;
    uchar shdk;
    uchar grfshd;
    uchar unk_6;
    uchar unk_7;
    RGBA rgba;
    RGBA rgbaVolume;
    RGBA rgba2;
    ushort OidAltSat;
    uchar rp;
    uchar ctex;
    void *atex;
    int cshdp;
    void *ashdp;
    int cframe;
    SAA *psaa;
};
struct WRBG;
struct XF
{
    MATRIX4 mat;
    MATRIX4 matWorld;
};
struct GLOB
{
    ushort oid;
    XF *pxf;
    MATRIX4 *pmatUnk08;
    union
    {
        uint grf;
        struct
        {
            uint grfLow : 14;
            uint iUnkFirst : 10;
            uint cUnk : 8;
        };
    };
    void *pvUnk10;
    void *pvUnk14;
    void *abnd;
    WRBG *pwrbg;
    SAA *psaa;
};
struct SUBGLOB
{
    char bUnk00;
    char cbnd;
    int bUnk02 : 8;
    char type;
    float gUnk04;
    void *pvLit;
    int iqwBone;
    int cqw;
};
struct SUBGLOBX;
struct BATCH
{
    int cvtx;
    SHD *pshd;
    int grf;
    SAA *psaa;
    int ivtxOwn;
    int *aivtx;
    void *pvPos;
    void *pvPosDelta;
    void *pvUv;
    void *pvUvLink;
    int obColorA;
    int obColorB;
    uchar *pbAlpha;
    int obAlpha;
    uchar *pbRgb;
    uchar *pbNorm;
    uchar *pbWeights;
};
struct SPECPARAMS
{
    float agUnk00[3];
    float gPad0c;
    float agUnk10[2];
    int iSpec;
    int fMode;
    VECTOR vec;
    float gPad2c;
} __attribute__((aligned(16)));
struct BATCHFILE
{
    int cvtx;
    int ishd;
    uint grf;
};
struct BATCHPART0
{
    ushort iqwVtx;
    ushort iqwEnd;
    ushort iqwUv;
    ushort cvtxFlag;
    ushort aiqwShdp[4];
    ushort iqwOwn;
    ushort iqwSkin;
    ushort iqwSaa;
    ushort iqwSpec;
    ushort oidAltSat;
    ushort iqwUvLink;
    ushort iqwWeights;
    ushort cframe;
};
struct BATCHHDR0
{
    ushort unk_0x00;
    ushort oid;
    ushort unk_0x04;
    ushort iqwShadow;
    ushort grf;
    ushort iqwBase;
    ushort grfWarp;
    ushort iqwWarp;
    ushort aiqwBone[4];
    BATCHPART0 apart[2];
};
struct VERTREC
{
    int ivtxFile;
    BATCH *pbatchFirst;
    int ivtxFirst;
    BATCH *pbatch;
    int ivtx;
};
struct WRBGBATCH
{
    int cvtx;
    void *pvPos;
    void *apvWarp[4];
    WRBGBATCH *pwrbgbatchNext;
};
struct BATCHREC
{
    int cvtx;
    uint grf;
    void *pvUv;
    void *pvPos;
    void *pvUvLink;
    void *pbRgb;
    void *pbNorm;
    int unk_0x1c;
};
struct BATCHRECS
{
    SUBGLOB *psubglob;
    int cbatch;
    BATCHREC *abatchrec;
    BATCHRECS *pbatchrecsNext;
};
struct CLUTCOLOR
{
    ushort ucA;
    ushort ucB;
    uchar bAlpha;
};
struct CLUTPAL
{
    int ibatch;
    int ccolor;
    CLUTCOLOR *acolor;
};
struct CLUTSET
{
    int cpal;
    CLUTPAL *apal;
};
struct SUBGLOBLOAD
{
    float gUnk00;
    int nUnk04;
    int nUnk08;
};
struct GLOBSET
{
    SO *pso;
    float tUnk04;
    uint unk_0x08[2];
    VECTOR posCenter;
    uint unk_0x1c;
    float sRadius;
    int cpsaa;
    SAA **apsaa;
    int cnUnk2c;
    int *anUnk30;
    int nUnk34;
    int cglob;
    SUBGLOB *asubglob;
    GLOB *aglob;
    SUBGLOBX *asubglobx;
    void *aposeset;
    int nUnk4c;
    union
    {
        float gUnk50;
        struct
        {
            ulong unk_0x50 : 32;
            ulong fBoundsUnk32 : 1;
            ulong fBoundsUnk33 : 1;
            ulong fUnk34 : 1;
            ulong unk_0x54 : 29;
        };
    };
    WRBG *pwrbgFirst;
    void *pbatchrecsFirst;
};
struct WEKI
{
    int wek;
    float sInner;
    float uInner;
    float sOuter;
    float uOuter;
    uchar unknown[12];
    MATRIX4 dmat;
};
struct WRBG
{
    SO *pso;
    GLOB *pglob;
    int oid;
    WR *pwr;
    int cmat;
    int fDpos;
    int fDuv;
    int unk_0x1c;
    ushort grf;
    int iqw;
    uchar unknown[8];
    WEKI weki;
    SL slBatch;
    int unk_0x9c;
    WRBG *pwrbgNextGlobset;
    WRBG *pwrbgNextWr;
};
// Local transform used by the compressed-position path (see func_00195028 / func_001951A0).
struct XFORMQ
{
    MATRIX4 matLocal;
    MATRIX4 matWorld;
    VECTOR4 pos;
    QW qwLast;
};
struct SAAVIRT
{
    int unk_0x0[3];
    virtual void V0();
    virtual void V1();
    virtual void V2();
    virtual void V3();
    virtual void V4();
    virtual void V5();
    virtual void V6();
    virtual void V7();
    virtual void V8();
    virtual bool V9(SHD *pshd);
};
struct SAAFIELDS : public SAAVIRT
{
    int unk_0x10[4];
    uint grf;
    int unk_0x24[9];
    int cqwMain;
    void *pvMain;
};
struct SWALLOC
{
    int cb;
    int cbAlign;
    SWALLOC(int cbArg, int cbAlignArg)
    {
        cb = cbArg;
        cbAlign = cbAlignArg;
    }
};
struct UVF
{
    float u, v;
};
struct RGBA5551 { ushort r : 5; ushort g : 5; ushort b : 5; ushort a : 1; };
struct UVLINK { short u, v; ushort link; } __attribute__((packed));
void *PvAllocCopy(HEAP *pheap, int cb, void *pv, int nKind);
void *PvAllocClear(HEAP *pheap, int cb, int cbAlign);
extern "C" {
void *memset(void *ptr, int value, size_t num);
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) __asm__("func_00292540");
void CopyAb(void *pvDst, void *pvSrc, uint cb);
void *func_001D25B0(SWALLOC *pswalloc);
void *func_001D2670(SWALLOC *pswalloc);
void *func_001D2538(SWALLOC *pswalloc);
void *func_001D2470(SWALLOC *pswalloc);
int func_0013B500(SO *pso, int cid);
void func_001692E8(void *pcm, float *pg, float gScale);
CLUTSET *func_001929B0(GLOBSET *pglobset, CBinaryInputStream *pbis);
void func_0011AD60(SL *psl, int ibSle);
void func_0011AD80(SL *psl, void *pv);
void func_00195028(XFORMQ *pxq, CBinaryInputStream *pbis);
void func_00195168(XFORMQ *pxq, VIFS *pvifs, float g);
void func_001951A0(XFORMQ *pxq, short *ps, VECTOR *ppos, float gW);
float func_002BE308(const U *pu);
float func_002BE310(const U *pu);
float func_002BE318(const U *pu);
SHD *func_00235F68(int ishd);
SHD *func_00235E60(int oid);
int func_00235CC0(SHD *pshd, int ishdp, int iqw, VIFS *pvifs);
int func_00235D08(SHD *pshd, int ishdp, int iqw, VIFS *pvifs);
int func_00237060(SAA *psaa, int iqw, VIFS *pvifs, GLOB *pglob);
void func_00235D78(int iFirst, int c, int cb, void *pvOld, void *pvNew);
void func_00236908(RGBA *prgba);
int func_0018F650(const void *pv1, const void *pv2);
void func_0018FBB0(SUBGLOB *psubglob, GLOB *pglob, uint cqw, void *pvBase, int cqwMain, char *pbNew, char *pbOld);
void func_0018F6B8(GLOBSET *pglobset, SUBGLOB *psubglob, GLOB *pglob, SUBGLOBX *psubglobx, int cSubExtra, int cbatch, int *acbatch, BATCH **apbatch, CBinaryInputStream *pbis);
void func_0027E388(VIFS *pvifs, uint unMode);
void func_0018FF98(GLOBSET *pglobset, SUBGLOB *psubglob, GLOB *pglob, SUBGLOBLOAD *psgl, SUBGLOBX *psubglobx, int cSubExtra, CBinaryInputStream *pbis, HEAP *pheap);
extern char D_00000000[];
extern char D_00003638[];
extern char D_00003648[];
extern char D_000036D0[];
extern char D_00003758[];
extern char D_000037A0[];
extern char D_000037C8[];
extern char D_00003BE8[];
extern char D_00003EB8[];
extern char D_00003F00[];
extern char D_00003F48[];
extern char D_00003F80[];
extern char D_0036BC10[];
extern QW D_0036DBC0;
extern int D_0036DBB0;
extern uint D_00345000[];
extern int D_00345018[];
extern int D_00345040;
extern float D_00321CC8;
extern int D_0046FF40;
}
static inline void *PvAllocStackP(int cb)
{
    SWALLOC swalloc(cb, 0x10);
    return func_001D25B0(&swalloc);
}
static inline void *PvAllocStackClearP(int cb)
{
    SWALLOC swalloc(cb, 0x10);
    return func_001D2670(&swalloc);
}
static inline void *PvAllocSwClearP(int cb)
{
    SWALLOC swalloc(cb, 0x10);
    return func_001D2538(&swalloc);
}
static inline void *PvAllocSwP(int cb)
{
    SWALLOC swalloc(cb, 0x10);
    return func_001D2470(&swalloc);
}
static inline int CwtFromSubglob(SUBGLOB *psubglob)
{
    int cbnd = psubglob->cbnd;
    int cwt = 4;
    if (cbnd < 4)
        cwt = cbnd;
    return cwt;
}
static inline void RelocPpv(char *pbOld, int cb, char *pbNew, char **ppb)
{
    if (ppb != 0 && *ppb >= pbOld && *ppb < pbOld + cb)
        *ppb += pbNew - pbOld;
}
static inline char *PbReloc(char *pbOld, int cb, char *pbNew, char *pb)
{
    char *pbRet;
    if (pb != 0 && pb >= pbOld && pb < pbOld + cb)
        pbRet = pb + (pbNew - pbOld);
    else
        pbRet = pb;
    return pbRet;
}
static inline int Min(int a, int b) { return a < b ? a : b; }
static inline void WriteVertex(U *destination, U value)
{
    float x = func_002BE308(&value);
    float y = func_002BE310(&value);
    float z = func_002BE318(&value);
    destination->f[0] = x; destination->f[1] = y; destination->f[2] = z;
}
static inline void SetPosFixed(int *pn, const VECTOR *pvec)
{
    pn[0] = (int)(pvec->x * 16.0f);
    pn[1] = (int)(pvec->y * 16.0f);
    pn[2] = (int)(pvec->z * 16.0f);
}
void func_0018FF98(GLOBSET *pglobset, SUBGLOB *psubglob, GLOB *pglob, SUBGLOBLOAD *psgl, SUBGLOBX *psubglobx, int cSubExtra, CBinaryInputStream *pbis, HEAP *pheap)
{
    psubglob->bUnk02 = pbis->U8Read();
    if (psubglob->bUnk02 & 1)
        pglob->grf |= 0x100;
    if (psubglob->bUnk02 & 2)
        pglob->grf |= 0x200;
    if (psubglob->bUnk02 & 0x10)
        pglob->grf |= 0x400;
    int isaa = pbis->S8Read();
    if (isaa >= 0)
        pglob->psaa = pglobset->apsaa[isaa];

    FRAME scopeOuter;
    VIFS vifs;
    VIFS vifsAux;
    vifs.AllocSw(0x2000);
    QW *pqwChain = (QW *)vifs.m_pb;
    pglob->iUnkFirst = D_0046FF40;
    if (psubglob->bUnk02 & 3)
    {
        vifs.AddDmaCnt();
        pglobset->fBoundsUnk32 = 1;
    }
    else
    {
        vifsAux.AllocSw(0x800);
        if (func_0013B500(pglobset->pso, 0x30) && !(psubglob->bUnk02 & 0x20) && (uchar)(psubglob->bUnk00 - 6) >= 2 &&
            psubglob->gUnk04 == D_00321CC8)
        {
            QW qwOne;
            qwOne.ag[0] = 1.0f;
            qwOne.ag[1] = 1.0f;
            qwOne.ag[2] = 0.0f;
            qwOne.ag[3] = 0.0f;
            pglob->grf |= 0x2000;
            vifsAux.AddDmaCnt();
            vifsAux.AddVifUnpack(UPK_V4_32, 4, &pglob->pxf->matWorld, 0);
            vifsAux.AddVifUnpack(UPK_V4_32, 1, &qwOne, 8);
            vifsAux.EndDmaCnt();
        }
    }
    float *pgFit;
    if (psubglob->bUnk02 & 8)
        vifs.UnpackHelper(UPK_V4_32, 3, 9, 0, (uint **)&pgFit);
    else
        vifs.UnpackHelper(UPK_V4_32, 1, 9, 0, (uint **)&pgFit);
    func_001692E8(D_0036BC10, pgFit, psgl->gUnk00);

    int iqwBase = (psubglob->bUnk02 & 3) ? 0x23 : 0x17;
    if (psubglob->cbnd != 0)
    {
        psubglob->iqwBone = iqwBase;
        iqwBase += psubglob->cbnd * 4;
    }
    SPECPARAMS spec;
    spec.iSpec = pbis->S8Read();
    if (spec.iSpec != -1)
    {
        pbis->ReadCb12(&spec.agUnk00);
        pbis->ReadCb8(&spec.agUnk10);
        pbis->ReadVector(&spec.vec);
        spec.agUnk00[1] *= 0.007874016f;
        spec.agUnk00[2] *= 6.200012e-05f;
        spec.fMode = (psubglob->bUnk02 & 3) != 0;
    }
    CLUTSET *pclutset = func_001929B0(pglobset, pbis);
    if (psubglob->bUnk02 & 0x20)
    {
        WRBG wrbg;
        memset(&wrbg, 0, sizeof(WRBG));
        wrbg.oid = pbis->S32Read();
        wrbg.weki.wek = pbis->S8Read();
        if (wrbg.weki.wek != -1)
        {
            wrbg.weki.sInner = pbis->F32Read();
            wrbg.weki.uInner = pbis->F32Read();
            wrbg.weki.sOuter = pbis->F32Read();
            wrbg.weki.uOuter = pbis->F32Read();
            pbis->ReadMatrix4(&wrbg.weki.dmat);
        }
        wrbg.cmat = pbis->U8Read();
        int fDpos = pbis->U8Read();
        int fDuv = pbis->U8Read();
        WRBG *pwrbg = (WRBG *)PvAllocCopy(pheap, sizeof(WRBG), &wrbg, 0x2D);
        pwrbg->pso = pglobset->pso;
        pwrbg->pglob = pglob;
        pwrbg->grf = pwrbg->cmat;
        if (fDpos != 0)
            pwrbg->grf = pwrbg->cmat | 0x100;
        if (fDuv != 0)
            pwrbg->grf |= 0x200;
        func_0011AD60(&pwrbg->slBatch, 0x18);
        pwrbg->iqw = iqwBase;
        if (fDpos != 0)
            iqwBase += pwrbg->cmat * 4;
        if (fDuv != 0)
            iqwBase += pwrbg->cmat * 4;
        pglob->pwrbg = pwrbg;
        pwrbg->pwrbgNextGlobset = pglobset->pwrbgFirst;
        pglobset->pwrbgFirst = pwrbg;
    }
    XFORMQ xq;
    if (psubglob->bUnk02 & 8)
    {
        func_00195028(&xq, pbis);
        pgFit[4] = xq.matWorld.mat[0][0];
        pgFit[5] = xq.matWorld.mat[1][1];
        pgFit[6] = xq.matWorld.mat[2][2];
        WriteVertex((U *)&pgFit[8], *(U *)&xq.matWorld.mat[3]);
        func_00195168(&xq, &vifs, *pgFit);
    }
    int cbatch = pbis->S16Read();
    int nLit = 0;
    VIFS vifsLit;
    if (!(psubglob->bUnk02 & 3))
    {
        vifsLit.AllocSw(0x2000);
        vifsLit.AddDmaCnt();
    }
    int *acbatch = (int *)PvAllocStackClearP(cbatch * 4);
    BATCH **apbatch = (BATCH **)PvAllocStackClearP(cbatch * 4);
    void *apvLit[1024];
    for (int ibatch = 0; ibatch < cbatch; ibatch++)
    {
        int cbatchThis = pbis->U8Read();
        BATCH *abatch = (BATCH *)PvAllocStackClearP(cbatchThis * sizeof(BATCH));
        acbatch[ibatch] = cbatchThis;
        apbatch[ibatch] = abatch;
        BATCHHDR0 *phdr;
        vifs.UnpackHelper((UPK)0xd, 0xb, 0xc, 0, (uint **)&phdr);
        memset(phdr, 0, sizeof(BATCHHDR0));
        switch (ibatch)
        {
        case 0:
        {
            phdr->grf = 1;
            if (psubglob->bUnk02 & 8)
                phdr->grf |= 0x2000;
            switch (psgl->nUnk08)
            {
            case 0:
                phdr->grf |= 0x100;
                break;
            case 1:
                phdr->grf |= 0x200;
                break;
            case 2:
                phdr->grf |= 0x400;
                break;
            case 3:
                phdr->grf |= 0x1000;
                break;
            }
            break;
        }
        case 1:
            phdr->grf = 4;
            break;
        }
        phdr->oid = pglob->oid;
        if (psubglob->bUnk02 & 1)
            phdr->grf |= 2;
        if (psubglob->bUnk02 & 2)
            phdr->grf |= 0x800;
        if (psubglob->bUnk02 & 0x80)
            phdr->grf |= 0x80;
        if (pglob->pwrbg != 0)
        {
            phdr->grfWarp = pglob->pwrbg->grf;
            phdr->iqwWarp = pglob->pwrbg->iqw;
        }
        if (psubglob->cbnd != 0)
            phdr->iqwWarp = psubglob->iqwBone;
        int cvtxTotal = 0;
        for (int ib = 0; ib < cbatchThis; ib++)
        {
            BATCH *pbatch = &abatch[ib];
            BATCHFILE bf;
            pbis->Read(sizeof(BATCHFILE), &bf);
            pbatch->cvtx = bf.cvtx;
            pbatch->pshd = func_00235F68(bf.ishd);
            pbatch->grf = bf.grf;
            SAAFIELDS *psaaGlob = (SAAFIELDS *)pglob->psaa;
            if (psaaGlob != 0)
            {
                if (psaaGlob->V9(pbatch->pshd))
                    pbatch->psaa = pglob->psaa;
            }
            if (pbatch->psaa == 0)
            {
                SAAFIELDS *psaaShd = (SAAFIELDS *)pbatch->pshd->psaa;
                if (psaaShd != 0)
                {
                    if (psaaShd->V9(pbatch->pshd))
                        pbatch->psaa = pbatch->pshd->psaa;
                }
            }
            if (pbatch->psaa != 0)
            {
                if (((SAAFIELDS *)pbatch->psaa)->grf & 1)
                    pbatch->grf |= 0x10;
                if (((SAAFIELDS *)pbatch->psaa)->grf & 2)
                    pbatch->grf |= 8;
            }
            if (pbatch->grf & 0x20)
                pbatch->aivtx = (int *)PvAllocStackClearP(pbatch->cvtx << 2);
            cvtxTotal += pbatch->cvtx;
            if (D_0036DBB0 != 0)
                pbatch->grf &= ~2;
            switch (pbatch->pshd->shdk)
            {
            case 3:
                pbatch->grf |= 6;
                break;
            case 7:
                if (!(pbatch->pshd->grfshd & 0x10))
                    pbatch->grf |= 4;
                break;
            }
        }
        FRAME scope;
        int cvtxFile = pbis->U8Read();
        VECTOR *aposFile = (VECTOR *)PvAllocStackP(cvtxFile * sizeof(VECTOR));
        pbis->Read(cvtxFile * sizeof(VECTOR), aposFile);
        UVF *auvFile = (UVF *)PvAllocStackP(cvtxFile * sizeof(UVF));
        pbis->Read(cvtxFile * sizeof(UVF), auvFile);
        VECTOR *anormFile = (VECTOR *)PvAllocStackP(cvtxFile * sizeof(VECTOR));
        pbis->Read(cvtxFile * sizeof(VECTOR), anormFile);
        RGBA *argbaFile = (RGBA *)PvAllocStackP(cvtxFile * sizeof(RGBA));
        pbis->Read(cvtxFile * sizeof(RGBA), argbaFile);
        for (RGBA *prgba = argbaFile; prgba < argbaFile + cvtxFile; prgba++)
            func_00236908(prgba);
        int fAlpha = pbis->S8Read();
        if (psubglob->bUnk00 < 8)
            fAlpha = (psubglob->bUnk00 < 2) ? fAlpha : 1;
        void *pvWeights;
        if (psubglob->cbnd != 0)
        {
            for (int iwt = 0; iwt < 4; iwt++)
                phdr->aiqwBone[iwt] = psubglob->iqwBone + pbis->U8Read() * 4;
            pvWeights = PvAllocStackP(CwtFromSubglob(psubglob) * cvtxFile);
            pbis->Read(CwtFromSubglob(psubglob) * cvtxFile, pvWeights);
        }
        else
        {
            pvWeights = 0;
        }
        uchar *pbVtx = (uchar *)PvAllocStackP(cvtxTotal);
        uint *punBits;
        uint un = 1;
        pbis->Read(cvtxTotal, pbVtx);
        int cbBits = ((cvtxTotal + 31) / 32) * 4;
        int fMulti = 0;
        uint *aunBits = (uint *)PvAllocStackP(cbBits);
        pbis->Read(cbBits, aunBits);
        punBits = aunBits;
        if ((psubglob->bUnk02 & 0x23) || psubglob->cbnd != 0 || spec.iSpec != -1)
            fMulti = 1;
        int fNoSaa = !fMulti && abatch[0].psaa == 0 && abatch[1].psaa == 0;
        int iqw = iqwBase;
        phdr->iqwBase = iqw;
        VERTREC *arec;
        if (psubglob->cbnd == 0 && !(psubglob->bUnk02 & 3) && spec.iSpec == -1)
        {
            arec = 0;
        }
        else
        {
            if (psubglob->bUnk02 & 0x40)
            {
                uchar *pbV = pbVtx;
                arec = (VERTREC *)PvAllocStackP(cvtxTotal * sizeof(VERTREC));
                VERTREC *prec = arec;
                for (int ib = 0; ib < cbatchThis; ib++)
                {
                    BATCH *pbatch = &abatch[ib];
                    pbatch->ivtxOwn = 0;
                    for (int iv = 0; iv < pbatch->cvtx; iv++)
                    {
                        prec->ivtxFile = *pbV++;
                        prec->ivtxFirst = iv;
                        prec->ivtx = iv;
                        prec->pbatch = pbatch;
                        prec->pbatchFirst = pbatch;
                        prec++;
                    }
                }
            }
            else
            {
                VERTREC **apvtx = (VERTREC **)PvAllocStackClearP(cvtxFile << 2);
                arec = (VERTREC *)PvAllocStackP(cvtxTotal * sizeof(VERTREC));
                VERTREC *prec = arec;
                for (int ib = 0; ib < cbatchThis; ib++)
                    abatch[ib].ivtxOwn = abatch[ib].cvtx;
                uchar *pb = pbVtx + cvtxTotal;
                BATCH *pbatchFirst = &abatch[cbatchThis - 1];
                for (int ib = cbatchThis - 1; ib >= 0; ib--)
                {
                    BATCH *pbatch = &abatch[ib];
                    int iv = pbatch->cvtx;
                    while (--iv >= 0)
                    {
                        int ivtxFile = *--pb;
                        if (apvtx[ivtxFile] != 0)
                        {
                            *prec = *apvtx[ivtxFile];
                        }
                        else
                        {
                            prec->pbatchFirst = pbatchFirst;
                            prec->ivtxFile = ivtxFile;
                            prec->ivtxFirst = --pbatchFirst->ivtxOwn;
                            apvtx[ivtxFile] = prec;
                            if (pbatchFirst->ivtxOwn == 0)
                                pbatchFirst--;
                        }
                        prec->ivtx = iv;
                        prec->pbatch = pbatch;
                        prec++;
                    }
                    if (!fMulti)
                    {
                        pbatchFirst = &abatch[ib - 1];
                        memset(apvtx, 0, cvtxFile << 2);
                    }
                }
                qsort(arec, cvtxTotal, sizeof(VERTREC), func_0018F650);
            }
        }
        if (spec.iSpec != -1)
        {
            phdr->apart[0].iqwSpec = phdr->apart[1].iqwSpec = iqw;
            iqw += 3;
            vifs.AddVifUnpack(UPK_V4_32, 3, &spec, phdr->apart[0].iqwSpec);
        }
        int ib;
        uchar *pbVtxCur = pbVtx;
        for (ib = 0; ib < cbatchThis; ib++)
        {
            BATCH *pbatch = &abatch[ib];
            BATCHPART0 *ppart = &phdr->apart[ib];
            ppart->cvtxFlag = pbatch->cvtx | 0x8000;
            ppart->oidAltSat = pbatch->pshd->OidAltSat;
            ppart->cframe = pbatch->pshd->cframe;
            for (int ishdp = 0; ishdp < 3; ishdp++)
            {
                for (int ibPrev = 0; ibPrev < ib; ibPrev++)
                {
                    BATCH *pbatchPrev = &abatch[ibPrev];
                    BATCHPART0 *ppartPrev = &phdr->apart[ibPrev];
                    if (pbatch->pshd == pbatchPrev->pshd && ((pbatch->grf >> ishdp) & 1) && ((pbatchPrev->grf >> ishdp) & 1))
                    {
                        ppart->aiqwShdp[ishdp] = ppartPrev->aiqwShdp[ishdp];
                        break;
                    }
                }
            }
            for (int ishdp = 0; ishdp < 3; ishdp++)
            {
                if (ppart->aiqwShdp[ishdp] == 0 && ((pbatch->grf >> ishdp) & 1))
                {
                    if (psubglob->bUnk02 & 0x10)
                    {
                        int ioid = pglobset->cnUnk2c;
                        while (--ioid >= 0)
                            iqw += func_00235D08(func_00235E60(pglobset->anUnk30[ioid]), ishdp, iqw, &vifs);
                    }
                    ppart->aiqwShdp[ishdp] = iqw;
                    iqw += func_00235CC0(pbatch->pshd, ishdp, iqw, &vifs);
                }
            }
            if (pbatch->psaa != 0)
            {
                for (int ibPrev = 0; ibPrev < ib; ibPrev++)
                {
                    BATCH *pbatchPrev = &abatch[ibPrev];
                    BATCHPART0 *ppartPrev = &phdr->apart[ibPrev];
                    if (pbatch->psaa == pbatchPrev->psaa)
                    {
                        ppart->iqwSaa = ppartPrev->iqwSaa;
                        break;
                    }
                }
                if (ppart->iqwSaa == 0)
                {
                    ppart->iqwSaa = iqw;
                    iqw += func_00237060(pbatch->psaa, iqw, &vifs, pglob);
                }
            }
            iqw += 1;
            ppart->iqwVtx = iqw;
            iqw += pbatch->cvtx * 4;
            ppart->iqwUv = iqw;
            ppart->iqwEnd = ppart->iqwVtx + (((pbatch->cvtx / 2) & ~3) + 2) * 4;
            if (arec != 0)
                ppart->iqwOwn = ppart->iqwVtx + pbatch->ivtxOwn * 4;
            if (psubglob->cbnd != 0)
            {
                ppart->iqwWeights = iqw;
                iqw += pbatch->cvtx - pbatch->ivtxOwn;
                if (psubglob->bUnk02 & 3)
                    phdr->grf |= 0x20;
                else
                    phdr->grf |= 0x10;
            }
            if (pbatch->pshd->shdk == 3 && phdr->iqwShadow == 0)
            {
                phdr->apart[0].aiqwShdp[3] = phdr->apart[1].aiqwShdp[3] = iqw;
                iqw += func_00235CC0(pbatch->pshd, 3, iqw, &vifs);
                ushort *pus;
                vifs.UnpackHelper(UPK_S16, 1, iqw, 0, (uint **)&pus);
                *pus = iqw + 2;
                phdr->iqwShadow = iqw;
                iqw += 0x1a;
            }
            if (spec.iSpec != -1)
            {
                if (psubglob->bUnk02 & 3)
                {
                    ppart->iqwUvLink = ppart->iqwOwn + 1;
                }
                else
                {
                    ppart->iqwUvLink = iqw;
                    int c = pbatch->cvtx - pbatch->ivtxOwn;
                    iqw += c;
                    vifs.UnpackHelper((UPK)0x1e, c, ppart->iqwUvLink, 0, (uint **)&pbatch->pbNorm);
                }
            }
            if (pglob->pwrbg != 0)
            {
                ppart->iqwWeights = iqw;
                int cqwWarp = pglob->pwrbg->cmat * pbatch->cvtx;
                phdr->grf |= 0x40;
                iqw += cqwWarp;
            }
            vifs.AddVifStcycl(1, 4);
            if ((psubglob->bUnk02 & 3) || psubglob->cbnd != 0 || spec.iSpec != -1)
                vifs.UnpackHelper((UPK)0x19, pbatch->cvtx, ppart->iqwVtx, 0, (uint **)&pbatch->pvUvLink);
            else
                vifs.UnpackHelper((UPK)0x15, pbatch->cvtx, ppart->iqwVtx, 0, (uint **)&pbatch->pvUv);
            if (psubglob->bUnk02 & 3)
            {
                if (pbatch->ivtxOwn < pbatch->cvtx)
                {
                    vifs.UnpackHelper((UPK)0x1e, pbatch->cvtx - pbatch->ivtxOwn, ppart->iqwOwn + 1, 0, (uint **)&pbatch->pbNorm);
                    vifs.UnpackHelper(UPK_V4_8, pbatch->cvtx - pbatch->ivtxOwn, ppart->iqwOwn + 2, 0, (uint **)&pbatch->pbRgb);
                }
            }
            else
            {
                vifs.Align(0);
                vifsAux.AddDmaRefs((vifs.m_pb - (uchar *)pqwChain) >> 4, pqwChain);
                pqwChain = (QW *)vifs.m_pb;
                vifsAux.AddDmaCnt();
                vifsAux.UnpackHelper(UPK_V4_5, pbatch->cvtx, ppart->iqwVtx + 1, 0, (uint **)&pbatch->obColorA);
                if ((pbatch->grf & 2) && pbatch->pshd->shdk != 3)
                    vifsAux.UnpackHelper(UPK_V4_5, pbatch->cvtx, ppart->iqwVtx + 2, 0, (uint **)&pbatch->obColorB);
                if (fAlpha != 0 || pbatch->obColorB != 0)
                {
                    vifsAux.AddVifStmask(0x3f3f3f3f);
                    if (fAlpha != 0)
                        vifsAux.UnpackHelper(UPK_S8, pbatch->cvtx, ppart->iqwVtx + 1, 0, (uint **)&pbatch->pbAlpha);
                    if (pbatch->obColorB != 0)
                        vifsAux.UnpackHelper(UPK_S8, pbatch->cvtx, ppart->iqwVtx + 2, 0, (uint **)&pbatch->obAlpha);
                    vifsAux.AddVifStmask(0);
                }
                vifsAux.EndDmaCnt();
            }
            if (psubglob->bUnk02 & 8)
            {
                func_0027E388(&vifs, 2);
                vifs.UnpackHelper((UPK)0x1d, pbatch->cvtx, ppart->iqwVtx + 3, 0, (uint **)&pbatch->pvPosDelta);
                func_0027E388(&vifs, 0);
            }
            else
            {
                vifs.UnpackHelper(UPK_V4_32, pbatch->cvtx, ppart->iqwVtx + 3, 0, (uint **)&pbatch->pvPos);
            }
            vifs.AddVifStcycl(1, 1);
            if (psubglob->cbnd != 0 && pbatch->ivtxOwn < pbatch->cvtx)
            {
                if (psubglob->cbnd < 4)
                {
                    vifs.AddVifStrow(&D_0036DBC0);
                    vifs.AddVifStmask(D_00345000[CwtFromSubglob(psubglob)]);
                }
                vifs.UnpackHelper((UPK)D_00345018[CwtFromSubglob(psubglob)], pbatch->cvtx - pbatch->ivtxOwn, ppart->iqwWeights,
                                  0, (uint **)&pbatch->pbWeights);
                if (psubglob->cbnd < 4)
                    vifs.AddVifStmask(0);
            }
            if (pglob->pwrbg != 0)
            {
                int iqwW = ppart->iqwWeights;
                WRBGBATCH *pwb = (WRBGBATCH *)PvAllocClear(pheap, sizeof(WRBGBATCH), 4);
                func_0011AD80(&pglob->pwrbg->slBatch, pwb);
                pwb->cvtx = pbatch->cvtx;
                pwb->pvPos = pbatch->pvPos;
                for (int imat = 0; imat < pglob->pwrbg->cmat; imat++)
                {
                    vifs.UnpackHelper(UPK_V4_32, pbatch->cvtx, iqwW, 0, (uint **)&pwb->apvWarp[imat]);
                    memset(pwb->apvWarp[imat], 0, pbatch->cvtx << 4);
                    iqwW += pbatch->cvtx;
                }
            }
            if (!(psubglob->bUnk02 & 3))
            {
                int shdk = pbatch->pshd->shdk;
                if (shdk != 1 && shdk != 7)
                {
                    RGBA5551 *pcol = (RGBA5551 *)pbatch->obColorA;
                    uchar *pbAlpha = pbatch->pbAlpha;
                    for (int iv = 0; iv < pbatch->cvtx; iv++)
                    {
                        RGBA rgbaA = argbaFile[pbVtxCur[iv]];
                        RGBA rgbaB = pbatch->pshd->rgba;
                        uchar a = (rgbaA.bAlpha * rgbaB.bAlpha + 0xff) / 0x1fe;
                        uchar r = (rgbaA.bRed * rgbaB.bRed + 0xff) / 256;
                        uchar g = (rgbaA.bGreen * rgbaB.bGreen + 0xff) / 256;
                        uchar b = (rgbaA.bBlue * rgbaB.bBlue + 0xff) / 256;
                        RGBA5551 *pc = pcol++;
                        RGBA5551 col;
                        col.r = r >> 3;
                        col.g = g >> 3;
                        col.b = b >> 3;
                        col.a = a >> 7;
                        *pc = col;
                        if (pbAlpha != 0)
                        {
                            *pbAlpha = a;
                            pbAlpha++;
                        }
                    }
                }
                else
                {
                    if (D_00345040 != 0 || !(pbatch->grf & 0x20))
                    {
                        for (int iofs = 0; iofs < pbatch->cvtx; iofs += 0x26)
                        {
                            int n = Min(0x26, pbatch->cvtx - iofs);
                            uint *pun;
                            vifsLit.UnpackHelper(UPK_V4_32, 3, 0x307, 0, &pun);
                            pun[0] = 0x30a;
                            pun[1] = pun[0] + n * 3;
                            pun[2] = pun[1];
                            pun[3] = pun[2] + n;
                            pun[4] = pun[3] + n;
                            pun[5] = pbatch->obColorA + iofs * 2;
                            pun[6] = pbatch->obColorB + iofs * 2;
                            if (fAlpha != 0)
                                pun[8] = (uint)pbatch->pbAlpha + iofs;
                            else
                                pun[8] = 0;
                            pun[9] = pbatch->obAlpha + iofs;
                            *(float *)&pun[7] = (float)pbatch->pshd->OidAltSat * 0.000244140625f;
                            apvLit[nLit] = pun;
                            nLit++;
                            vifsLit.AddVifStcycl(1, 3);
                            VECTOR *pvNorm;
                            RGBA *prgbaCol;
                            VECTOR *pvPos;
                            vifsLit.UnpackHelper(UPK_V3_32, n, 0x30a, 0, (uint **)&pvNorm);
                            vifsLit.UnpackHelper(UPK_V4_8, n, 0x30b, 0, (uint **)&prgbaCol);
                            vifsLit.UnpackHelper(UPK_V3_32, n, 0x30c, 0, (uint **)&pvPos);
                            vifsLit.AddVifStcycl(1, 1);
                            {
                                for (int k = 0; k < n; k++)
                                {
                                    int ivtxFile = pbVtxCur[iofs + k];
                                    *pvNorm++ = anormFile[ivtxFile];
                                    *pvPos++ = aposFile[ivtxFile];
                                    RGBA rgba = argbaFile[ivtxFile];
                                    RGBA rgbaB = pbatch->pshd->rgba;
                                    rgba.bRed = (rgba.bRed * rgbaB.bRed + 0xff) / 256;
                                    rgba.bGreen = (rgba.bGreen * rgbaB.bGreen + 0xff) / 256;
                                    rgba.bBlue = (rgba.bBlue * rgbaB.bBlue + 0xff) / 256;
                                    rgba.bAlpha = (rgba.bAlpha * rgbaB.bAlpha + 0xff) / 0x1fe;
                                    *prgbaCol++ = rgba;
                                }
                            }
                            vifsLit.AddVifMscal(D_00000000 + 0x10);
                            AddDmaInt(&vifsLit, 0x90000000);
                        }
                    }
                }
            }
            CLUTPAL *ppal = 0;
            if ((pbatch->grf & 0x20) && pclutset != 0)
            {
                for (int ipal = 0; ipal < pclutset->cpal; ipal++)
                {
                    ppal = &pclutset->apal[ipal];
                    if (ppal->ibatch == ibatch)
                        break;
                }
            }
            for (int iv = 0; iv < pbatch->cvtx; iv++)
            {
                uint ivtxFile = pbVtxCur[iv];
                float gW = *pgFit;
                if (*punBits & un)
                    gW += 4096.0f;
                if (psubglob->bUnk02 & 8)
                {
                    func_001951A0(&xq, (short *)((char *)pbatch->pvPosDelta + iv * 8), &aposFile[ivtxFile], gW);
                }
                else
                {
                    if (psubglob->cbnd == 0)
                    {
                        SetPosFixed((int *)((char *)pbatch->pvPos + iv * 0x10), &aposFile[ivtxFile]);
                    }
                    else if (iv < pbatch->ivtxOwn)
                    {
                        VECTOR4 posNone = {-1.0f, -1.0f, -1.0f};
                        SetPosFixed((int *)((char *)pbatch->pvPos + iv * 0x10), (VECTOR *)&posNone);
                    }
                    *(float *)((char *)pbatch->pvPos + iv * 0x10 + 0xc) = gW;
                }
                un <<= 1;
                if (un == 0)
                {
                    punBits++;
                    un = 1;
                }
                if (pbatch->pvUvLink != 0)
                {
                    ((UVLINK *)((uchar *)pbatch->pvUvLink + iv * 6))->u = (int)(auvFile[ivtxFile].u * 4096.0f + 0.5f);
                    ((UVLINK *)((uchar *)pbatch->pvUvLink + iv * 6))->v = (int)(auvFile[ivtxFile].v * 4096.0f + 0.5f);
                }
                else
                {
                    ((short *)((char *)pbatch->pvUv + iv * 4))[0] = (short)(int)(auvFile[ivtxFile].u * 4096.0f + 0.5f);
                    ((short *)((char *)pbatch->pvUv + iv * 4))[1] = (short)(int)(auvFile[ivtxFile].v * 4096.0f + 0.5f);
                }
                if (pbatch->grf & 0x20)
                {
                    if (ppal != 0)
                    {
                        pbatch->aivtx[iv] = ivtxFile;
                        CLUTCOLOR *pcc = &ppal->acolor[ivtxFile];
                        ((ushort *)pbatch->obColorA)[iv] = pcc->ucA;
                        ((ushort *)pbatch->obColorB)[iv] = pcc->ucB;
                        ((uchar *)pbatch->obAlpha)[iv] = pcc->bAlpha;
                        if (pbatch->pbAlpha != 0)
                        {
                            RGBA rgbaA = argbaFile[ivtxFile];
                            RGBA rgbaB = pbatch->pshd->rgba;
                            pbatch->pbAlpha[iv] = (rgbaA.bAlpha * rgbaB.bAlpha + 0xff) / 0x1fe;
                        }
                    }
                }
            }
            pbVtxCur += pbatch->cvtx;
            if (!fMulti)
            {
                if (ib == 0)
                {
                    if (psubglob->bUnk00 == 0xa || psubglob->bUnk00 == 0xe)
                    {
                        vifs.AddVifMscal(D_00003638);
                        vifs.AddVifMscal(D_00003648);
                    }
                    else
                    {
                        vifs.AddVifMscal(D_00003638);
                        char *pvMscal;
                        switch (ibatch)
                        {
                        case 0:
                            pvMscal = fNoSaa ? D_00003EB8 : D_000036D0;
                            break;
                        case 1:
                            pvMscal = fNoSaa ? D_00003F00 : D_00003758;
                            break;
                        default:
                            pvMscal = fNoSaa ? D_00003F48 : D_000037A0;
                            break;
                        }
                        vifs.AddVifMscal(pvMscal);
                    }
                }
                else if (psubglob->bUnk00 == 0xa || psubglob->bUnk00 == 0xe)
                {
                    vifs.AddVifMscal(D_000037C8);
                }
                else
                {
                    vifs.AddVifMscal(fNoSaa ? D_00003F80 : D_00003BE8);
                }
            }
        }
        if (fMulti)
        {
            if (psubglob->bUnk00 == 0xa || psubglob->bUnk00 == 0xe)
            {
                vifs.AddVifMscal(D_00003638);
                vifs.AddVifMscal(D_00003648);
                vifs.AddVifMscal(D_000037C8);
            }
            else
            {
                vifs.AddVifMscal(D_00003638);
                switch (ibatch)
                {
                case 0:
                    vifs.AddVifMscal(D_000036D0);
                    break;
                case 1:
                    vifs.AddVifMscal(D_00003758);
                    break;
                default:
                    vifs.AddVifMscal(D_000037A0);
                    break;
                }
                vifs.AddVifMscal(D_00003BE8);
            }
        }
        if (arec != 0)
        {
            VERTREC *precEnd = arec + cvtxTotal;
            BATCH *pbatchLast = 0;
            for (VERTREC *prec = arec; prec < precEnd; prec++)
            {
                BATCH *pbatch = prec->pbatch;
                BATCHPART0 *ppartRec = &phdr->apart[pbatch - abatch];
                if (pbatchLast != prec->pbatchFirst)
                {
                    pbatchLast = prec->pbatchFirst;
                    BATCHPART0 *ppartFirst = &phdr->apart[pbatchLast - abatch];
                    int iqwSkin = ppartRec->iqwVtx + (prec->ivtx << 2);
                    ppartFirst->iqwSkin = iqwSkin;
                }
                uint usLink;
                if (prec == precEnd - 1 || prec[1].pbatchFirst != pbatchLast)
                {
                    usLink = 0;
                }
                else
                {
                    BATCHPART0 *ppartNext = &phdr->apart[prec[1].pbatch - abatch];
                    usLink = ppartNext->iqwVtx + prec[1].ivtx * 4;
                    if (prec->ivtxFirst == prec[1].ivtxFirst)
                        usLink |= 0x8000;
                }
                ((UVLINK *)((uchar *)pbatch->pvUvLink + prec->ivtx * 6))->link = usLink;
            }
            for (VERTREC *prec = arec; prec < precEnd; )
            {
                int ivtxFile = prec->ivtxFile;
                BATCH *pbatchFirst = prec->pbatchFirst;
                int ivtxFirst = prec->ivtxFirst;
                RGBA rgbaA = argbaFile[ivtxFile];
                int bRed = rgbaA.bRed;
                int bGreen = rgbaA.bGreen;
                int bBlue = rgbaA.bBlue;
                int bMax;
                if (bRed > bGreen && bRed > bBlue)
                {
                    bMax = bRed;
                }
                else if (bGreen > bBlue)
                    bMax = bGreen;
                else
                    bMax = bBlue;
                float gBright = (float)bMax * 0.003921569f;
                if (pbatchFirst->pbNorm != 0)
                {
                    VECTOR *pnorm = &anormFile[ivtxFile];
                    char *pbN = (char *)pbatchFirst->pbNorm + (ivtxFirst - pbatchFirst->ivtxOwn) * 4;
                    pbN[0] = (int)(pnorm->x * 127.0f);
                    pbN[1] = (int)(pnorm->y * 127.0f);
                    pbN[2] = (int)(pnorm->z * 127.0f);
                    pbN[3] = (int)(gBright * 127.0f);
                }
                if (pbatchFirst->pbRgb != 0)
                {
                    RGBA rgbaB = pbatchFirst->pshd->rgba;
                    uchar *pbC = pbatchFirst->pbRgb + (ivtxFirst - pbatchFirst->ivtxOwn) * 4;
                    pbC[0] = (rgbaA.bRed * rgbaB.bRed + 0xff) / 512;
                    pbC[1] = (rgbaA.bGreen * rgbaB.bGreen + 0xff) / 512;
                    pbC[2] = (rgbaA.bBlue * rgbaB.bBlue + 0xff) / 512;
                    pbC[3] = (rgbaA.bAlpha * rgbaB.bAlpha + 0xff) / 0x1fe;
                }
                if (psubglob->cbnd != 0)
                {
                    SetPosFixed((int *)(ivtxFirst * 0x10 + (uint)pbatchFirst->pvPos), &aposFile[ivtxFile]);
                    CopyAb(pbatchFirst->pbWeights + (ivtxFirst - pbatchFirst->ivtxOwn) * CwtFromSubglob(psubglob), (char *)pvWeights + ivtxFile * CwtFromSubglob(psubglob), CwtFromSubglob(psubglob));
                }
                prec++;
                while (prec < precEnd && prec->pbatchFirst == pbatchFirst && prec->ivtxFirst == ivtxFirst)
                    prec++;
            }
        }
    }
    int cqwMain;
    char *pbOld;
    char *pbNew;
    if (psubglob->bUnk02 & 3)
    {
        vifs.EndDmaCnt();
        vifs.AddDmaRet();
        vifs.DetachCopySw(pheap, &cqwMain, (QW **)&pbOld, (QW **)&pbNew);
        psubglob->cqw = cqwMain;
        pglob->pvUnk10 = pbNew;
    }
    else
    {
        vifs.Align(0);
        vifsAux.AddDmaRefs((vifs.m_pb - (uchar *)pqwChain) >> 4, pqwChain);
        vifsAux.AddDmaRet();
        vifs.DetachCopySw(pheap, &cqwMain, (QW **)&pbOld, (QW **)&pbNew);
        if (pglob->psaa != 0)
        {
            ((SAAFIELDS *)pglob->psaa)->cqwMain = cqwMain;
            ((SAAFIELDS *)pglob->psaa)->pvMain = pbNew;
        }
        func_0018FBB0(psubglob, pglob, (vifsAux.m_pb - vifsAux.m_ab) / sizeof(QW), vifsAux.m_ab, cqwMain, pbNew, pbOld);
        if (nLit > 0)
        {
            vifsLit.EndDmaCnt();
            vifsLit.AddDmaRet();
            int cqwLit = (vifsLit.m_pb - vifsLit.m_ab) / sizeof(QW);
            psgl->nUnk04 = cqwLit;
            psubglob->pvLit = PvAllocCopy(pheap, cqwLit << 4, vifsLit.m_ab, 0x31);
        }
    }
    if (pclutset != 0)
        pglobset->nUnk4c = -2;
    pglob->cUnk = D_0046FF40 - pglob->iUnkFirst;
    func_00235D78(pglob->iUnkFirst, pglob->cUnk, cqwMain << 4, pbOld, pbNew);
    if (pglob->pwrbg != 0)
    {
        for (WRBGBATCH *pwb = (WRBGBATCH *)pglob->pwrbg->slBatch.head; pwb != 0; pwb = pwb->pwrbgbatchNext)
        {
            RelocPpv(pbOld, cqwMain << 4, pbNew, (char **)&pwb->pvPos);
            for (int imat = 0; imat < pglob->pwrbg->cmat; imat++)
                RelocPpv(pbOld, cqwMain << 4, pbNew, (char **)&pwb->apvWarp[imat]);
        }
    }
    if (psubglob->bUnk02 & 0x40)
    {
        int cbatchAll = 0;
        int i;
        for (i = 0; i < cbatch; i++)
            cbatchAll += acbatch[i];
        BATCHRECS *pbatchrecs = (BATCHRECS *)PvAllocSwClearP(sizeof(BATCHRECS));
        pbatchrecs->pbatchrecsNext = (BATCHRECS *)pglobset->pbatchrecsFirst;
        pglobset->pbatchrecsFirst = pbatchrecs;
        pbatchrecs->psubglob = psubglob;
        pbatchrecs->cbatch = cbatchAll;
        pbatchrecs->abatchrec = (BATCHREC *)PvAllocSwP(cbatchAll << 5);
        BATCHREC *pbr = pbatchrecs->abatchrec;
        for (i = 0; i < cbatch; i++)
        {
            BATCH *pb = apbatch[i];
            for (int j = 0; j < acbatch[i]; j++)
            {
                pbr->cvtx = pb->cvtx;
                pbr->grf = pb->grf;
                pbr->pvPos = PbReloc(pbOld, cqwMain << 4, pbNew, (char *)pb->pvPos);
                pbr->pvUv = PbReloc(pbOld, cqwMain << 4, pbNew, (char *)pb->pvUv);
                pbr->pvUvLink = PbReloc(pbOld, cqwMain << 4, pbNew, (char *)pb->pvUvLink);
                pbr->pbRgb = PbReloc(pbOld, cqwMain << 4, pbNew, (char *)pb->pbRgb);
                pbr->pbNorm = PbReloc(pbOld, cqwMain << 4, pbNew, (char *)pb->pbNorm);
                pbr->unk_0x1c = 0;
                pb++;
                pbr++;
            }
        }
    }
    func_0018F6B8(pglobset, psubglob, pglob, psubglobx, cSubExtra, cbatch, acbatch, apbatch, pbis);
}
