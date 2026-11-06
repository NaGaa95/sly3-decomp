// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; struct VTE e120; };
struct PO { char pad[0xC]; struct VT *pvt; };
struct P { struct PO *p0; float g4; int pad[2]; qword pos; int d20; float t24; int f28; };
extern struct CLOCK { float t; } g_clock;

static __inline__ struct M4 *Matrix(struct PO *p)
{
    struct VTE *e = &p->pvt->e120;
    return ((struct M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
static __inline__ qword Dist(qword a, qword b)
{
    qword d, t;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return d;
}
static __inline__ float GDist(qword a, qword b) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(Dist(a, b))); return g; }
static __inline__ int IDist(qword a, qword b) { register int n asm("$3"); /* register pin: target keeps the distance bits in v1 */ __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(Dist(a, b))); return n; }

void func_001572A0(struct P *p, qword pos)
{
    if (p->f28 == 0) {
        int fNear = 0;
        if (GDist(p->pos, pos) < 10.0f && p->t24 != 3.40282347e+38f)
            fNear = 1;
        if (fNear)
            return;
        p->pos = pos;
        p->d20 = IDist(Matrix(p->p0)->r[3], p->pos);
        p->t24 = g_clock.t + p->g4;
    }
}
