// Sly 2 reference: src/hand/func_0012DDB0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct M4 { int q[16]; } __attribute__((aligned(16))) M4;
typedef struct T { int a[7]; int n; M4 mat; } T;
T *func_0012FFB0(int k, void *a, void *b, void *c, void *d);
void func_0028ECE0(void *a, void *b, T *p);
T *func_001302A0(void *a, void *b, void *c, void *d, int n, M4 *pmat)
{
    T *p = func_0012FFB0(6, a, b, c, d);
    p->n = n;
    p->mat = *pmat;
    func_0028ECE0(a, b, p);
    return p;
}
