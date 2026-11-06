// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct P *(*pf)(void *); };
struct Y { char pad[0xC]; float fC; float f10; float f14; };
struct X { int a[3]; struct VTE *vt; char pad[0x134 - 0x10]; struct Y *x134; };
struct Q { char pad[0x48]; struct X *x48; float f4C; };
struct S { void *x0; char pad[0x1C]; struct Q *x20; char pad2[0xC]; qword q30; };
struct SMP;
extern struct SMP D_003292C0;
extern struct { float dt; } D_0036BB9C;
void func_00169E78(struct S *p);
float func_002A3EE8(float y, float x);
float func_0011E3B8(float g);
qword func_0011FD70(float a, float r, float z);
qword func_00120C80(qword cur, qword target, float dt, struct SMP *psmp, qword *pv);
void func_00166E48(void *p, qword a, qword b, float f, float g);
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
void func_00279AF8(struct S *p)
{
    float zero;
    qword v;
    struct X *x;
    struct Y *y;
    func_00169E78(p);
    zero = 0.0f;
    __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(v));
    x = p->x20->x48;
    y = x->x134;
    if (zero < y->f14)
        v = func_0011FD70(func_0011E3B8(func_002A3EE8(-y->fC, y->f10)), p->x20->f4C * (y->f14 * 0.5f), zero);
    p->q30 = func_00120C80(p->q30, v, D_0036BB9C.dt, &D_003292C0, 0);
    {
        qword c = Add(x->vt[36].pf((char *)x + x->vt[36].d)->q30, p->q30);
        union { qword q; float f[4]; } u;
        u.q = Make(zero, zero, p->x20->f4C);
        func_00166E48(p->x0, Add(c, u.q), c, zero, zero);
    }
}
