// Sly 2 reference: src/hand/func_0019EAA0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct S { int pad[0x30/4]; qword a; qword b; };
void func_001BFAC0(struct S *s, qword a, qword b) { s->a = a; s->b = b; }
