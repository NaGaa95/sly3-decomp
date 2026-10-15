// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "heap.h"
#include "dmas.h"

extern "C" void *func_001D2470(ALLOCREQ *preq);

void *CGlobalHeap::PvAllocAlign(int cb, int cbAlign, int n)
{
    ALLOCREQ req;
    req.cb = cb;
    req.cbAlign = cbAlign;
    return func_001D2470(&req);
}

void *CGlobalHeap::PvRealloc(void *pv, int cb, int n)
{
    return PvAlloc(cb, m_n == -1 ? n : m_n);
}

void CGlobalHeap::Free(void *pv) {}

void *CSwHeap::PvAllocAlign(int cb, int cbAlign, int n)
{
    ALLOCREQ req;
    req.cb = cb;
    req.cbAlign = cbAlign;
    return PvAllocSlot(&req);
}

void *CSwHeap::PvRealloc(void *pv, int cb, int n)
{
    return PvAlloc(cb, n);
}

void CSwHeap::Free(void *pv) {}
