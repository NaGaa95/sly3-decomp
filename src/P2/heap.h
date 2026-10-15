/* Sly 3 allocator interface. Explicit alignment adds the virtual slot at 0x10.
 * Names and fields use the Sly 2 decomp conventions where identities are recovered. */
#ifndef HEAP_H
#define HEAP_H
#include "common.h"

class HEAP
{
public:
    HEAP();
    virtual void *PvAlloc(int cb, int n) = 0;                 /* slot 1 */
    virtual void *PvAllocAlign(int cb, int cbAlign, int n) = 0;/* slot 2 */
    virtual void *PvRealloc(void *pv, int cb, int n) = 0;     /* slot 3 */
    virtual void Free(void *pv) = 0;                          /* slot 4 */
};

struct ALLOCREQ { int cb; int cbAlign; };

class CGlobalHeap : public HEAP
{
public:
    /* 0x04 */ int m_n;
    CGlobalHeap(int n);
    virtual void *PvAllocAlign(int cb, int cbAlign, int n);
    virtual void *PvAlloc(int cb, int n);
    virtual void *PvRealloc(void *pv, int cb, int n);
    virtual void Free(void *pv);
};

class CSwHeap : public HEAP
{
public:
    virtual void *PvAllocAlign(int cb, int cbAlign, int n);
    virtual void *PvAlloc(int cb, int n);
    virtual void *PvRealloc(void *pv, int cb, int n);
    virtual void Free(void *pv);
};

class CLinearHeap : public HEAP
{
public:
    /* 0x04 */ int m_cbMax;
    /* 0x08 */ byte *m_pbBase;
    /* 0x0c */ int m_ib;

    CLinearHeap(int cbMax, byte *pbBase);
    CLinearHeap();
    void Init(int cbMax, byte *pbBase);
    virtual void *PvAlloc(int cb, int n);
    virtual void *PvAllocAlign(int cb, int cbAlign, int n);
    virtual void *PvRealloc(void *pv, int cb, int n);
    virtual void Free(void *pv);
};

/* Growable array of m_cb-byte elements allocated from m_pheap */
class CDynArray
{
public:
    /* 0x00 */ void *m_pv;
    /* 0x04 */ int m_c;
    /* 0x08 */ int m_cMax;
    /* 0x0c */ int m_cb;
    /* 0x10 */ int m_unk10;
    /* 0x14 */ HEAP *m_pheap;

    void Free();
    void Reserve(int c);
    void Append(void *pv, int c);
};

extern "C" void CopyAb(void *pvDst, void *pvSrc, uint cb);
extern "C" void *memset(void *pv, int b, uint cb);
extern "C" int strlen(const char *sz);
void *PvAllocCopy(HEAP *pheap, int cb, void *pv, int n);
void *PvAllocClear(HEAP *pheap, int cb, int n);
void *PvAllocClear(HEAP *pheap, int cb, int cbAlign, int n);
int CchzWide(const unsigned short *pchz);
unsigned short *PchzAllocCopy(HEAP *pheap, unsigned short *pchz, int n);
#endif
