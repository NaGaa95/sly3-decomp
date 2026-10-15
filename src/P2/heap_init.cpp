// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "heap.h"

inline CGlobalHeap::CGlobalHeap(int n) : m_n(n) {}

// Recovered fixed-pool state prefix; backing objects retain their original storage.

struct POOLSTATE
{
    int cb;
    int c;
    int cbAlign;
    void *pv;
    int cAlloc;
    void *pvBlock;
    void *PvAlloc();
    void Reset();
    void Free(void *p);
    void WarmUp();
    POOLSTATE(int cb, int c, int cbAlign);
};

extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" POOLSTATE D_004D2AD8, D_004D2BB0, D_004D2C88;
extern "C" POOLSTATE D_004D2D60, D_004D2E38, D_004D2F10;

POOLSTATE::POOLSTATE(int cb, int c, int cbAlign)
{
    this->cb = cb;
    this->c = c;
    this->cbAlign = cbAlign;
    pv = 0;
}

inline void *operator new(unsigned int cb, void *pv) { return pv; }

CGlobalHeap g_heapSw(-1);

template<int cb, int c, int *pcRef, POOLSTATE *pstate>
class CPoolRef
{
public:
    CPoolRef()
    {
        if (++*pcRef == 1)
            new (pstate) POOLSTATE(cb, c, 16);
    }
};

CPoolRef<16, 2048, &D_0036AE78, &D_004D2AD8> g_ref16;
CPoolRef<24, 1024, &D_0036AE7C, &D_004D2BB0> g_ref24;
CPoolRef<24, 256, &D_0036AE80, &D_004D2C88> g_ref24Small;
CPoolRef<28, 1024, &D_0036AE84, &D_004D2D60> g_ref28;
CPoolRef<12, 256, &D_0036AE88, &D_004D2E38> g_ref12;
CPoolRef<24, 256, &D_0036AE8C, &D_004D2F10> g_ref24Other;

extern "C" void *func_001D2470(ALLOCREQ *preq);
extern "C" void *memset(void *pv, int b, unsigned int cb);

void *POOLSTATE::PvAlloc()
{
    if (pv == 0)
    {
        ALLOCREQ req;
        req.cb = c * cb;
        req.cbAlign = cbAlign;
        unsigned char *ab = (unsigned char *)func_001D2470(&req);
        int i;
        for (i = 1; i < c; i++)
            *(void **)(ab + (i - 1) * cb) = ab + i * cb;
        *(void **)(ab + (i - 1) * cb) = 0;
        pv = ab;
        pvBlock = ab;
    }
    void *p = pv;
    pv = *(void **)p;
    memset(p, 0, cb);
    cAlloc++;
    return p;
}

void POOLSTATE::Reset()
{
    pvBlock = 0;
    cAlloc = 0;
    pv = 0;
}

void POOLSTATE::Free(void *p)
{
    cAlloc--;
    *(void **)p = pv;
    pv = p;
}

void POOLSTATE::WarmUp()
{
    Free(PvAlloc());
}
