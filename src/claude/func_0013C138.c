// SLY3_CFLAGS: -Os -G0
/* Sly 2 func_001337D0 (detach a node from the link/edge tables), Sly 3 offsets. */
struct VTE { short d; short pad; void *pfn; };
struct LO { int pad[3]; struct VTE *vt; };
struct X;
struct L { void *pv; struct L *pnext; struct L *pother; struct LO *po; int f; };
struct LX { char pad[0xDC]; struct X *px; };
struct X { char pad[0x60]; struct LO *plo; struct L *pl; int x68; void *pv6C; unsigned long grf; };
struct E { int f0; struct X *px; int x8; };
struct P { char pad[0x446C]; int c; struct E *aae[3]; char a447C[0x4494 - 0x447C]; char a4494[0x44AC - 0x4494];
    char a44AC[0xC]; char a44B8[0xC]; char a44C4[0xC]; char a44D0[0xC]; };
struct L *func_0013C608(struct P *, struct X *, struct X *);
void func_001CBAA0(struct P *, void *);
void func_0023E228(struct LO *);
void Free__9POOLSTATEPv(void *, void *);
void func_0011B028(void *, struct X *);
int func_0011B0C0(void *, struct X *);
void *func_00291F38(void *, void *, int);
#define VCALL(po, n, T) ((T)(po)->vt[n].pfn)((char *)(po) + (po)->vt[n].d
void func_0013C138(struct P *p, struct X *px)
{
    struct L *pl, *plNext;
    int i;
    for (pl = px->pl; pl; pl = plNext) {
        struct L *pl2;
        VCALL(px->plo, 58, void (*)(void *, struct LO *)), pl->po);
        VCALL(pl->po, 58, void (*)(void *, struct LO *)), px->plo);
        pl2 = func_0013C608(p, ((struct LX *)pl->po)->px, px);
        if (pl->pv) {
            if (!VCALL(pl->po, 66, int (*)(void *))))
                func_0023E228(pl->po);
            func_001CBAA0(p, pl->pv);
        }
        plNext = pl->pnext;
        Free__9POOLSTATEPv(p->a4494, pl);
        Free__9POOLSTATEPv(p->a4494, pl2);
    }
    func_001CBAA0(p, px->pv6C);
    func_0011B028(p->a44AC, px);
    if (func_0011B0C0(p->a44B8, px))
        func_0011B028(p->a44B8, px);
    if ((px->grf & 1) == 1)
        func_0011B028(p->a44C4, px);
    if (px->grf & 2)
        func_0011B028(p->a44D0, px);
    for (i = 0; i < 3; i++) {
        struct E *ae = p->aae[i];
        struct E *pe = ae;
        struct E *peStart;
        while (1) {
            while (pe->px != px)
                pe++;
            if (pe->f0)
                break;
            peStart = pe++;
        }
        func_00291F38(peStart, peStart + 1, (pe - peStart) * sizeof(struct E) - sizeof(struct E));
        func_00291F38(pe - 1, pe + 1, (p->c - (pe - ae)) * sizeof(struct E) - sizeof(struct E));
    }
    p->c -= 2;
    Free__9POOLSTATEPv(p->a447C, px);
}
