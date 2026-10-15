// Reference algorithm: src/hand/func_001C2048.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x40]; int a; char pad2[0]; int b; };
void func_001C7340(struct S *p);
void func_0017A9D8(struct S *p) { func_001C7340(p); p->a = -1; p->b = -1; }
