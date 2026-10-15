// Reference algorithm: src/hand/func_00180188.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x190]; int n; };
void func_0019B420(struct S *p);
void func_0019C9F8(struct S *p)
{
    func_0019B420(p);
    p->n = 10;
}
