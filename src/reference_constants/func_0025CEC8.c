// Reference algorithm: src/hand/func_0020FA50.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; int (*pfn)(void *); };
struct O { int a, b, c; struct VTE *vt; };
struct S { int a; struct O *po; };
int func_0025CE90(void *pv, struct S *p);
int func_0025CEC8(void *pv, struct S *p) { struct O *o; struct VTE *e; if (!func_0025CE90(pv, p)) return 0; o = p->po; e = &o->vt[66]; return e->pfn((char *)o + e->d); }
