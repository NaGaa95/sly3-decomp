// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct P { float x; float y; int n; } P;
void func_00136908(void *a, float x, float y, int b, int n, int c);
void func_001367F0(void *a, P *p)
{
    func_00136908(a, p->x, p->y, 0, p->n, 0);
}
