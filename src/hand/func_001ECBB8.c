// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct S { int a[5]; int n14; };
void *func_001EB5B0(struct S *p, int n, qword q);
qword func_001EC188(void *p, qword q);
int func_001ECBB8(struct S *p, qword q, qword *pq)
{
    void *pv = func_001EB5B0(p, p->n14, q);
    if (!pv) return 0;
    *pq = func_001EC188(pv, q);
    return 1;
}
