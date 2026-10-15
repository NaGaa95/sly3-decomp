// Reconstructed using the corresponding Sly 2 source and checked against Sly 3.
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

extern "C" void func_00182D60(DMAS *pdmas, QW *pqwStart, QW *pqwEnd)
{
    pdmas->AddDmaRefs((uint)((char *)pqwEnd - (char *)pqwStart + 15) >> 4, pqwStart);
}
