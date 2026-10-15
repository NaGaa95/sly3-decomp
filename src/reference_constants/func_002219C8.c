// Reference algorithm: src/hand/func_001DD728.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a, b, c; struct VTE *vt; };
struct S { int a, b, c; struct VTE *vt; char pad[0x24]; struct O *po; };
void func_002219C8(struct S *p) {
    if (p->po) {
        {
            struct VTE *e = &p->vt[11];
            ((void (*)(void *))e->pfn)((char *)p + e->d);
        }
        {
            struct O *po = p->po;
            struct VTE *e = &po->vt[54];
            ((void (*)(void *))e->pfn)((char *)po + e->d);
        }
    }
}
