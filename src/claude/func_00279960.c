typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x130]; int cmax; int c; qword *a; };
void func_00279960(struct S *p, qword v)
{
    int i = p->c;
    if (i < p->cmax) {
        qword *a = p->a;
        int off = i * 16;
        p->c = i + 1;
        *(qword *)(off + (int)a) = v;
    }
}
