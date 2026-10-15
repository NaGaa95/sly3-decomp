typedef int qword __attribute__((mode(TI)));
struct S { int a; int pad[3]; qword q; };
void func_002081F8(void *a, qword q, int z, int output_address, float parameter);
float func_00208318(struct S *p, float parameter) { float g; func_002081F8((void *)p->a, p->q, 0, (int)&g, parameter); return g; }
