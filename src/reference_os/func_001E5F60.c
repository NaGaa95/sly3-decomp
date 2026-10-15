// Sly 2 reference: src/hand/func_001BBDB0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct I { int a, b; };
struct E { int id; int n; int c; struct I *a; };
struct S;
extern char D_00324BB0[];
struct E *func_001E6018(struct S *p, void *k);
struct I *func_001E5F60(struct S *p, int x)
{
    struct E *pe = func_001E6018(p, D_00324BB0);
    struct I *pi;
    if (!pe) return 0;
    if (pe->c >= 0x40) return 0;
    pi = &pe->a[pe->c++];
    pi->a = x;
    return pi;
}
