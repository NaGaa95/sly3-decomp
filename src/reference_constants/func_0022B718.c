// Reference algorithm: src/hand/func_001E5410.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

struct VTE { short d; short pad; void (*pf)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x60]; struct O *po; int n5C; };
void func_0013BD88(struct O *po, struct S *p);
void func_0022B718(struct S *p)
{
    if (p->po) {
        func_0013BD88(p->po, p);
        { struct O *po = p->po; po->vt[2].pf((char *)po + po->vt[2].d); }
        p->po = 0;
        p->n5C = 0;
    }
}
