// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void func_001304B8(char *p, qword *pq, int *pv)
{
    if (pq) *pq = *(qword *)(*(char **)(p + 8) + 0xC0);
    if (pv) { pv[2] = 0; pv[1] = 0; pv[0] = 0; }
}
