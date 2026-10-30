// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
int *func_00185860(void *g, void *a, int n);
char *func_00185720(void *g, void *a);
int func_0014DBA0(void *p);
void *func_002459F8(int n);
void func_00244F08(void *p, int n);
void func_0014DC98(void *p, int n);
struct S { char pad[0x18]; int x18; char pad2[0x127C - 0x1C]; char *x127C; };
void func_001561F0(struct S *a, struct S *b)
{
    int *ra = 0, *rb = 0;
    char *pa = a->x127C;
    char *pb = b->x127C;
    char *x, *y;
    if (pa)
        ra = func_00185860(D_0036C700, a, 0);
    if (pb)
        rb = func_00185860(D_0036C700, a, 0);
    if (ra)
        *ra = b->x18;
    if (rb)
        *rb = a->x18;
    x = func_00185720(D_0036C700, a);
    y = func_00185720(D_0036C700, b);
    *(int *)(x + 8) = pb ? func_0014DBA0(pb) : -1;
    *(int *)(y + 8) = pa ? func_0014DBA0(pa) : -1;
    if (pa || pb)
        func_00244F08(func_002459F8(0x27), 0);
    if (pa) {
        func_0014DC98(pa, 7);
        *(struct S **)(pa + 0x140) = b;
        func_0014DC98(pa, 2);
    }
    if (pb) {
        func_0014DC98(pb, 7);
        *(struct S **)(pb + 0x140) = a;
        func_0014DC98(pb, 2);
    }
}
