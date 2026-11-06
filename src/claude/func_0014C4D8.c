// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "../../include/deferred_callback_api.h"
typedef int qword __attribute__((mode(TI)));
struct P;
struct HALF { int x0; int x4; struct P *p8; int xC; char pad[0x40 - 0x10]; };
struct O { union { struct HALF ah[2]; struct { int pad[4]; qword q10; } s; } u; char pad[0xAC - 0x80]; struct O *pNext; };
struct NODE { struct O *po; struct NODE *pNext; };
struct W { char pad[0x64]; struct NODE *pHead; };
struct D { char pad[0x60]; qword q60; };
struct VTE { short d; short pad; qword (*pfn)(void *); };
struct VT { char pad[0x130]; struct VTE e130; };
struct P {
    char pad[0xC]; struct VT *pvt; char pad1[0xD4 - 0x10]; struct D *pD4; int pad2; struct W *pw; char pad3[0x130 - 0xE0];
    int x130; char pad4[0x150 - 0x134]; int x150; char pad5[0x1C8 - 0x154]; int x1C8; int x1CC;
};
extern qword D_00317530;
extern unsigned char D_00475480[];
extern const struct DEFERRED_PMF D_00320268; /* member pointer in the original unit's rodata row 0x320260 */
extern const float D_00320270; /* FLT_MAX */
void func_0023E068(struct P *p);
int func_0014C778(struct P *p, int n);
void func_0014C9B8(struct P *p, qword a, qword b, int n);
void func_0014CB98(struct P *p, float g);

static __inline__ float Dist(qword a, qword b)
{
    qword d, t, one;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(t), "=j"(one) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(t) : "j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
static __inline__ void SafeNormalize(qword *pv, qword *pvDefault)
{
    register qword v __asm__("vf3") = *pv; /* register pin: the target keeps the vector in vf3 */
    qword t, t2, one, d;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(t), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(t2) : "j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t2));
    d = *pvDefault;
    __asm__("" : "+r"(d));
    if (g < 0.0001f)
        *pv = d;
    else {
        qword r;
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(t2), "j"(v));
        *pv = r;
    }
}

void func_0014C4D8(struct P *p)
{
    qword pos;
    float dBest;
    struct O *pBest;
    struct NODE *pn;
    func_0023E068(p);
    switch (p->x130) {
    case 0:
        if (p->x150)
            return;
        break;
    case 1:
        if (!p->x1C8 || p->x1CC)
            return;
        break;
    }
    pBest = 0;
    pos = p->pD4->q60;
    dBest = D_00320270;
    for (pn = p->pw->pHead; pn; pn = pn->pNext) {
        struct O *po;
        for (po = pn->po; po; po = po->pNext) {
            float d = Dist(po->u.s.q10, pos);
            int f, st;
            if (dBest <= d)
                continue;
            st = p->x130;
            f = 0;
            switch (st) {
            case 0:
                f = 1;
                break;
            case 1: {
                int k = p != po->u.ah[0].p8;
                int r = func_0014C778(p, po->u.ah[st - k].xC);
                f = 0;
                if (r)
                    f = st;
                break;
            }
            }
            if (f) {
                dBest = d;
                pBest = po;
            }
        }
    }
    if (!pBest)
        return;
    switch (p->x130) {
    case 0: {
        qword v = pBest->u.s.q10;
        qword dir = p->pvt->e130.pfn((char *)p + p->pvt->e130.d);
        int k;
        SafeNormalize(&dir, &D_00317530);
        k = p == pBest->u.ah[0].p8;
        func_0014C9B8(p, v, dir, ((struct HALF *)((int)pBest + (k << 6)))->xC);
        func_0014CB98(p, 0.0f);
        break;
    }
    case 1:
        {
            int k = p != pBest->u.ah[0].p8;
            func_0015DC68(D_00475480, p, D_00320268, (void *)pBest->u.ah[1 - k].xC);
        }
        break;
    }
}
