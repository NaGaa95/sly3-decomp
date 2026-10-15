// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
#ifndef VIFS_H
#define VIFS_H
/* DMA chain builder. vtable _vt$4DMAS @0x2CE488, vptr at +0x18. */
#ifndef DMAS_H
#define DMAS_H
#ifndef QW_H
#define QW_H
/* Sly 2 decomp: basic types (shared with the Sly 1 decomp conventions). */
#ifndef COMMON_H
#define COMMON_H
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;     /* 64-bit on the EE */
typedef int sint;
#ifndef NULL
#define NULL 0
#endif
#define STRUCT_OFFSET(p, off, type) (*(type *)((byte *)(p) + (off)))
#endif

/* 128-bit quadword (DMA tags, GIF/VIF packets) */
union QW {
    ulong aul[2];
    long al[2];
    uint aui[4];
    uint aun[4];
    int an[4];
    float ag[4];
} __attribute__((aligned(16)));
#endif

struct HEAP;
struct ALLOCREQ { int cb; int cbAlign; };       /* passed by value to the allocator */

class DMAS
{
public:
    /* 0x00 */ uchar *m_pbMax;
    /* 0x04 */ uchar *m_ab;
    /* 0x08 */ QW *m_pqwCnt;
    /* 0x0c */ uchar *m_pb;
    /* 0x10 */ int m_fPad;
    /* 0x14 */ int m_fEndPrim;
    /* 0x18    vptr */

    DMAS();
    void Clear();
    void Reset();
    void AllocSw(int cqw);
    void AllocStatic(int cqw, QW *aqw);
    void Detach(int *pcqw, QW **paqw);
    void DetachCopySw(int *pcqw, QW **paqw, QW **paqwCopy);
    void DetachCopySw(HEAP *pheap, int *pcqw, QW **paqw, QW **paqwCopy);
    void Flush();
    void AddDmaCnt();
    void AddDmaRefs(int cqw, QW *aqw);
    void AddDmaCall(QW *aqw);
    void AddDmaRet();
    void AddDmaBulk(int cqw, QW *aqw);
    void AddDmaEnd();
    void EndDmaCnt();

    virtual void EndPrim(int n);
};

extern HEAP g_heapSw;
void *PvAllocSlot(ALLOCREQ *preq);                       /* 0x1AE318 */
void *PvAllocCopy(HEAP *pheap, int cb, void *pv, int n); /* 0x116970 */
void CopyAqw(void *pvDst, void *pvSrc, int cqw);        /* 0x1AE528 */
#endif

enum UPK
{
    UPK_Nil = -1, UPK_S32 = 0, UPK_S16 = 1, UPK_S8 = 2,
    UPK_V2_32 = 4, UPK_V2_16 = 5, UPK_V2_8 = 6,
    UPK_V3_32 = 8, UPK_V3_16 = 9, UPK_V3_8 = 10,
    UPK_V4_32 = 12, UPK_V4_16 = 13, UPK_V4_8 = 14, UPK_V4_5 = 15, UPK_Max = 16
};

class GIFS;
class CBinaryInputStream;

/* VIF packet builder on top of DMAS */
class VIFS : public DMAS
{
public:
    /* 0x1c */ uint m_unMask;
    /* 0x20 */ int m_fCheckCnt;

    VIFS();
    void Align(int iun);
    void AddVifBaseOffset(int iqwBase, int diqwOffset);
    void AddVifMscal(void *pv);
    void AddVifFlush();
    void AddVifFlusha();
    void AddVifStcycl(int wl, int cl);
    void AddVifStrow(QW *pqw);
    void AddVifStmask(uint unMask);
    int CbUnpackSetup(UPK upk, int c, int iqw);
    void UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun);
    void AddVifUnpack(UPK upk, int c, void *pvSrc, int iqw);
    void AddVifUnpack(UPK upk, int c, CBinaryInputStream *pbis, int iqw);
    void AddVifUnpackRefs(UPK upk, int c, void *pvSrc, int iqw, void ***pppv);
    void AddVifDirect(int cqw, QW *aqw, int fInt);
    void AddVifDirectRefs(int cqw, QW *aqw, int fInt);
    void AddVifGifs(GIFS *pgifs);
};

static inline void AddDmaInt(DMAS *pdmas, int n)
{
    uchar *pb = pdmas->m_pb;
    pdmas->m_pb = pb + 4;
    *(int *)pb = n;
}
#endif

#ifndef GIFS_H
#define GIFS_H
/* DMA chain builder. vtable _vt$4DMAS @0x2CE488, vptr at +0x18. */
#ifndef DMAS_H
#define DMAS_H
#ifndef QW_H
#define QW_H
/* Sly 2 decomp: basic types (shared with the Sly 1 decomp conventions). */
#ifndef COMMON_H
#define COMMON_H
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;     /* 64-bit on the EE */
typedef int sint;
#ifndef NULL
#define NULL 0
#endif
#define STRUCT_OFFSET(p, off, type) (*(type *)((byte *)(p) + (off)))
#endif

/* 128-bit quadword (DMA tags, GIF/VIF packets) */
union QW {
    ulong aul[2];
    long al[2];
    uint aui[4];
    uint aun[4];
    int an[4];
    float ag[4];
} __attribute__((aligned(16)));
#endif

struct HEAP;
struct ALLOCREQ { int cb; int cbAlign; };       /* passed by value to the allocator */

class DMAS
{
public:
    /* 0x00 */ uchar *m_pbMax;
    /* 0x04 */ uchar *m_ab;
    /* 0x08 */ QW *m_pqwCnt;
    /* 0x0c */ uchar *m_pb;
    /* 0x10 */ int m_fPad;
    /* 0x14 */ int m_fEndPrim;
    /* 0x18    vptr */

    DMAS();
    void Clear();
    void Reset();
    void AllocSw(int cqw);
    void AllocStatic(int cqw, QW *aqw);
    void Detach(int *pcqw, QW **paqw);
    void DetachCopySw(int *pcqw, QW **paqw, QW **paqwCopy);
    void DetachCopySw(HEAP *pheap, int *pcqw, QW **paqw, QW **paqwCopy);
    void Flush();
    void AddDmaCnt();
    void AddDmaRefs(int cqw, QW *aqw);
    void AddDmaCall(QW *aqw);
    void AddDmaRet();
    void AddDmaBulk(int cqw, QW *aqw);
    void AddDmaEnd();
    void EndDmaCnt();

    virtual void EndPrim(int n);
};

extern HEAP g_heapSw;
void *PvAllocSlot(ALLOCREQ *preq);                       /* 0x1AE318 */
void *PvAllocCopy(HEAP *pheap, int cb, void *pv, int n); /* 0x116970 */
void CopyAqw(void *pvDst, void *pvSrc, int cqw);        /* 0x1AE528 */
#endif

/* GIF packet builder */
class GIFS : public DMAS
{
public:
    /* 0x1c */ QW *m_pqwPrim;
    /* 0x20 */ uint m_creg;
    /* 0x24 */ uint m_cregAll;

    GIFS();
    void AddPrimEnd();
    virtual void EndPrim(int fEOP);
    void CheckReg(int fExpectPack, int regExpect);
    void AddPrimBulk(int prim, int c, int creg, ulong regs, QW **paqwBulk);
    void AddPrimPack(int prim, int creg, ulong regs);
    void AddGifTag(int prim, int c, int creg, ulong regs, uint fEOP);
    void PackRGBA(uint rgba);
    void PackUV(int u, int v);
    void PackSTQ(float s, float t, float q);
    void PackXYZ(int x, int y, int z);
    void PackXYZF(int x, int y, int z, int fog);
    void PackAD(long a, long d);
    void AddPrimList(int creg, ulong regs);
    void ListRGBAQ(uint rgba, float q);
    void ListUV(int u, int v);
    void ListXYZ(int x, int y, int z);
    void ListXYZF(int x, int y, int z, int fog);
    void AddImage(int cqw);
};
#endif

extern "C" void func_00182D60(VIFS *pvifs, void *pvStart, void *pvEnd);
extern char D_002C4BF0[];
extern char D_002C8C08[];
extern "C" void func_00182D88(VIFS *pvifs, int *pcqw, QW **paqw)
{
    QW aqw[8];
    GIFS gifs;
    gifs.AllocStatic(8, aqw);
    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(0x61, 0);
    gifs.AddPrimEnd();
    pvifs->AddDmaCnt();
    pvifs->AddVifFlush();
    pvifs->AddVifGifs(&gifs);
    pvifs->EndDmaCnt();
    func_00182D60(pvifs, D_002C4BF0, D_002C8C08);
    pvifs->AddDmaEnd();
    pvifs->Detach(pcqw, paqw);
}
