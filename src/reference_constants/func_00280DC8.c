// Reference algorithm: src/hand/func_002292D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pf)(void *, void *); };
struct O { int a[3]; struct VTE *vt; };
struct B { int a; struct O *po; };
void func_00280DC8(void *p, struct B *b)
{
    struct O *po = b->po;
    po->vt[76].pf((char *)po + po->vt[76].d, p);
}
