// SLY3_CFLAGS: -Os -G0
// Adapted from the matched Sly 2 source src/hand/func_001336F0.c (Sly 3 offsets). The Sly 3 loop is a goto loop (no loop opts):
// the a0 entry pointer is a user-incremented pointer, the a10 entry is recomputed from a base pointer each pass.
struct E { int k; void *p; int *pn; };
struct N { int a0[4]; int a10[4]; char pad[0x34 - 0x20]; int dl34[3]; char pad2[0x60 - 0x40]; void *f60; };
struct P { char pad[0x14]; void *f14; };
struct G { char pad[0x3df8]; int dl3df8[3]; char pad2[0x446c - 0x3e04]; int ce; struct E *ape[3]; int pool447c;
    char pad3[0x44ac - 0x4480]; int dl44ac[3]; int dl44b8[3]; };
struct N *func_0011E118(void *);
void func_0011AF38(void *, int);
void func_0011AF60(void *, struct N *);
int func_0011B0C0(void *, void *);
struct N *func_0013C050(struct G *pg, struct P *p) {
    int i;
    int *pa;
    struct N *pn = func_0011E118(&pg->pool447c);
    func_0011AF38(pn->dl34, 0x70);
    pn->f60 = p;
    func_0011AF60(pg->dl44ac, pn);
    if (func_0011B0C0(pg->dl3df8, p->f14)) func_0011AF60(pg->dl44b8, pn);
    i = 0;
    pa = pn->a0;
loop:
    {
        struct E *pe = &pg->ape[i][pg->ce];
        pe->k = 0;
        pe->p = pn;
        pe->pn = pa++;
        pe++;
        pe->k = 1;
        pe->p = pn;
        { int *pb = pn->a10; pe->pn = pb + i; }
    }
    if (++i < 3) goto loop;
    pg->ce += 2;
    return pn;
}
