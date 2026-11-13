// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00211170: scene render-list walk. Sly 3 version of Sly 2 func_001D5808 (references/sly2/src/hand): the scene's BLOCK tree is
// walked with a stack, every RENDER (4 per block) of the block is tested against all views (func_0018E500 returns one weight per
// view, VU MAC-flag test as in func_00201390) and queued: kind 1 pushes the child block, kind 4 collects a deferred object (its
// virtual call runs at the end), kind 3 queues a prebuilt packet and kind 0 builds the mesh packet (matrices, skin matrices,
// parameters, optional near flag for sort 6/7) once and one render-list record (RPL) per distinct view weight. Like
// func_0018E800 the per-view positions live in a VECTOR apos[4] (its empty constructor is the 3-iteration nop loop).
// Notes: i (objects, skin matrices, deferred loop) and j (apos loop, packet loop) are function-level counters shared by several loops
// (global-alloc priority); M4 results come from the value-returning externs (struct-return temps); the empty do-while in CopyQws
// (as in func_0018E800) and the allocation-only "j" input of SetX (as in Sly 2 func_001D5808) keep the target's scheduling and
// registers; func_0018E500 is declared with the float first (same registers) so its load is issued first.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
union U
{
    qword q;
    float f[4];
    uint w[4];
};
struct M4
{
    float mat[4][4];
} __attribute__((aligned(16)));
struct V4
{
    float x, y, z, w;
} __attribute__((aligned(16)));
struct VECTOR
{
    float x, y, z, w;
    VECTOR() {}
} __attribute__((aligned(16)));
struct XF
{
    char pad[0x40];
    M4 mat;
};
struct VTENT
{
    short delta, pad;
    void *(*pfn)(void *, ...);
};
struct OBJ
{
    char pad[0xC];
    VTENT *pvt;
};
struct BLOCK;
enum KIND
{
    KIND_NONE = -1,
    KIND_MESH = 0,
    KIND_BLOCK = 1,
    KIND_PACKET = 3,
    KIND_DEFERRED = 4
};
struct RENDER
{
    U sphere;
    float g;
    KIND kind : 4;
    long channels : 8;
    long sort : 6;
    ulong hidden : 1;
    ulong index : 13;
    void *pv;
    BLOCK *pblockNext;
};
struct BLOCK
{
    RENDER ar[4];
};
struct STACK
{
    uint c;
    BLOCK *a[256];
};
struct SKIN
{
    char pad[0xC];
    OBJ *powner;
    int cmat;
    M4 *amatFirst;
    M4 *amatSecond;
    int pad1C[2];
    uint ib;
};
struct MESH
{
    int unknown;
    XF *pxf;
    M4 *pmatParent;
    uint grf;
    void *pv;
    int pad14[2];
    SKIN *pskin;
    int pad20[2];
};
struct DESC
{
    int unknown;
    float dist;
    void *chain;
    int padC[2];
};
struct SCENE
{
    char pad[0x24];
    int cobj;
    OBJ **apobj;
    char pad2C[0x10];
    DESC *adesc;
    MESH *amesh;
    void *pv44;
    BLOCK *pblockRoot;
    int nStamp;
    float scale;
};
struct VOBJ
{
    char pad[0xC];
    VTENT *pvt;
    char pad10[0x130];
    float rad;
};
struct G
{
    char pad[0x3EB8];
    int cview;
    VOBJ *apview[4];
    U wView;
    qword qwMax;
    char pad3EF0[0x608];
    int nStamp;
};
struct DMA
{
    char pad[0xC];
    uchar *pb;
};
struct RPL
{
    int kind;
    float dist;
    uchar *pb;
    void *pv;
};
extern "C" {
extern DMA D_0036C308;
extern G D_00475480;
extern RPL D_00447B00[];
extern RPL *D_00468D00;
M4 func_0011D558(const M4 &matA, const M4 &matB);
M4 func_0011D768(const M4 &matSrc);
qword func_0018E500(float g, G *pg, qword w, int mask, qword sph);
void func_0018E0B8(SCENE *pscene);
int func_00237120(OBJ *pobj);
void func_00211120(STACK *pstack, BLOCK *pblock);
BLOCK *func_00211148(STACK *pstack);
int func_00174FF0(int a, int i);
int func_00174FF8(int a, int b);
}
static inline int Flags(int a, int b, int i) { return func_00174FF8(b, func_00174FF0(a, i)); }
static inline int FZero(qword v)
{
    int mac;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(mac) : "j"(v));
    return (mac & 0xF) == 0xF;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float Scalar(qword v)
{
    float f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(v));
    return f;
}
static inline float SqLength(qword v) { return Scalar(Dot(v, v)); }
static inline void SetX(float *pg, qword q) { __asm__("sw %1,%0" : "=m"(*pg) : "r"(q), "j"(q)); }
static inline bool Near(qword a, qword s, float r) { return SqLength(Sub(a, s)) < r * r; }
static inline qword Position(VOBJ *o)
{
    VTENT *e = &o->pvt[36];
    return *(qword *)((char *)e->pfn((char *)o + e->delta) + 0x30);
}
static inline void CopyQws(uint *pwDst, const uint *pwSrc, int cw)
{
    do
    {
    } while (0);
    for (int k = 0; k < cw; k += 4)
    {
        uint w0 = pwSrc[0];
        uint w1 = pwSrc[1];
        uint w2 = pwSrc[2];
        uint w3 = pwSrc[3];
        pwSrc += 4;
        pwDst[0] = w0;
        pwDst[1] = w1;
        pwDst[2] = w2;
        pwDst[3] = w3;
        pwDst += 4;
    }
}
template <uint TAG> static inline void UnpackQws(const void *pv, int cw)
{
    DMA *pdma = &D_0036C308;
    *(uint *)pdma->pb = TAG;
    pdma->pb += 4;
    CopyQws((uint *)pdma->pb, (const uint *)pv, cw);
    pdma->pb += cw * 4;
}
static inline void UnpackQws(uint tag, const void *pv, int cw)
{
    DMA *pdma = &D_0036C308;
    *(uint *)pdma->pb = tag;
    pdma->pb += 4;
    CopyQws((uint *)pdma->pb, (const uint *)pv, cw);
    pdma->pb += cw * 4;
}
static inline void CopyWords(uint *punDst, const uint *punSrc, int cun)
{
    int cunOdd = cun & 3;
    for (int i = 0; i < cunOdd; i++)
        *punDst++ = *punSrc++;
    for (int i = cunOdd; i < cun; i += 4)
    {
        uint w0 = punSrc[0];
        uint w1 = punSrc[1];
        uint w2 = punSrc[2];
        uint w3 = punSrc[3];
        punSrc += 4;
        punDst[0] = w0;
        punDst[1] = w1;
        punDst[2] = w2;
        punDst[3] = w3;
        punDst += 4;
    }
}
static inline void UnpackWords(uint tag, const void *pv, int cw)
{
    DMA *pdma = &D_0036C308;
    *(uint *)pdma->pb = tag;
    pdma->pb += 4;
    CopyWords((uint *)pdma->pb, (const uint *)pv, cw);
    pdma->pb += cw * 4;
}
static inline void PadQw()
{
    DMA *pdma = &D_0036C308;
    for (uchar *pbPad = pdma->pb; (uint)pbPad & 0xF; pbPad = pdma->pb)
    {
        *(uint *)pbPad = 0;
        pdma->pb += 4;
    }
}
extern "C" void func_00211170(STACK *pstack, SCENE *pscene)
{
    OBJ *apobjDeferred[512];
    int i;
    int j;
    for (i = 0; i < pscene->cobj; i++)
    {
        OBJ *pobj = pscene->apobj[i];
        if (func_00237120(pobj))
        {
            VTENT *pvte = &pobj->pvt[8];
            pvte->pfn((char *)pobj + pvte->delta);
        }
    }
    if (pscene->nStamp != D_00475480.nStamp)
        func_0018E0B8(pscene);
    int cDeferred = 0;
    func_00211120(pstack, pscene->pblockRoot);
    VECTOR apos[4];
    for (j = 0; j < D_00475480.cview; j++)
    {
        float *pwv = D_00475480.wView.f;
        if (pwv[j] > 0.0f)
            *(qword *)&apos[j] = Position(D_00475480.apview[j]);
    }
    BLOCK *pblock;
    while ((pblock = func_00211148(pstack)) != 0)
    {
        for (uint ir = 0; ir < 4; ir++)
        {
            RENDER *prender = &pblock->ar[ir];
            if (prender->kind == -1)
                break;
            if (prender->kind == 5)
                continue;
            U w;
            w.q = func_0018E500(prender->g, &D_00475480, D_00475480.wView.q, prender->channels, prender->sphere.q);
            if (FZero(w.q))
                continue;
            switch (prender->kind)
            {
            case 1:
                func_00211120(pstack, (BLOCK *)prender->pv);
                break;
            case 4:
                if ((uint)cDeferred < 512)
                    apobjDeferred[cDeferred++] = (OBJ *)prender->pv;
                break;
            case 3:
            {
                if (prender->hidden)
                    break;
                for (j = 0; j < D_00475480.cview; j++)
                {
                    if (w.f[j] == 0.0f)
                        continue;
                    RPL *prpl = D_00468D00;
                    qword dpos = Sub(prender->sphere.q, *(qword *)&apos[j]);
                    if ((uint)(prpl - D_00447B00) >= 0x2000)
                        break;
                    D_00468D00 = prpl + 1;
                    int sort = prender->sort;
                    prpl->kind = Flags(5, sort, j);
                    SetX(&prpl->dist, Dot(dpos, dpos));
                    if (w.f[j] == 1.0f)
                    {
                        prpl->pb = (uchar *)prender->pv;
                        prpl->pv = 0;
                    }
                    else
                    {
                        switch ((int)prender->sort)
                        {
                        case 2:
                            prpl->kind = Flags(5, 4, j);
                            break;
                        case 3:
                            prpl->kind = Flags(5, 5, j);
                            break;
                        }
                        DMA *pdma = &D_0036C308;
                        prpl->pb = pdma->pb;
                        prpl->pv = (uchar *)prender->pv + 0x70;
                        *(ulong *)pdma->pb = ((ulong)(uint)((uchar *)prender->pv + 0x10) << 32) | 0x40000006;
                        pdma->pb += 0x10;
                        V4 params;
                        params.x = w.f[j];
                        params.y = 1.0f;
                        params.z = pscene->scale;
                        *(uint *)&params.w = 0;
                        *(ulong *)pdma->pb = 0x10000002;
                        pdma->pb += 0x10;
                        UnpackQws<0x6C01C008>(&params, 4);
                        PadQw();
                        *(ulong *)D_0036C308.pb = 0x60000000;
                        D_0036C308.pb += 0x10;
                    }
                }
                break;
            }
            case 0:
            {
                MESH *pmesh = &pscene->amesh[prender->index];
                DESC *pdesc = &pscene->adesc[prender->index];
                if (prender->hidden)
                    break;
                if ((uint)((int)prender->sort - 6) < 2)
                    w.q = Min(w.q, D_00475480.qwMax);
                for (int iview = 0; iview < D_00475480.cview; iview++)
                {
                    if (w.f[iview] == 0.0f)
                        continue;
                    ulong *ptag = (ulong *)D_0036C308.pb;
                    if ((uint)((int)prender->sort - 6) < 2)
                    {
                        int fNear = 0;
                        for (int k = 0; k < D_00475480.cview; k++)
                        {
                            if (w.f[k] == 0.0f)
                                continue;
                            if (Near(*(qword *)&apos[k], prender->sphere.q, prender->sphere.f[3] + D_00475480.apview[k]->rad))
                            {
                                fNear = 1;
                                break;
                            }
                        }
                        *(ulong *)D_0036C308.pb = 0x10000000;
                        D_0036C308.pb += 0x10;
                        UnpackWords(0x6001C012, &fNear, 1);
                    }
                    else
                    {
                        *(ulong *)D_0036C308.pb = 0x10000000;
                        D_0036C308.pb += 0x10;
                    }
                    if (pmesh->pmatParent)
                    {
                        M4 mat;
                        mat = func_0011D558(*pmesh->pmatParent, pmesh->pxf->mat);
                        UnpackQws<0x6C04C000>(&mat, 16);
                    }
                    else
                    {
                        UnpackQws<0x6C04C000>(&pmesh->pxf->mat, 16);
                    }
                    SKIN *pskin = pmesh->pskin;
                    if (pskin)
                    {
                        OBJ *powner = pskin->powner;
                        VTENT *pvte = &powner->pvt[53];
                        pvte->pfn((char *)powner + pvte->delta, pskin);
                        M4 matInv;
                        if (pmesh->pmatParent)
                            matInv = func_0011D768(func_0011D558(*pmesh->pmatParent, pmesh->pxf->mat));
                        else
                            matInv = func_0011D768(pmesh->pxf->mat);
                        uint ib = pskin->ib;
                        for (i = 0; i < pskin->cmat; i++)
                        {
                            if (pskin->amatFirst)
                            {
                                M4 mat;
                                mat = func_0011D558(matInv, pskin->amatFirst[i]);
                                UnpackQws(ib | 0x6C04C000, &mat, 16);
                                ib += 4;
                            }
                            if (pskin->amatSecond)
                            {
                                UnpackQws(ib | 0x6C04C000, &pskin->amatSecond[i], 16);
                                ib += 4;
                            }
                        }
                    }
                    V4 params;
                    params.x = w.f[iview];
                    params.y = 1.0f;
                    params.z = pscene->scale;
                    *(uint *)&params.w = 0;
                    UnpackQws<0x6C01C008>(&params, 4);
                    PadQw();
                    *(uint *)ptag |= ((int)(D_0036C308.pb - (uchar *)ptag) >> 4) - 1;
                    *(ulong *)D_0036C308.pb = 0x60000000;
                    D_0036C308.pb += 0x10;
                    for (int k = iview; k < D_00475480.cview; k++)
                    {
                        if (iview < k)
                        {
                            if (w.f[k] != w.f[iview])
                                continue;
                            w.f[k] = 0.0f;
                        }
                        RPL *prpl = D_00468D00;
                        qword dpos = Sub(prender->sphere.q, *(qword *)&apos[k]);
                        if ((uint)(prpl - D_00447B00) >= 0x2000)
                            break;
                        D_00468D00 = prpl + 1;
                        int sort = prender->sort;
                        prpl->kind = Flags(5, sort, k);
                        if (w.f[k] < 1.0f)
                        {
                            switch ((int)prender->sort)
                            {
                            case 2:
                                prpl->kind = Flags(5, 4, k);
                                break;
                            case 3:
                                prpl->kind = Flags(5, 5, k);
                                break;
                            }
                        }
                        prpl->dist = (pmesh->grf & 0x800) ? pdesc->dist : SqLength(dpos);
                        prpl->pb = (uchar *)ptag;
                        prpl->pv = pmesh->pv;
                    }
                }
                break;
            }
            }
        }
        if (pblock->ar[3].pblockNext)
            func_00211120(pstack, pblock->ar[3].pblockNext);
    }
    for (i = 0; i < cDeferred; i++)
    {
        OBJ *pobj = apobjDeferred[i];
        VTENT *pvte = &pobj->pvt[21];
        pvte->pfn((char *)pobj + pvte->delta);
    }
}
