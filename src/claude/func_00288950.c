// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x1D0]; float f1D0; float f1D4; char pad2[8]; float f1E0; float f1E4; float f1E8; float f1EC; };
struct S { char pad[0x20]; int k; float t24; struct X *x28; float f2C; float f30; int x34; int x38;
           float f3C; float f40; float f44; float f48; float f4C; float f50; };
extern struct CLOCK { float t; } g_clock;
float func_0011EE68(void *p, float g);
void func_00288950(struct S *p, int k)
{
    struct X *x;
    float a, b;
    if (p->k == k)
        return;
    if (p->k == 2) {
        p->f2C = p->f4C;
        p->f30 = p->f50;
    }
    p->k = k;
    p->t24 = g_clock.t;
    switch (k) {
    case 0:
        p->f3C = -6.2831855f;
        p->f40 = 6.2831855f;
        x = p->x28;
        p->f44 = x->f1D0;
        p->f48 = x->f1D4;
        break;
    case 1:
        a = p->f2C;
        b = p->f30;
        x = p->x28;
        p->f4C = a;
        p->f50 = b;
        p->f3C = a + x->f1E0;
        p->f40 = a + x->f1E4;
        p->f44 = func_0011EE68(&x->f1D0, b + x->f1E8);
        p->f48 = func_0011EE68(&p->x28->f1D0, p->f30 + p->x28->f1EC);
        break;
    }
}
