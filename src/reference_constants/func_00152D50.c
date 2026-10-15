// Reference algorithm: src/hand/func_00140678.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x11B4]; int b; int pad2; int a; int d; int c; };
void func_00155D00(struct X *p, int a, int b, int c, int d);
void func_00152D50(struct X *p, int a, int b, int c, int d)
{
    if (b != p->b) func_00155D00(p, a, b, c, d);
    p->b = b;
    p->a = a;
    p->d = d;
    p->c = c;
}
