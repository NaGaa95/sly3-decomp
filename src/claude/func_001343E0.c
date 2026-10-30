// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* state 4: push the actor toward (0, 0, 2000) from its slot-38 vector over one frame, limited by func_001205F0 */
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct A { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x10]; struct A *pa; char pad2[0x30 - 0x14]; int x30; };
struct CLOCK { float t; int dt; };
extern struct CLOCK g_clock;
extern qword D_00317550;
int func_002389B8(struct S *p);
qword func_001205F0(qword v, float g);
void func_00244828(struct A *pa, qword v);
static __inline__ qword Qmtc2(int g)
{
    qword v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v) : "r"(g));
    return v;
}
static __inline__ qword QwMulX(qword a, qword g)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(g));
    return r;
}
static __inline__ qword QwSub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static __inline__ qword QwDiv(qword a, qword g)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(a), "j"(g));
    return r;
}
int func_001343E0(struct S *p)
{
    struct A *pa;
    qword v, d;
    union { qword qw; float f[4]; } u;
    union { float f; int n; } g;
    if (p->x30 == 4) {
        pa = p->pa;
        v = ((qword (*)(void *))pa->vt[38].pfn)((char *)pa + pa->vt[38].d);
        g.f = 2000.0f;
        u.qw = Qmtc2(g.n);
        d = QwSub(QwMulX(D_00317550, u.qw), v);
        u.qw = Qmtc2(g_clock.dt);
        func_00244828(p->pa, func_001205F0(QwDiv(d, u.qw), 20000.0f));
        return 1;
    }
    return func_002389B8(p);
}
