// Reference algorithm: src/hand/func_001A5BF0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x10]; struct S *x10; };
int func_0013B500(struct S *p, int n);
struct S *func_001C7D60(struct S *p) { if (func_0013B500(p, 0x2F)) return p; return p->x10; }
