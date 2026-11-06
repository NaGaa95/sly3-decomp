// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
typedef struct { VU r[3]; } M3;
struct A { qword p0; char pad[0x10]; qword p1; };
struct P { char pad[0x40]; char a40[0x20]; float t; char pad1[0xC]; float x, y, z; };
struct X { char pad[0x11C]; int x11C; };
struct S { char pad[0x20]; struct X *x20; char pad1[0xC8 - 0x24]; float gC8; };
void *func_00292034(void *p, int c, int n);
void func_00274270(struct S *ps, qword v, qword *pq, void *pv);
void func_00274390(struct X *px, qword *pq, M3 *pm, void *pv, float g, float h, int f, qword *ppos);
void func_00273AB0(struct P *p, struct A *pa, qword *ppos, struct S *ps)
{
    VU u;
    qword r, a;
    __asm__("qmtc2.ni %1, %0" : "=j"(a) : "r"(p->t - 1.0f));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(pa->p0), "j"(pa->p1), "j"(a));
    u.q = a;
    *ppos = r;
    if (ps) {
        struct X *x = ps->x20;
        if (x) {
            M3 m;
            char ab[0x10];
            int n;
            func_00292034(&m, 0, 0x30);
            m.r[0].f[1] = p->x;
            m.r[1].f[1] = p->y;
            m.r[2].f[1] = p->z;
            n = x->x11C;
            x->x11C = 0;
            func_00274270(ps, *ppos, &u.q, ab);
            func_00274390(x, &u.q, &m, p->a40, ps->gC8, 0.0f, 1, ppos);
            x->x11C = n;
        }
    }
}
