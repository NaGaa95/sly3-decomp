// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x98]; float f98; };
struct S { char pad[0x10]; int x10; struct X *x14; void *x18; };
struct T { float f[8]; };
extern char D_00475480[];
void *func_0017E1B8(void *g, int a, int b, int c);
void func_00283B98(struct S *p, void *q);
void *func_00292034(void *p, int c, int n);
void func_00262848(void *o, struct T *t);
void func_00283970(struct S *p)
{
    p->x18 = func_0017E1B8(D_00475480, 0x405, 0x41E, 0);
    func_00283B98(p, func_0017E1B8(D_00475480, 0x105, p->x10, 0));
    if (p->x18 && p->x14 && p->x14->f98 != 0.0f) {
        struct T t;
        func_00292034(&t, 0, sizeof(t));
        t.f[3] = 1.0f;
        t.f[0] = 1.0f;
        t.f[5] += p->x14->f98;
        func_00262848(p->x18, &t);
    }
}
