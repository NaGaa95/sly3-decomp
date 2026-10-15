// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct A { int pad[2]; int a, b, c, d; };
struct S { int n0; int a, b, c, d; int n14; int n18; };
int func_00291B48(int a, int b, int c, int d, int e, int f);
void func_001DAC88(struct S *p);
int func_001DABD8(struct S *p, struct A *pa)
{
    p->a = pa->a;
    p->b = pa->b;
    p->c = pa->c;
    p->d = pa->d;
    if (p->a == 0x10) {
        p->n18 = p->c << 12;
        p->n14 = func_00291B48(0x400, 0x1000, 0x400, 0, 2, 3);
    } else {
        p->n18 = 0x6000;
        p->n14 = func_00291B48(0x6000, 0, 0x400, 0, 2, 2);
    }
    if (p->n14 < 0)
        return 0;
    func_001DAC88(p);
    return 1;
}
