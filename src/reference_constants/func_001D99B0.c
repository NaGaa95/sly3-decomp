// Reference algorithm: src/hand/func_0017E5F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a[8]; };
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; char *p30; int n34; };
int func_001EE878(void *pe, void *p, float g);
int func_001D99B0(struct S *p) { return func_001EE878(p->p30 + 0x50 + p->n34 * 32, p->p10, 25.0f); }
