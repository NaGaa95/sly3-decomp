// Reference algorithm: src/hand/func_001C2048.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x190]; int a; char pad2[4]; int b; };
void func_001F3B50(struct S *p);
void func_00171108(struct S *p) { func_001F3B50(p); p->a = -1; p->b = -1; }
