// Reference algorithm: src/hand/func_001BB950.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct I { int a, b; };
struct E { int id; int n; int c; struct I *a; };
struct S { char pad[0x13C]; int i; int c; struct E *ae; };
void *func_001D25B0(struct MSG *pmsg);
static __inline__ void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D25B0(pmsg); }
void func_001E5B00(struct S *p, int id)
{
    struct MSG msg;
    if (p->c < 0x20) {
        struct E *pe;
        p->i = p->c++;
        pe = &p->ae[p->i];
        pe->id = id;
        pe->n = 1;
        pe->a = PvAllocMsg(&msg, 0x200, 0x10);
    }
}
