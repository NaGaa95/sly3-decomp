// Sly 2 reference: src/hand/func_00258448.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct { float a, b, x; float y; } P;
void func_002BC888(P *p, float x, float y) { p->x = x; p->y = y; }
