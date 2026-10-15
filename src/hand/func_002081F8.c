// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct S { int pad[5]; void *p14; void *p18; int pad2[3]; void *p28; void *p2C; };
void func_0022E148(void *p, float t, qword *pq, int n);
void func_00120A00(qword q, qword a, qword b, int n, int c, int d);
void func_002081F8(struct S *p, qword q, int c, int d, float t)
{
    qword a, b;
    func_0022E148(p->p14, t, &a, 0);
    func_0022E148(p->p28, t, &b, 0);
    func_00120A00(q, a, b, 0, c, d);
}
