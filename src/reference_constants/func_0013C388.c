// Reference algorithm: src/hand/func_00133A38.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void *pfn; };
struct LO { int pad[3]; struct VTE *vt; };
struct L { void *pv; struct L *pnext; struct L *pother; struct LO *po; int f; };
struct X { char pad[0x60]; struct LO *plo; struct L *pl; };
struct P { char pad[0x4494]; char aCF8[4]; };
int func_0013C658(struct P *, struct X *, struct X *);
struct L *func_0013C5B8(struct P *, struct X *, struct X *);
struct L *func_0013C608(struct P *, struct X *, struct X *);
void func_001CBAA0(struct P *, void *);
void func_0023E228(struct LO *);
void func_0011E1F0(void *, struct L *);
#define VCALL(po, n, T) ((T)(po)->vt[n].pfn)((char *)(po) + (po)->vt[n].d
void func_0013C388(struct P *p, struct X *px1, struct X *px2, int k)
{
    struct L *pl;
    struct L *plT;
    int f;
    for (plT = px1->pl; plT; plT = plT->pnext) {
        if (plT->po == px2->plo)
            break;
    }
    switch (k) {
    case 1:
        f = 1;
        break;
    case 2:
        f = 0;
        break;
    case 0:
        f = 0;
        if (plT)
            f = plT->f;
        break;
    }
    pl = plT;
    if (f || func_0013C658(p, px1, px2)) {
        if (!pl) {
            struct L *pl2;
            plT = func_0013C5B8(p, px1, px2);
            pl2 = func_0013C5B8(p, px2, px1);
            plT->pother = pl2;
            pl2->pother = plT;
            pl = plT;
        }
    } else if (pl) {
        struct L *pl1, *pl2;
        VCALL(px1->plo, 58, void (*)(void *, struct LO *)), px2->plo);
        VCALL(px2->plo, 58, void (*)(void *, struct LO *)), px1->plo);
        pl1 = func_0013C608(p, px1, px2);
        pl2 = func_0013C608(p, px2, px1);
        if (pl1->pv) {
            func_001CBAA0(p, pl1->pv);
            if (!VCALL(pl1->po, 66, int (*)(void *))))
                func_0023E228(pl1->po);
            if (!VCALL(pl2->po, 66, int (*)(void *))))
                func_0023E228(pl2->po);
        }
        func_0011E1F0(p->aCF8, pl1);
        func_0011E1F0(p->aCF8, pl2);
        pl = 0;
    }
    if (pl) {
        pl->pother->f = f;
        pl->f = f;
    }
}
