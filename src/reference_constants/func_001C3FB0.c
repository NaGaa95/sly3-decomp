// Reference algorithm: src/hand/func_001A2358.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; int (*pfn)(void *, int); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { struct O *po; };
int func_001C3FB0(struct S *p, int a) { struct O *o = p->po; struct VTE *e = &o->vt[97]; return e->pfn((char *)o + e->d, a); }
