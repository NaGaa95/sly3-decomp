// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct K { int a, b; };
struct T { char pad[0x10]; int x; struct K k; };
struct T *func_00241AD8(void *);
void func_00241B18(void *p, int x, struct K *pk) { struct T *pt = func_00241AD8(p); pt->x = x; if (pk) pt->k = *pk; }
