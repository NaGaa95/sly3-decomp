// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E { int k; int v; int pad; };
struct O { char pad[0x48]; int c; struct E *a; };
extern char D_00475480[];
int func_0017E1B8(void *g, int k, int v, struct O *p);
void func_0016F090(struct O *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *e = &p->a[i];
        if (e->k == 0) {
            e->v = func_0017E1B8(D_00475480, 4, e->v, p);
        } else if (e->k == 1) {
            e->v = func_0017E1B8(D_00475480, 4, e->v, p);
        }
    }

}
