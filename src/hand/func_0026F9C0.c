// Preserve the eight-byte selection key around the inherited update.
// Reference algorithm: src/hand/func_00156D98.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct K { short x; short y; int i; };
struct S { char pad[0xD0]; struct K k; };
void func_0028FE20(struct S *p, int n);
void func_0026F9C0(struct S *p, int n)
{
    struct K k = p->k;
    func_0028FE20(p, n);
    p->k = k;
}
