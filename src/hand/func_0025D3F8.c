typedef struct QW { int a[4]; } QW;
void func_0025D478(void *p, QW *pq, void *a, int b, int c, int d);
void func_0025D3F8(void *p, int c, QW *pq, void *a, int b)
{
    int i;
    for (i = 0; i < c; i++) {
        func_0025D478(p, &pq[i], a, b, 0, 0);

    }
}
