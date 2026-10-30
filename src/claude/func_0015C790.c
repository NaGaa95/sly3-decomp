// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
typedef int qword __attribute__((mode(TI)));
struct P;
struct HALF { int x0; int x4; int x8; struct P *pOwner; qword q10; char pad[0x40 - 0x20]; };
struct O { struct HALF ah[2]; qword q80; char pad[0x9C - 0x90]; int x9C; char padA0[0xAC - 0xA0]; struct O *pNext; qword qB0; };
struct NODE { struct O *po; struct NODE *pNext; };
struct W { char pad[0x60]; int x60; struct NODE *pHead; };
struct STATE { int state; float t; float tMax; };
struct VTE { short d; short pad; int (*pfn)(void *, int, qword, qword, int); };
struct VT { char pad[0x280]; struct VTE e280; };
struct P {
    char pad[0xC]; struct VT *pvt; char pad1[0xDC - 0x10]; struct W *pw; char pad2[0x130 - 0xE0]; struct STATE st;
    char pad3[0x144 - 0x13C]; int x144; char pad4[0x220 - 0x148]; int x220; char pad5[0x240 - 0x224]; qword q240;
};
extern struct CLOCK { float t; } g_clock;
extern unsigned char D_00475480[];
void func_0015CAD0(void *, void *);
static const struct DEFERRED_PMF s_pmf = { 0, -1, { func_0015CAD0 } };
void func_0023C660(struct P *p);
void func_0015C178(struct STATE *pst, int state);

void func_0015C790(struct P *p)
{
    int stNext, st4, st; /* st4 is read uninitialized in case 4, as in the target (movn from the po register) */
    struct NODE *pn;
    struct O *po;
    func_0023C660(p);
    st = p->st.state;
    switch (st) {
    case 2:
        if (p->st.tMax >= 0.0f && g_clock.t - p->st.t > p->st.tMax)
            func_0015C178(&p->st, 4);
        return;
    case 4:
        func_0015C178(&p->st, p->x220 ? st4 : 1);
        return;
    found:
        p->q240 = po->qB0;
        func_0015DCD0(D_00475480, p, s_pmf, 0);
        stNext = p->st.state;
        break;
    case 0:
    case 1:
        stNext = st;
        if (!p->x220) {
            if (!p->pw)
                break;
            pn = p->pw->pHead;
            stNext = 0;
            for (; pn; pn = pn->pNext) {
                for (po = pn->po; po; po = po->pNext) {
                    if (po->x9C != 10) {
                        int k = p->pw->x60 != po->ah[0].x8;
                        struct HALF *ph = &po->ah[k];
                        int id = po->ah[1 - k].x8;
                        if (ph->pOwner == p) {
                            struct VTE *e = &p->pvt->e280;
                            if (e->pfn((char *)p + e->d, ph->x0, ph->q10, po->q80, id)) {
                                p->x144 = id;
                                goto found;
                            }
                        }
                    }
                }
            }
        }
        break;
    case 3:
    default:
        return;
    }
    func_0015C178(&p->st, stNext);
}

/* Next .rodata item of the original unit (the member pointer read by func_0015CFD8); it follows the jump table. */
void func_0015D288(void *, void *);
const struct DEFERRED_PMF D_00320868 = { 0, -1, { func_0015D288 } };
