// SLY3_CFLAGS: -Os -G0
struct REQ { int cb; int align; };
void *func_001D25B0(struct REQ *r);
void func_001D2898(void *d, void *s, int n);
struct ARR { int x; int cap; int n; int *a; };
void func_00151A78(struct ARR *p, int cnt, int *src)
{
    int need = p->n + cnt;
    if (p->cap < need) {
        int c = p->cap;
        int *a;
        struct REQ r;
        do {
            int d = c * 2;
            if (d < 32) d = 32; c = d;
        } while (c < need);
        r.cb = c * 4;
        r.align = 16;
        a = func_001D25B0(&r);
        func_001D2898(a, p->a, p->n * 4);
        p->cap = c;
        p->a = a;
    }
    func_001D2898(p->a + p->n, src, cnt * 4);
    p->n += cnt;
}
