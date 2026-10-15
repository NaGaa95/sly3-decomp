// Reference algorithm: src/hand/func_00181780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *, int, int, int, int, int); };
struct S { char pad[0xC]; struct VTE *vt; char p2[0x220]; int a; int b; };
extern char D_00475480[];
void func_0025D3F8(void *g, int a, int *pb, struct S *p, int n);
void func_0019E1F8(struct S *p)
{
    struct VTE *e;
    func_0025D3F8(D_00475480, p->a, &p->b, p, 1);
    e = &p->vt[3];
    e->pfn((char *)p + e->d, 5, 0, 0, 0, 0);
}
