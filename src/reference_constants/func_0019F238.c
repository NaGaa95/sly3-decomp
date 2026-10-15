// Reference algorithm: src/hand/func_00182780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E { int a; int b; int c; char p[0x10]; int x1c; float g; int x24; int p2; float h; };
struct S { char pad[0x1F4]; int c; struct E ae[4]; };
void func_0023E290(struct S *p);
void func_0022F798(int n, qword *pa, qword *pb);
void func_0023E940(struct S *p, qword q, float g);
void func_0019F238(struct S *p)
{
    int i;
    func_0023E290(p);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        qword a, b;
        func_0022F798(pe->x24, &a, &b);
        func_0023E940(p, a, pe->g);
        func_0023E940(p, b, pe->g);
    }
}
