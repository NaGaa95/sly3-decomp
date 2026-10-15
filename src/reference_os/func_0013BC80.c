// Sly 2 reference: src/hand/func_00133340.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct S { int pad[3]; struct VTE *vt; };
void func_0013BC80(struct S *p) { struct VTE *vt = p->vt; ((void (*)(void *, int, int, int, int, int))vt[3].pfn)((char *)p + vt[3].d, 5, 0, 0, 0, 0); }
