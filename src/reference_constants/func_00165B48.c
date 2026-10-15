// Reference algorithm: src/hand/func_001FE990.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x3EB8]; int c; int a[1]; };
int func_00165B48(struct S *p, int n) { int i; for (i = 0; i < p->c; i++) if (p->a[i] == n) return i; return -1; }
