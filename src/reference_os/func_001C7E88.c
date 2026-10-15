// Sly 2 reference: src/hand/func_001A5D08.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
void func_001C7E88(struct O *p) { struct VTE *e = &p->vt[9]; e->pfn((char *)p + e->d); }
