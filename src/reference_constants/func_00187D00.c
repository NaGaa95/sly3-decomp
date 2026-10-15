// Reference algorithm: src/hand/func_00163430.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x44]; int n; };
struct S { char pad[0x54]; struct X *a; struct X *b; };
static inline int Max(int a, int b) { return a > b ? a : b; }
int func_00187D00(struct S *p)
{
    int n = p->a->n;
    return n < 2 ? n : Max(p->b->n, 1);
}
