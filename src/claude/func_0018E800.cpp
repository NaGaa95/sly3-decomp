// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0018E800 (A41): Sly 3 rewrite of Sly 2 func_00168638 (model draw: per-view weights from func_0018E630, VU MAC-flag
// zero tests, packet built once per distinct view weight and queued once per view). func_0018F650 (qsort-style comparator)
// follows in the same unit. D_00321C90 (0.0025 scale) / jump table / D_00321CC8 are this unit's .rodata (0x321C90-0x321CCC).
// Notes: j-loop bound read as D_00475480.cview (== 0x479338): %hi(D_00475480+0x3EB8) is not GCSE-merged with the
// loop-top copy, as in the target; non-const D_003175A0 (no /u) fixes two sched ties; VU_FLOAT2/SqLengthBitsTo use
// allocation-only second alternatives (Sly 2 GBitsSqLengthTo style) so the lw / qmfc2 become reloads.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
union U
{
    qword q;
    float f[4];
    int i[4];
};
struct M4
{
    float mat[4][4];
} __attribute__((aligned(16)));
struct V4
{
    float x, y, z, w;
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
    char pad10[0x1C];
    uchar mask;
    char pad2D[0x7];
    float gain;
    char pad38[0x18];
    XF *pxf;
};
struct VOBJ
{
    char pad[0xC];
    VTENT *pvt;
    char pad10[0x104];
    float scale;
    char pad118[0x28];
    float rad;
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
struct SUBDESC
{
    int n;
    float dist;
    int pad[3];
};
struct SUB
{
    int n;
    XF *pxf;
    M4 *pmatParent;
    union
    {
        uint grf;
        struct
        {
            uint kindLo : 3;
            uint kind : 5;
        };
    };
    char *pb;
    int pad14;
    void *abone;
    SKIN *pskin;
    int pad20[2];
};
struct SPH
{
    float pos[3];
    float rad;
    float gain;
    int mask;
};
struct MODEL
{
    OBJ *powner;
    float t;
    char pad8[8];
    qword posCenter;
    float rad;
    int cobj;
    OBJ **apobj;
    char pad2C[8];
    uint grfMode;
    int csub;
    SUBDESC *asubdesc;
    SUB *asub;
    SPH *asph;
    int pad48;
    int nStamp;
    union
    {
        ulong grf;
        float scale;
    };
};
struct SHD
{
    uint aw[9];
    M4 *pmatClip;
    uint ibRef;
    uint cqwRef;
};
struct G
{
    char pad[0x3EB8];
    int cview;
    VOBJ *apview[4];
    char pad3ECC[0x62C];
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
    char *pv;
};
extern "C" {
extern DMA D_0036C308;
extern G D_00475480;
extern qword D_00479360;
extern int D_004797B8;
extern qword D_003175A0;
extern const M4 D_003174C0;
void CopyAb(void *pvDst, const void *pvSrc, uint cb);
void *Memcpy(void *pvDst, const void *pvSrc, uint cb) __asm__("memcpy");
void func_0011D558(M4 *pmatDst, const M4 *pmatA, const M4 *pmatB);
void func_0011D768(M4 *pmatDst, const M4 *pmatSrc);
qword func_0011D5C8(const M4 *pmat, qword sph);
qword func_0018DC58(const M4 *pmat, qword sph);
qword func_0018E630(G *pg, qword w, int mask, qword sph);
float func_00167FE8(VOBJ *pobj, qword sph);
void func_0018E0B8(MODEL *pmodel);
int func_00237120(OBJ *pobj);
void func_0018E3A8(MODEL *pmodel, SUBDESC *pdesc, SUB *psub);
RPL *func_00209B60(void);
int func_00174FF0(int a, int i);
int func_00174FF8(int a, int b);
}
union UF { float f[4]; qword q; };
extern "C" const UF D_00321C90 = {{0.0025f, 0.0025f, 0.0025f, 0.0025f}};
#define s_qwScale D_00321C90.q
static inline float GetX(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0, %1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline float GetW(qword v) { float f; __asm__("pextuw %0,$0,%1\n\tpextuw %0,$0,%0" : "=r"(f) : "r"(v)); return f; }
struct VU_FLOATL { qword q; VU_FLOATL(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
static inline qword Pack(float x, float y, float z, float w)
{
    U u; qword q, t, s;
    __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    u.q = q;
    return u.q;
}
static inline qword Copy(qword v) { qword r; __asm__("vmax.xyzw %0,%1,%1" : "=j"(r) : "j"(v)); return r; }
static inline int IsZero(qword v)
{
    int mac;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(mac) : "j"(v));
    return (mac & 0xF) == 0xF;
}
static inline qword Mul(qword a, qword b) { qword r; __asm__("vmul.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float SqLength(qword v)
{
    qword qwSq, qwOne;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qwSq), "=&j"(qwOne) : "j"(v));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(qwSq));
    return g;
}
static inline qword Position(VOBJ *o)
{
    VTENT *e = &o->pvt[36];
    return *(qword *)((char *)e->pfn((char *)o + e->delta) + 0x30);
}
struct VECTOR
{
    float x, y, z, w;
    VECTOR() {}
} __attribute__((aligned(16)));
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
static inline void UnpackWords(uint tag, const void *pv, int cw)
{
    DMA *pdma = &D_0036C308;
    *(uint *)pdma->pb = tag;
    pdma->pb += 4;
    uint *pwDst = (uint *)pdma->pb;
    const uint *pwSrc = (const uint *)pv;
    for (int k = 0; k < cw; k++)
        *pwDst++ = *pwSrc++;
    pdma->pb += cw * 4;
}
static inline bool Near(qword a, qword s, float r) { return SqLength(Sub(a, Copy(s))) < r * r; }
// lw comes from reload (the "!r"/"m" alternative is never chosen; it keeps the float a MEM operand)
struct VU_FLOAT2 { qword q; VU_FLOAT2(const float &f) { __asm__("qmtc2.ni %1,%0" : "=j,!r"(q) : "r,m"(f)); } };
static inline qword MAdd2(qword p, qword v, VU_FLOAT2 k) { qword r; __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p), "j"(v), "j"(k.q)); return r; }
static inline void SqLengthBitsTo(int &gDst, qword v)
{
    qword qwSq, qwOne;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(qwOne), "=j"(qwSq) : "j"(v));
    __asm__("qmfc2.ni %0, %1" : "=r,m"(gDst) : "j,!r"(qwSq));
}
static inline M4 MulMat(const M4 &matA, const M4 &matB) return mat
{
    func_0011D558(&mat, &matA, &matB);
}
static inline void CopyMat(M4 &matDst, const M4 &matSrc)
{
    Memcpy(&matDst, &matSrc, sizeof(M4));
}
extern "C" void func_0018E800(MODEL *pmodel, qword qw, M4 *pmatWorld, SHD *pshd, float gFirst, float gSecond)
{
    int i;
    qword sph = func_0011D5C8(&pmodel->powner->pxf->mat, Pack(GetX(pmodel->posCenter), GetY(pmodel->posCenter), GetZ(pmodel->posCenter), GetX(VU_FLOATL(pmodel->rad).q)));
    if (pmatWorld)
        sph = func_0011D5C8(pmatWorld, sph);
    if ((pmodel->grf & 0x200000000UL) && pshd->pmatClip)
        sph = func_0018DC58(pshd->pmatClip, sph);
    U w;
    U *pw = &w;
    pw->q = func_0018E630(&D_00475480, qw, pmatWorld ? 0xFF : pmodel->powner->mask, sph);
    if (IsZero(w.q))
        return;
    U out;
    out.i[3] = 0;
    out.i[2] = 0;
    out.i[1] = 0;
    out.i[0] = 0;
    for (i = 0; i < D_00475480.cview; i++)
    {
        if (w.f[i] != 0.0f)
        {
            VOBJ *pview = D_00475480.apview[i];
            out.f[i] = -func_00167FE8(pview, Copy(sph)) * pview->scale;
        }
    }
    qword prod = Mul(out.q, s_qwScale);
    w.q = Min(Max(MAdd2(prod, s_qwScale, VU_FLOAT2(pmodel->powner->gain)), D_003175A0), w.q);
    if (IsZero(w.q))
        return;
    if (pmodel->nStamp != D_00475480.nStamp)
        func_0018E0B8(pmodel);
    for (i = 0; i < pmodel->cobj; i++)
    {
        OBJ *pobj = pmodel->apobj[i];
        if (func_00237120(pobj))
        {
            VTENT *pvte = &pobj->pvt[8];
            pvte->pfn((char *)pobj + pvte->delta);
        }
    }
    VECTOR apos[4];
    for (i = 0; i < D_00475480.cview; i++)
    {
        if (w.f[i] > 0.0f)
            *(qword *)&apos[i] = Position(D_00475480.apview[i]);
    }
    int fAlt = 0;
    if (pmodel->grf & 0x400000000UL)
        fAlt = D_004797B8 == 0;
    U wSub = *(U *)&w;
    for (int isub = 0; isub < pmodel->csub; isub++)
    {
        SUBDESC *pdesc = &pmodel->asubdesc[isub];
        SUB *psub = &pmodel->asub[isub];
        SPH *psph = &pmodel->asph[isub];
        if (psub->grf & 0x1000)
            continue;
        wSub.q = MAdd2(prod, s_qwScale, VU_FLOAT2(psph->gain));
        wSub.q = Min(Max(wSub.q, *(qword *)&D_003175A0), w.q);
        if (IsZero(wSub.q))
            break;
        V4 posSph;
        M4 matModel;
        if (psub->grf & 0x2000)
        {
            CopyAb(&matModel, psub->pb + 0x14, sizeof(M4));
            if (pmatWorld)
                matModel = MulMat(*pmatWorld, matModel);
        }
        else
        {
            M4 *pmatParent = psub->pmatParent;
            M4 mat;
            CopyMat(mat, psub->pxf->mat);
            if (pmatParent)
                CopyMat(mat, MulMat(mat, *pmatParent));
            if (pmatWorld)
                CopyMat(mat, MulMat(*pmatWorld, mat));
            matModel = mat;
        }
        CopyAb(&posSph, psph, 12);
        qword sphSub = func_0011D5C8(&matModel, Pack(GetX(*(qword *)&posSph), GetY(*(qword *)&posSph), GetZ(*(qword *)&posSph), GetX(VU_FLOATL(psph->rad).q)));
        if ((psub->grf & 7) == 2 && pshd->pmatClip)
            sphSub = func_0018DC58(pshd->pmatClip, sphSub);
        if (!psub->abone)
            wSub.q = func_0018E630(&D_00475480, wSub.q, psph->mask, sphSub);
        switch (psub->grf & 7)
        {
        case 2:
            if (!pshd->cqwRef)
                continue;
        case 3:
            wSub.q = Min(wSub.q, D_00479360);
        }
        if (IsZero(wSub.q))
            continue;
        for (int j = 0; j < D_00475480.cview; j++)
        {
            if (wSub.f[j] == 0.0f)
                continue;
            DMA *pdma = &D_0036C308;
            uchar *pbStart = pdma->pb;
            ulong *ptag;
            switch (psub->grf & 7)
            {
            case 2:
                *(ulong *)pbStart = (ulong)(int)(pshd->ibRef | 0x40000000) | ((ulong)(int)pshd->cqwRef << 32);
                pdma->pb += 0x10;
                ptag = (ulong *)pdma->pb;
                *ptag = 0x10000000;
                pdma->pb += 0x10;
                break;
            case 3:
            {
                ptag = (ulong *)pbStart;
                *ptag = 0x10000000;
                pdma->pb += 0x10;
                int fNear = 0;
                for (int k = 0; k < D_00475480.cview; k++)
                {
                    if (wSub.f[k] == 0.0f)
                        continue;
                    if (Near(*(qword *)&apos[k], sphSub, GetW(sphSub) + D_00475480.apview[k]->rad))
                    {
                        fNear = 1;
                        break;
                    }
                }
                UnpackWords(0x6001C012, &fNear, 1);
                break;
            }
            default:
                if (psub->grf & 0x300)
                {
                    *(ulong *)D_0036C308.pb = (ulong)(int)(pshd->aw[5] | 0x40000000) | ((ulong)(int)pshd->aw[6] << 32);
                    D_0036C308.pb += 0x10;
                }
                ptag = (ulong *)D_0036C308.pb;
                *ptag = 0x10000000;
                D_0036C308.pb += 0x10;
                break;
            }
            if (psub->abone)
            {
                const M4 *pmat = pmatWorld;
                if (!pmat)
                    pmat = &D_003174C0;
                UnpackQws<0x6C04C000>(pmat, 16);
            }
            else
            {
                UnpackQws<0x6C04C000>(&matModel, 16);
            }
            V4 vecParams;
            vecParams.x = gFirst * wSub.f[j];
            vecParams.y = gSecond * wSub.f[j];
            vecParams.z = pmodel->scale;
            *(uint *)&vecParams.w = (psub->grf & 0x400) ? pmodel->grfMode : 0;
            UnpackQws<0x6C01C008>(&vecParams, 4);
            if (psub->abone)
                func_0018E3A8(pmodel, pdesc, psub);
            SKIN *pskin = psub->pskin;
            if (pskin)
            {
                OBJ *powner = pskin->powner;
                VTENT *pvte = &powner->pvt[53];
                pvte->pfn((char *)powner + pvte->delta, pskin);
                M4 matInv;
                func_0011D768(&matInv, &matModel);
                uint ib = pskin->ib;
                for (int imat = 0; imat < pskin->cmat; imat++)
                {
                    if (pskin->amatFirst)
                    {
                        M4 mat;
                        func_0011D558(&mat, &matInv, &pskin->amatFirst[imat]);
                        UnpackQws(ib | 0x6C04C000, &mat, 16);
                        ib += 4;
                    }
                    if (pskin->amatSecond)
                    {
                        UnpackQws(ib | 0x6C04C000, &pskin->amatSecond[imat], 16);
                        ib += 4;
                    }
                }
            }
            {
                DMA *pdma = &D_0036C308;
                for (uchar *pbPad = pdma->pb; (uint)pbPad & 0xF; pbPad = pdma->pb)
                {
                    *(uint *)pbPad = 0;
                    pdma->pb += 4;
                }
            }
            *(uint *)ptag |= ((int)(D_0036C308.pb - (uchar *)ptag) >> 4) - 1;
            *(ulong *)D_0036C308.pb = 0x60000000;
            D_0036C308.pb += 0x10;
            for (int k = j; k < D_00475480.cview; k++)
            {
                if (j < k)
                {
                    if (wSub.f[k] != wSub.f[j])
                        continue;
                    wSub.f[k] = 0.0f;
                }
                RPL *prpl = func_00209B60();
                int kind = psub->kind;
                int layer = 5;
                switch (psub->kind)
                {
                case 2:
                    if (vecParams.x != 1.0f)
                        kind = 4;
                    if (fAlt)
                        layer = 10;
                    break;
                case 3:
                    if (vecParams.x != 1.0f)
                        kind = 5;
                    if (fAlt)
                        layer = 10;
                    break;
                case 4:
                case 5:
                case 8:
                case 9:
                    if (fAlt)
                        layer = 10;
                    break;
                case 0:
                    layer = 1;
                    break;
                }
                prpl->kind = func_00174FF8(kind, func_00174FF0(layer, k));
                if (psub->grf & 0x800)
                    prpl->dist = pdesc->dist;
                else
                    SqLengthBitsTo(*(int *)&prpl->dist, Sub(Copy(sphSub), *(qword *)&apos[k]));
                prpl->pb = pbStart;
                prpl->pv = psub->pb;
            }
        }
    }
}

struct T44 { char pad[0x44]; };
struct KEY { int n; T44 *p4; int n8; T44 *pC; int n10; };
extern "C" int func_0018F650(const KEY *a, const KEY *b)
{
    int d = a->p4 - b->p4;
    if (d)
        return d;
    d = a->n8 - b->n8;
    if (d)
        return d;
    d = a->pC - b->pC;
    if (d)
        return d;
    return a->n10 - b->n10;
}

// next rodata literal of this unit
extern "C" const float D_00321CC8 = 3.4028234663852886e+38f;
