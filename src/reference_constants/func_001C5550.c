// Reference algorithm: src/hand/func_001A3650.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct K { int a, b; };
struct S { char pad[0x154]; struct K k; };
void func_001C5868(struct S *p);
void func_001C5550(struct S *p, struct K *pk) { p->k = *pk; func_001C5868(p); }
