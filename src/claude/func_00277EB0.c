// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct X { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct X *(*pf)(void *); };
struct S { int a[3]; struct VTE *vt; char pad[0x154 - 0x10]; int x154; int x158; int x15C; };
void func_001C7A00(struct S *p, int a, int b);
void func_00277C08(struct S *p, int a, int b, int c, qword q, float f);
void func_00277EB0(struct S *p, float f)
{
    struct X *x;
    func_001C7A00(p, 0, 0x13);
    x = p->vt[36].pf((char *)p + p->vt[36].d);
    func_00277C08(p, p->x154, p->x158, p->x15C, x->q30, f);
}
void func_00277F18(struct S *p, int a)
{
    p->x158 = a;
}
