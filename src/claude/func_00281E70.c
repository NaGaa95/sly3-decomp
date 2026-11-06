// SLY3_CFLAGS: -Os -G0
struct E { int id; int x4; float f8; };
struct G { char pad[0x3EB4]; int x3EB4; int c3EB8; int a3EBC[1]; };
extern struct G D_00475480;
struct S { char pad[0x158]; int x158; int c15C; char a160[0x30]; char pad2[0x1A4 - 0x190]; int x1A4; float f1A8; };
void *func_00292034(void *p, int c, int n);
int func_00168DD8(int id);
struct E *func_00281E28(struct S *p, int id);
void func_001D2898(void *d, void *s, int n);
void func_00281E70(struct S *p)
{
    struct G *g = &D_00475480;
    struct E a[4];
    int i, n;
    if (p->x158 == g->x3EB4)
        return;
    p->x158 = g->x3EB4;
    func_00292034(a, 0, sizeof(a));
    i = 0;
    n = 0;
    for (; i < D_00475480.c3EB8; i++) {
        int id = D_00475480.a3EBC[i];
        struct E *e, *src;
        if (func_00168DD8(id))
            continue;
        e = &a[n++];
        src = func_00281E28(p, id);
        if (src) {
            *e = *src;
        } else {
            e->id = id;
            e->x4 = -1;
        }
        if (p->x1A4)
            e->f8 = p->f1A8;
    }
    p->c15C = n;
    func_001D2898(p->a160, a, sizeof(a));
}
