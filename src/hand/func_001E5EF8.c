// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct MSG { int cb; int nKind; };
struct I { int a, b; };
struct S;
struct I *func_001E5F60(struct S *p, int x);
void *func_001D25B0(struct MSG *pmsg);
static __inline__ void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D25B0(pmsg); }
void func_001E5EF8(struct S *p, int a, int b)
{
    struct MSG msg;
    struct I *pi = func_001E5F60(p, 0xC);
    pi->b = (int)PvAllocMsg(&msg, 8, 0x10);
    ((int *)pi->b)[0] = a;
    ((int *)pi->b)[1] = b;
}
