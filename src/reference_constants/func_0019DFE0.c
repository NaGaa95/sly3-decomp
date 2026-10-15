// Reference algorithm: src/hand/func_00181598.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x230]; int a; int b; };
extern char D_00475480[];
void func_0019B668(struct S *p);
void func_0019E060(struct S *p, int n);
void func_0025D3F8(void *g, int a, int *pb, struct S *p, int n);
void func_0019DFE0(struct S *p)
{
    func_0019B668(p);
    func_0019E060(p, 0);
    func_0025D3F8(D_00475480, p->a, &p->b, p, 0);
}
