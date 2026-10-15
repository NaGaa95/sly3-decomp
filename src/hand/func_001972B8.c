// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct K { int a, b; };
struct R { int x, y; struct K k; };
struct R *func_00197628(void *p, int a, int b);
void func_001972B8(void *p, struct K *pk) { func_00197628(p, 1, -1)->k = *pk; }
