// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Allocate and fill a contact record for two shapes, notify both owners and append it to the caller's list
// (same routine as Sly 2 func_001A7C18).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct LO;
struct C;
typedef struct { short d; short pad; void (*pfn)(struct LO *, struct C *, int); } VTE;
struct SUB { char pad[0x60]; void *x60; };
struct LO { int x0, x4, x8; VTE *vt; char pad[0xDC - 0x10]; struct SUB *xDC; };
struct S { void *x0; struct LO *x4; };
struct E { struct S *ps; void *x4; void *x8; struct LO *plo; qword pos; qword x20; int pad[4]; };
struct C { struct E ae[2]; qword dir; float g; float x94, x98; int x9C, xA0, xA4; int xA8; struct C *next; };
struct W { char pad[0x44DC]; char pool[1]; };
struct C *func_0011E118(void *pool);
qword func_0028E910(int n, void *p, qword pos);
void func_001CBC30(struct W *pw, int n, struct C **ppc);
void func_001CB8B0(struct W *pw, struct S *a, struct S *b, qword pos, qword dir, int k, int x, int y, struct C **ppc, float g)
{
    U u;
    struct C *c;
    int i;
    struct E *e;
    struct C *pc;
    c = pc = func_0011E118(pw->pool);
    pc->ae[0].pos = pos;
    {
        qword s, r;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(-g));
        u.q = s;
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(pos), "j"(dir), "j"(s));
        pc->ae[1].pos = r;
    }
    pc->dir = dir;
    for (i = 0; i < 2; i++) {
        e = &c->ae[i];
        if (i == 0)
            e->ps = a;
        else
            e->ps = b;
        if (e->ps) {
            e->x4 = e->ps->x0;
            e->plo = e->ps->x4;
            e->x8 = e->plo->xDC->x60;
        }
        e->x20 = func_0028E910(0, e->x4, e->pos);
    }
    c->g = g;
    c->x9C = k;
    c->x94 = 0.5f;
    c->x98 = 0.5f;
    c->xA0 = x;
    c->xA4 = y;
    for (i = 0; i < 2; i++) {
        struct LO *plo;
        e = &c->ae[i];
        plo = e->plo;
        if (plo)
            plo->vt[59].pfn((struct LO *)((char *)plo + plo->vt[59].d), c, i);
    }
    func_001CBC30(pw, 1, &c);
    {
        struct C *t = c;
        while (t->next)
            t = t->next;
        t->next = *ppc;
        *ppc = c;
    }
}
