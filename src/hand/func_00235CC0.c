// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct E { int a; int b; };
struct S { char pad[0x20]; struct E *ae; };
void func_0027E4C0(int a, int b, int c, int d, int e);
int func_00235CC0(struct S *p, int i, int x, int y)
{
    struct E *pe = &p->ae[i];
    func_0027E4C0(y, 12, pe->a, pe->b, x);
    return pe->a;
}
