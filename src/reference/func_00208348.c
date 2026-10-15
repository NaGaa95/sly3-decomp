// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
typedef int qword __attribute__((mode(TI)));
struct S { int a; int pad[3]; qword q; };
void func_00208288(int a, qword q, int z, float *pg);
float func_00208348(struct S *p) { float g; func_00208288(p->a, p->q, 0, &g); return g; }
