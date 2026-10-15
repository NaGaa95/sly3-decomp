// Reference algorithm: src/hand/func_001E5468.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pf)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x6C]; struct O *po; };
void func_0022B770(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        po->vt[54].pf((char *)po + po->vt[54].d);
        p->po = 0;
    }
}
