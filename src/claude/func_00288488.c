// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct VTE { short d; short pad; void (*pf)(void *, M3 *); };
struct X { int a[3]; struct VTE *vt; char pad[0x2C4 - 0x10]; float f2C4; };
struct S { void *x0; char pad[0x24]; struct X *x28; float f2C; float f30; char pad2[0x18]; float f4C; float f50; };
void func_00169E40(struct S *p);
M3 func_0011CAE0(float a, float b);
void func_00287000(struct X *p);
void func_00166548(void *p);
void func_00288488(struct S *p)
{
    M3 m;
    struct X *x;
    func_00169E40(p);
    m = func_0011CAE0(p->f2C, 0.0f);
    x = p->x28;
    x->vt[35].pf((char *)x + x->vt[35].d, &m);
    func_00287000(p->x28);
    p->x28->f2C4 = p->f30;
    p->f4C = p->f2C;
    p->f50 = p->f30;
    func_00166548(p->x0);
}
