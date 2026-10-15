// Reference algorithm: src/hand/func_0012DD28.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct T { int a[7]; void *q; } T;
typedef struct Q { int pad[12]; void *b; } Q;
T *func_0012FFB0(int k, void *a, void *b, void *c, int d);
void func_0028ECE0(void *a, void *b, T *p);
T *func_00130218(void *a, void *b, void *c, Q *q)
{
    T *p = func_0012FFB0(7, a, b, c, b == q->b ? 0xF : 0xE);
    p->q = q;
    func_0028ECE0(a, b, p);
    return p;
}
