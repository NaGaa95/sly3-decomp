// Reference algorithm: src/hand/func_00203758.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xDC]; void *p; int n; };
int func_00188A38(void *p);
int func_0024D6B0(struct S *p) { if (p->p) return func_00188A38(p->p); return p->n; }
