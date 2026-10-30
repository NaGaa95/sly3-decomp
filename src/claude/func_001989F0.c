// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0x80]; int c; int *a; };
void func_001989F0(struct S *p, int x) { if (p->c < 8) { p->a[p->c++] = x; } }
