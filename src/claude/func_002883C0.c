// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void *(*pf)(void *); };
struct X { int a[3]; struct VTE *vt; char pad[0x1D0 - 0x10]; float f1D0; float f1D4; char pad2[0x2C4 - 0x1D8]; float f2C4; };
struct S { void *x0; char pad[0x24]; struct X *x28; float f2C; float f30; int x34; int x38; float f3C; float f40; float f44; float f48; };
void func_00169E28(struct S *p);
void func_0011D048(void *m, float *pan, float *tilt);
void func_00288950(struct S *p, int k);
void func_00167960(void *p, float g);
void func_001679E0(void *p, float g);
void func_00166A40(void *p);
void func_002883C0(struct S *p)
{
    struct X *x;
    func_00169E28(p);
    x = p->x28;
    p->f3C = -6.2831855f;
    p->f40 = 6.2831855f;
    p->f44 = x->f1D0;
    p->f48 = x->f1D4;
    p->x34 = 0;
    p->x38 = 0;
    func_0011D048(x->vt[36].pf((char *)x + x->vt[36].d), &p->f2C, &p->f30);
    p->f30 = p->x28->f2C4;
    func_00288950(p, 0);
    func_00167960(p->x0, 1.5f);
    func_001679E0(p->x0, 49.0f);
    func_00166A40(p->x0);
}
