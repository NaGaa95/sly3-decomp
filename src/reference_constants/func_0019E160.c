// Reference algorithm: src/hand/func_001816E8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x230]; int a; int b; };
extern char D_00475480[];
void func_0025D350(void *g, void *pb, int n, void *pa, int x, int y, int z, int w);
void func_0019E160(struct S *p, int x, int y, int z, int w)
{
    func_0025D350(D_00475480, &p->b, 4, &p->a, x, y, z, w);
}
