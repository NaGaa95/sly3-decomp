// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; };
struct Z { char pad[0xD4]; int xD4; char pad1[0x184 - 0xD8]; int x184; };
struct SO {
    char pad[0xC]; VT *pvt; char pad0[0x508 - 0x10]; int x508; int x50C; char pad1[0x514 - 0x510]; Z *x514;
    char pad2[0x114C - 0x518]; int x114C;
};
struct VECTOR { qword q; };
extern "C" {
int func_0013B500(void *p, int k);
int func_00156B98(SO *p, SO *pso);
}
static inline M4 *Matrix(SO *p) { VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline float Dot(qword a, qword b)
{
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}

int func_00156B98(SO *p, SO *pso)
{
    switch (p->x508) {
    case 1:
        if (p->x50C)
            break;
        return 1;
    case 2:
        return 1;
    case 8:
        if (p->x50C == 9 || p->x50C == 10)
            return 1;
        break;
    case 0:
    case 13: {
        if (!pso)
            return 0;
        if (func_0013B500(p->x514, 0xB)) {
            if (p->x514->x184)
                return 0;
        } else if (func_0013B500(p->x514, 0x20)) {
            if (p->x514->xD4)
                return 0;
        } else {
            return !p->x514->xD4;
        }
        qword pos = Matrix(p)->r[3];
        VECTOR d;
        d.q = Sub(pos, Matrix(pso)->r[3]);
        float g = Dot(d.q, Matrix(p)->r[0]);
        if (p->x508 == 0 && !p->x114C)
            return 0.0f < g;
        return g < 0.0f;
    }
    }
    return 0;
}
