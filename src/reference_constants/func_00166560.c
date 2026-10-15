// Reference algorithm: src/hand/func_0014D8D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CMX { char pad[0x2F4]; int n; float a; float b; };
void func_00166560(struct CMX *p, float a, float b)
{
    int m = 2;
    p->b = b;
    p->a = a;
    if (m < p->n) m = p->n;
    p->n = m;
}
