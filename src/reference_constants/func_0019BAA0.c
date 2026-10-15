// Reference algorithm: src/hand/func_0017F550.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x19C]; void *p194; void *p198; };
int func_00138AC8(void *p);
int func_00239E70(void *p);
int func_00239E50(void *p);
int func_0019BAA0(struct S *p) { if (p->p194) return func_00138AC8(p->p194); { int f = 1; if (p->p198) f = func_00239E70(p->p198) == func_00239E50(p->p198); return f; } }
