// Sly 2 reference: src/hand/func_001306A8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; };
void func_00137688(struct O **pp) {
    struct O *p = *pp;
    if (p) { struct VTE *vt = p->vt; ((void (*)(void *))vt[2].pfn)((char *)p + vt[2].d); *pp = 0; }
}
