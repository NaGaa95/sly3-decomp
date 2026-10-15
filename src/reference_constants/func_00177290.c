// Reference algorithm: src/hand/func_00156D98.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { short x; short y; int i; };
struct S { char pad[0x40]; struct K k; };
void func_001C8BF0(struct S *p, int n);
void func_00177290(struct S *p, int n)
{
    struct K k = p->k;
    func_001C8BF0(p, n);
    p->k = k;
}
