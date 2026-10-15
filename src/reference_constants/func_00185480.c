// Reference algorithm: src/hand/func_00161958.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x42FC]; struct O *po; char pad2[0x4F60 - 0x4300]; int n; };
void func_00185480(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        struct VTE *e = &po->vt[54];
        e->pfn((char *)po + e->d);
    }
    p->n = 0;
}
