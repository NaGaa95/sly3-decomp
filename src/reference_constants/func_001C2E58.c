// Reference algorithm: src/hand/func_001A15B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { int a, b; };
struct S { char pad[0xC]; struct K k; };
void func_001C2E58(struct S *p, struct K k) { p->k = k; }
