// Reference algorithm: src/hand/func_001F0498.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Q { int a; char *ab; };
struct A { char pad[0x40]; int c; };
struct Q *func_00239AD8(struct A *p, int n);
int func_00239B20(struct A *p, int n, int y, int x)
{
    struct Q *pq = func_00239AD8(p, n);
    int r = 0;
    if (pq)
        r = pq->ab[y * p->c + x];
    return r;
}
