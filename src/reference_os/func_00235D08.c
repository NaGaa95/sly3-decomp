// Sly 2 reference: src/hand/func_001EC6D0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x30]; qword q; };
struct E { int a; struct O *po; };
struct S { char pad[0x20]; struct E *ae; };
void func_0027E4C0(int a, int b, int c, qword *d, int e);
int func_00235D08(struct S *p, int i, int x, int y)
{
    struct E *pe = p->ae + i; qword q = pe->po->q;
    func_0027E4C0(y, 12, 1, &q, x);
    return 1;
}
