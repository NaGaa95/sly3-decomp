// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 src/hand/func_001F8F80.c.
typedef int DI __attribute__((mode(DI)));
struct H { char pad[0x98]; short h98; };
struct E { char pad[0xA0]; int nA0; char pad2[0xC0 - 0xA4]; int nC0; };
struct O { char pad[0x48]; struct H *p48; struct H *p4C; char pad2[0xD8 - 0x50]; struct E *pe; char pad3[0x120 - 0xDC]; DI fl; };
struct L { char pad[0x40]; struct L *pNext; char pad2[0x60 - 0x44]; struct O *po; };
struct P { char pad[0x44B8]; struct L *pl; };
struct A { void *objects[0x300]; char done; int n; };
int func_0028F010(int);
void func_00242AA8(struct P *, struct O *, int *, void **);
void func_00242E50(struct P *, int, int, void **);
void func_002BBFE8(void *, int);
void func_00242B90(struct P *p, int k)
{
    struct A a;
    struct L *pl;
    struct O *po;
    for (pl = p->pl; pl; pl = pl->pNext) {
        struct E *pe;
        po = pl->po;
        pe = po->pe;
        if (!pe) continue;
        if (po->fl & ((DI)1 << 59)) continue;
        if (pe->nC0 == 3 && pe->nA0 == 3) continue;
        if (k & 1) {
            if (func_0028F010(po->p48->h98) && func_0028F010(po->p4C->h98))
                continue;
        }
        a.n = 0;
        func_00242AA8(p, po, &a.n, a.objects);
        func_00242E50(p, k, a.n, a.objects);
    }
    for (pl = p->pl; pl; pl = pl->pNext) {
        po = pl->po;
        po->fl &= ~((DI)1 << 59);
        po->fl &= ~((DI)1 << 60);
    }
    func_002BBFE8(&a.done, 2);
}
