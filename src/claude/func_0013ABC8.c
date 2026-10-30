// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct M { short delta, pad; int (*fn)(void *, int); };
struct VT { char pad[0x318]; struct M m318; struct M m320; };
struct O { char pad[0xC]; struct VT *vt; };
struct B { float g0; void *p4; char pad[0xC - 8]; float gC; void *p10; };
struct C { char pad[0x84]; void *p84; void *p88; struct B b8C; char pad1[0xA4 - 0xA0]; void *pA4; void *pA8; struct B bAC;
    char pad2[0xC4 - 0xC0]; void *pC4; };
struct D { char pad[0x1C]; float g1C; };
struct P { struct O *po; int st; float g8; struct C *pc; int x10; float g14; struct D *pd; char pad[0x28 - 0x1C]; int x28, x2C, x30, x34; };
void func_00148938(void *p);
/* float parameters placed before pv: same EE register assignment, gives the target's argument setup order */
void func_00137588(void *p, struct O *po, int n, float g, float h, void *pv);
static inline int M318(struct O *po, int n) { struct M *m = &po->vt->m318; return m->fn((char *)po + m->delta, n); }
static inline int M320(struct O *po) { struct M *m = &po->vt->m320; return ((int (*)(void *))m->fn)((char *)po + m->delta); }
void func_0013ABC8(struct P *p, int st)
{
    float g;
    void *pv;
    struct B *pb;
    void *pr;
    if (st == p->st)
        return;
    g = 0.0f;
    switch (p->st) {
    case -1:
        p->x28 = 0;
        p->x2C = 0;
        p->x30 = 0;
        p->x34 = 0;
        break;
    case 0:
    case 1:
        if ((unsigned)st < 2)
            g = p->pd->g1C;
        break;
    }
    p->st = st;
    pv = 0;
    pb = 0;
    pr = 0;
    p->g8 = g_clock.t;
    switch (st) {
    case 0:
        M318(p->po, 9);
        if (p->pc->p88) {
            pv = p->pc->p88;
            pb = &p->pc->b8C;
            pr = pv;
        } else
            pv = p->pc->p84;
        break;
    case 1:
        if (p->pc->pA8) {
            pv = p->pc->pA8;
            pb = &p->pc->bAC;
            pr = pv;
        } else
            pv = p->pc->pA4;
        break;
    case 2:
        M318(p->po, 9);
        pv = p->pc->pC4;
        break;
    case -1:
        if (M320(p->po) == 9)
            M318(p->po, 0);
        p->pc = 0;
        p->x10 = 0;
        break;
    case 3:
        return;
    }
    if (pr) {
        if (!pb->p10)
            pv = pb->p4;
        else if (!pb->p4)
            pv = pb->p10;
        else {
            pb->g0 = 1.0f - p->g14;
            pb->gC = p->g14;
            func_00148938(pr);
        }
    }
    func_00137588(pv, p->po, 3, g, 1.0f, &p->pd);
}
