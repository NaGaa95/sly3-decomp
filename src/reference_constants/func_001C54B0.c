// Reference algorithm: src/hand/func_001A35B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD0]; int xe0; };
void func_001C5A40(struct S *p);
void func_001C5868(struct S *p);
void func_001C54B0(struct S *p, int a) { func_001C5A40(p); p->xe0 = a; func_001C5868(p); }
