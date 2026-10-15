// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct T { int a[7]; float x; float y; } T;
T *func_0012FFB0(int k, void *a, void *b, void *c, void *d);
void func_0028ECE0(void *a, void *b, T *p);
T *func_00130190(void *a, void *b, void *c, void *d, float x, float y)
{
    T *p = func_0012FFB0(4, a, b, c, d);
    p->x = x;
    p->y = y;
    func_0028ECE0(a, b, p);
    return p;
}
