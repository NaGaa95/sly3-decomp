// If an attached object exists, invoke the owner reset and attached-object reset through their verified virtual slots.
// Reference algorithm: src/hand/func_001DD728.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a, b, c; struct VTE *vt; };
struct S { int a, b, c; struct VTE *vt; char pad[0x24]; struct O *po; };
void func_00221970(struct S *p) {
    if (p->po) {
        {
            struct VTE *e = &p->vt[10];
            ((void (*)(void *))e->pfn)((char *)p + e->d);
        }
        {
            struct O *po = p->po;
            struct VTE *e = &po->vt[56];
            ((void (*)(void *))e->pfn)((char *)po + e->d);
        }
    }
}
