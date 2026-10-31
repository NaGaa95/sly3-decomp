// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; };
struct SO { char pad[0xC]; VT *pvt; char pad1[0x2F0 - 0x10]; int x2F0; };
struct P { char pad[0xC]; VT *pvt; char pad1[0x1108 - 0x10]; void *p1108; char pad2[0x11BC - 0x110C]; int x11BC; SO *p11C0; int x11C4; };
extern "C" {
int func_00173428(void *p);
int func_0013B500(void *object, int kind);
int func_00153290(P *p, int fFar);
}
static inline M4 *Matrix(void *pv) { SO *p = (SO *)pv; VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline bool FBusy(P *p) { return p->p1108 && func_00173428(p->p1108); }
static inline float LenXY(qword v)
{
    qword d;
    float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
int func_00153290(P *p, int fFar)
{
    if (p->x11C4 != 4)
        return 0;
    if (p->x11BC == 3)
        return 0;
    if (FBusy(p))
        return 0;
    SO *pso = p->p11C0;
    float r = 1000.0f;
    if (func_0013B500(pso, 0x3A) && (unsigned)(pso->x2F0 - 1) < 2)
        r = 1700.0f;
    float zMin = -750.0f;
    float zMax = 750.0f;
    if (fFar) {
        r += 500.0f;
        zMin = -1250.0f;
        zMax = 1250.0f;
    }
    U d;
    qword dq;
    qword a = Matrix(p->p11C0)->r[3];
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(dq) : "j"(a), "j"(Matrix(p)->r[3]));
    d.q = dq;
    int res = 0;
    if (LenXY(dq) < r && zMin < d.f[2] && d.f[2] < zMax)
        res = 1;
    return res;
}
