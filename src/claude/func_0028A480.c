// SLY3_CFLAGS: -Os -G0
struct E { int x0; int x4; int x8; int xC; float f10; char pad[0x6C]; };
struct S { char pad[0x44]; int c44; int n48; int c4C; int a50[4]; struct E e[8]; int x460; };
int func_0028A470(struct S *p);
struct E *func_0028A480(struct S *p, int a, int b)
{
    int i = p->c44;
    int j, n;
    struct E *e;
    p->c44 = i + 1;
    e = &p->e[i];
    p->x460 = i;
    e->x0 = a;
    e->xC = func_0028A470(p);
    e->f10 = 1.0f;
    n = p->n48;
    for (j = 0; j < 4 && j <= n; j++) {
        if (b + p->a50[j] < 5) {
            e->x4 = j;
            e->x8 = p->a50[j];
            p->a50[j] += b;
            if (j == p->n48)
                p->n48 = j + 1;
            break;
        }
    }
    return e;
}
