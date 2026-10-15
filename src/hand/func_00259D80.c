// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { int a; int b; int c; int d; int e; };
void func_00259F88(struct S *p, int n);
void func_00259D80(struct S *p) { p->b = -1; p->e = 1; func_00259F88(p, 0); }
