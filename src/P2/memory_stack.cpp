// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "dmas.h"

extern "C" void func_001D2468(int cb);
extern "C" void *memset(void *pv, int b, unsigned int cb);
extern "C" void func_00271BB8(void *p);
extern "C" void func_00271C10(void *p);
extern "C" unsigned char *g_pbGlobalBase;
extern "C" unsigned char *g_pbGlobal;
extern "C" unsigned char *g_pbSlot;
extern "C" char g_stackGuard[12];
extern "C" int g_cStack;
extern "C" unsigned char *g_apbStack[];

extern "C" void *func_001D2470(ALLOCREQ *preq)
{
    unsigned char *pb = 0;
    if (preq->cb)
    {
        func_001D2468(preq->cb);
        int ip = (int)g_pbGlobal - 1;
        int align = preq->cbAlign;
        pb = (unsigned char *)((ip + align) & -align);
        g_pbGlobal = pb + preq->cb;
    }
    return pb;
}

void *PvAllocSlot(ALLOCREQ *preq)
{
    unsigned char *pb = 0;
    if (preq->cb)
    {
        func_001D2468(preq->cb);
        pb = (unsigned char *)(((int)g_pbSlot - preq->cb) & -preq->cbAlign);
        g_pbSlot = pb;
    }
    return pb;
}

extern "C" void *func_001D2538(ALLOCREQ *preq)
{
    ALLOCREQ req = *preq;
    void *pv = func_001D2470(&req);
    if (pv)
        memset(pv, 0, preq->cb);
    return pv;
}

extern "C" void func_001D2598()
{
    g_pbGlobal = g_pbGlobalBase;
}

extern "C" void *func_001D2670(ALLOCREQ *preq)
{
    ALLOCREQ req = *preq;
    void *pv = PvAllocSlot(&req);
    if (pv)
        memset(pv, 0, preq->cb);
    return pv;
}

extern "C" void func_001D26D0()
{
    func_00271BB8(g_stackGuard);
    g_apbStack[++g_cStack] = g_pbSlot;
}

extern "C" void func_001D2720()
{
    g_pbSlot = g_apbStack[g_cStack--];
    func_00271C10(g_stackGuard);
}
