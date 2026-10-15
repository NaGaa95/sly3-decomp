// Reference algorithm: src/hand/func_00143090.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S8 { float a, b; };
struct X { char pad[0x11F0]; struct S8 a, b, c; };
void func_00155AB8(struct X *p, struct S8 *a, struct S8 *b, struct S8 *c)
{
    p->a = *a;
    p->b = *b;
    p->c = *c;
}
