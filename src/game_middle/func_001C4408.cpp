// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Sweep test from an actor's position (offset by D_00317560) over its height range; returns the hit position.
// Port of Sly 2 src/hand/func_001A2788.cpp.
#include "../P2/state_position_ops.h"

typedef union { qword q; float f[4]; } U;
inline qword PackedSum(qword left, qword right) { qword result; asm("vadd.xyzw %0,%1,%2" : "=j"(result) : "j"(left), "j"(right)); return result; }
struct MSG { int cb; int nKind; };
struct HIT { qword pos; char pad[0x5F0]; };
struct VEntry { short d; short pad; unsigned char *(*pfn)(void *); };
struct O { char pad0[0xC]; VEntry *vt; char pad10[0x1170 - 0x10]; float x1170; float x1174; };
struct L { char pad[0xD0]; int xD0; };
extern "C" {
extern qword D_00317560;
void func_001D2770(void *p);
void func_001D2798(void *p, int n);
void *func_001D25B0(MSG *pmsg);
int func_002414D8(L *pl, void *pfn, int n, void *pv);
int func_00165130(qword a, qword b, int n, void *pv, int c, HIT *phit);
void func_00281850(void);
int func_001C4408(O *po, L *pl, qword *pv);
}
int func_001C4408(O *po, L *pl, qword *pv)
{
    U off, b, a;
    HIT hit;
    int frame[4];
    MSG msg;
    off.q = D_00317560;
    {
        qword p = *(qword *)(po->vt[36].pfn((unsigned char *)po + po->vt[36].d) + 0x30);
        qword d = PackedDifference(p, off.q);
        a.q = d;
        b.q = d;
    }
    a.f[2] += po->x1174;
    b.f[2] += po->x1170;
    func_001D2770(frame);
    MSG *pmsg = &msg;
    pmsg->cb = pl->xD0 * 4;
    pmsg->nKind = 0x10;
    void *pbuf = func_001D25B0(pmsg);
    int n = func_002414D8(pl, (void *)func_00281850, 0, pbuf);
    if (!func_00165130(a.q, b.q, n, pbuf, 0x10, &hit)) {
        func_001D2798(frame, 2);
        return 0;
    }
    *pv = PackedSum(hit.pos, off.q);
    func_001D2798(frame, 2);
    return 1;
}
