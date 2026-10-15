// Sly 2 reference: src/hand/func_001EA6C8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct E { char pad[0x18]; ulong a; ulong b; };
struct S { int x0, x4; void *p8; struct E **apeC; struct E **ape10; };
int func_00233C90(void *p);
ulong func_00233CD0(struct S *p, int i, int j)
{
    ulong fl = p->apeC[i]->b;
    struct E *pe = p->ape10[i * func_00233C90(p->p8) + j];
    if (pe)
        fl |= pe->a;
    return fl;
}
