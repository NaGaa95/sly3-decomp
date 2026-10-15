// Reference algorithm: src/hand/func_001B8938.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x113C]; void *p; char pad2[0x18DC - 0x1140]; void *q; };
extern char D_00324818[];
void func_00138CC8(void *a, struct S *p, int n, void *s);
void func_001DE690(struct S *p, int n);
void func_001E1320(struct S *p)
{
    func_00138CC8(p->p, p, 5, D_00324818);
    p->q = p->p;
    p->p = 0;
    func_001DE690(p, 0);
}
