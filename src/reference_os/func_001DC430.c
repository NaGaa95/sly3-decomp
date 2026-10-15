// Sly 2 reference: src/hand/func_001B41D0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0x1C]; int x1C; int x20; int x24; int x28; };
struct S { char pad[0x114]; struct T *x114; char x118[0x58]; int x170; char pad2[0x6C]; int x1E0; };
void func_0013B320(struct T *t);
void func_00293920(int n);
int func_002AE198(void *p, int a, int n);
void func_0013B388(struct T *t, int r);
int func_001DC430(struct S *p, int wait)
{
    int n, r;
    n = p->x114->x1C - p->x114->x24;
    while (n == 0) {
        if (!p->x114->x28) return 2;
        func_0013B320(p->x114);
        n = p->x114->x1C - p->x114->x24;
        if (n == 0 && !wait) return 0;
    }
    func_00293920(0);
    r = func_002AE198(p->x118, p->x114->x20 + p->x114->x24, n);
    func_0013B388(p->x114, r);
    if (r) return 0;
    if (p->x170 >= n && p->x1E0 >= n) return 2;
    return 1;
}
