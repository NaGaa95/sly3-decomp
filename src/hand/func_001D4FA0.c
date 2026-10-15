// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct S { int a, b; int x8; int xc; int pad[2]; int x18; int x1c; };
extern char D_0046F550[];
void func_001D3960(void *p, int a, int b, int c, int d);
void func_001D4FA0(struct S *p)
{
    func_001D3960(D_0046F550, p->x8, p->xc, 0, p->x18);
    if (p) p->x1c |= 2;
}
