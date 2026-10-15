// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "heap.h"
extern "C" void *memcpy(void *pvDst, const void *pvSrc, uint cb);

void *PvAllocClear(HEAP *pheap, int cb, int n)
{
    void *pv = pheap->PvAlloc(cb, n);
    memset(pv, 0, cb);
    return pv;
}

void *PvAllocClear(HEAP *pheap, int cb, int cbAlign, int n)
{
    void *pv = pheap->PvAllocAlign(cb, cbAlign, n);
    memset(pv, 0, cb);
    return pv;
}

void *PvAllocCopy(HEAP *pheap, int cb, void *pv, int n)
{
    void *pvNew = pheap->PvAlloc(cb, n);
    CopyAb(pvNew, pv, cb);
    return pvNew;
}

unsigned short *PchzAllocCopy(HEAP *pheap, unsigned short *pchz, int n)
{
    return (unsigned short *)PvAllocCopy(pheap, (CchzWide(pchz) + 1) * 2, pchz, n);
}

HEAP::HEAP() {}

CLinearHeap::CLinearHeap(int cbMax, byte *pbBase)
{
    Init(cbMax, pbBase);
}

CLinearHeap::CLinearHeap()
{
    Init(0, NULL);
}

void CLinearHeap::Init(int cbMax, byte *pbBase)
{
    m_cbMax = cbMax;
    m_pbBase = pbBase;
    m_ib = 0;
}

void *CLinearHeap::PvAlloc(int cb, int n)
{
    return PvAllocAlign(cb, 16, n);
}

void *CLinearHeap::PvAllocAlign(int cb, int cbAlign, int n)
{
    if (cb == 0)
        return NULL;
    byte *pb = (byte *)(((int)m_pbBase + m_ib + (cbAlign - 1)) & -cbAlign);
    int ibNew = pb + cb - m_pbBase;
    m_ib = ibNew;
    if (m_cbMax < ibNew)
        return NULL;
    return pb;
}

void *CLinearHeap::PvRealloc(void *pv, int cb, int n)
{
    return PvAlloc(cb, n);
}

void CLinearHeap::Free(void *pv) {}

void CDynArray::Free()
{
    m_pheap->Free(m_pv);
    m_pv = NULL;
    m_cMax = 0;
    m_c = 0;
}

void CDynArray::Reserve(int c)
{
    if (m_cMax < c)
    {
        int cMax;
        if (c < 0x200)
        {
            cMax = m_cMax ? m_cMax : 8;
            while (cMax < c)
                cMax *= 2;
        }
        else
        {
            cMax = (c + 0x3FF) & ~0x3FF;
        }
        m_pv = m_pheap->PvRealloc(m_pv, cMax * m_cb, 4);
        m_cMax = cMax;
    }
}

void CDynArray::Append(void *pv, int c)
{
    Reserve(m_c + c);
    memcpy((byte *)m_pv + m_cb * m_c, pv, m_cb * c);
    m_c += c;
}
