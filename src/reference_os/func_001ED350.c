// Sly 2 reference: src/hand/func_001C0A40.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct S { int a[0x30]; };
void *func_001ED1B0(void *p, qword a, qword b, int c, int d, int e);
int func_001EDFE0(void *p, int z, qword a, qword b, int c, void **ap);
void *func_001E6830(void *p, qword a, qword b, int n, struct S *ps);
void *func_00164D98(void *p, int d, void *r, struct S *ps, int c, int d2, int one);
void *func_001ED350(void *p, qword a, qword b, int c, int d)
{
    void *ap[0x80];
    struct S s;
    void *pv;
    int n, i;
    pv = func_001ED1B0(p, a, b, c, d, 2);
    if (!pv) return 0;
    n = func_001EDFE0(p, 0, a, b, 0x80, ap);
    for (i = 0; i < n; i++) {
        void *r = func_001E6830(ap[i], a, b, 2, &s);
        pv = func_00164D98(pv, d, r, &s, c, d, 1);
        if (!pv) goto out;
    }
out:
    return pv;
}
