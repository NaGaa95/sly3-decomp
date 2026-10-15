// Sly 2 reference: src/hand/func_0019E9C8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { int pad[0x94/4]; int a94; int a98; };
void func_001BFA08(void *p, struct S *s) { s->a94 = 0; s->a98 = 0; }
