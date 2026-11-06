// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[8]; float a8[2]; float a10[2]; int n18; int a1C[32]; int n9C; };
extern char D_0036BD20[];
float func_00171C98(void *);
float func_002A3510(float);
int func_0011E8F0(int, int);
static inline void Swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }
void func_00257B80(struct S *p)
{
    float w[2];
    float f;
    int c = 0;
    int i, k;
    f = func_00171C98(D_0036BD20);
    for (i = 0; i < 2; i++) {
        int n, j;
        w[i] = (1.0f - f) * p->a10[i] + f * p->a8[i];
        n = (int)func_002A3510(w[i] * 32.0f);
        for (j = 0; j < n; j++)
            p->a1C[c++] = i;
    }
    for (k = 0; k < c; k++) {
        int r = func_0011E8F0(0, c - 1);
        Swap(&p->a1C[k], &p->a1C[r]);
    }
    p->n18 = c;
    p->n9C = 0;
}
