// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
float func_0022DE50(void *p);
void func_0022EA50(void *p, qword q, int a, int b, int c, int d, int e, float g);
void func_0022EEA0(void *p, qword q, int a, int b, int c, int d, int e)
{
    func_0022EA50(p, q, a, b, c, d, e, func_0022DE50(p));
}
