// Sly 2 reference: src/hand/func_001E9F50.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void *func_001ED678(qword q, int n);
int func_001EDFE0(void *p, int n, qword q, qword q2, int c, void **ap);
int func_001E6BF0(void *p, qword q);
void *func_00231C50(qword q)
{
    void *ap[0x40];
    void *p = func_001ED678(q, 0);
    int c, i;
    if (!p) return 0;
    c = func_001EDFE0(p, 0, q, q, 0x40, ap);
    for (i = 0; i < c; i++) {
        void *pT = ap[i];
        if (func_001E6BF0(pT, q)) return pT;
    }
    return 0;
}
