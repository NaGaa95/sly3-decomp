// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { int a; char pad[0x9C]; int xa0; int xa4; };
void func_00291BC0(void);
void func_00290E98(int n, int v);
void func_00291118(unsigned int m);
void func_001DB368(struct S *p)
{
    p->a = 0;
    func_00291BC0();
    func_00290E98(2, p->xa0);
    func_00290E98(0x10, p->xa4);
    func_00291118(0xFFFFFFFF);
}
