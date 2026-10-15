// Reference algorithm: src/hand/func_001BB9B8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct I { int a, b; };
struct E { int id; int n; int c; struct I *a; };
struct S { char pad[0x13C]; int i; int c; struct E *ae; };
void *func_001D25B0(struct MSG *pmsg);
static __inline__ void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D25B0(pmsg); }
void func_001E5B68(struct S *p)
{
    struct E *pe;
    struct MSG msg;
    p->i = -1;
    pe = &p->ae[-1];
    pe->id = -1;
    pe->n = 1;
    if (!pe->a) pe->a = PvAllocMsg(&msg, 0x200, 0x10);
}
