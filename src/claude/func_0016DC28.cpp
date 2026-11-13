// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct M4 { qword r[4]; };
struct A;
struct VT {
    char pad[0x120];
    short d120; short p122; M4 *(*pfn120)(void *);
    int pad128[2];
    short d130; short p132; qword (*pfn130)(void *);
    int pad138[2];
    short d140; short p142; void (*pfn140)(void *, qword);
};
struct CLOCK { float t; float dt; };
struct C { char pad[0x1C]; float g1C; };
struct B { char pad[0x90]; C *p90; };
struct A { char pad[0xC]; VT *vt; char pad2[0x48 - 0x10]; B *p48; char pad3[0x218 - 0x4C]; int n218; };
struct Y { char pad[0x50]; void *p50; };
struct X { char pad[0x1AA4]; Y *p1AA4; };
struct S { char pad[0x10]; A *p10; char pad2[0x50 - 0x14]; int n50; float g54; int pad3; X *p5C; int pad4; C *p64; };
struct OUT { char pad[0x30]; qword v; };
extern "C" {
extern CLOCK g_clock;
void func_001317B0(S *p);
void func_0016E118(S *p, int n);
void func_0016DB68(S *p);
void func_0028F680(void *a, void *b, OUT *pm, void *other, float g);
void func_0016DC28(S *p);
}
static inline M4 *Matrix(A *a) { VT *v = a->vt; return v->pfn120((char *)a + v->d120); }
static inline qword Velocity(A *a) { VT *v = a->vt; return v->pfn130((char *)a + v->d130); }
static inline void SetVelocity(A *a, qword q) { VT *v = a->vt; v->pfn140((char *)a + v->d140, q); }
static inline qword Load(qword *p) { qword r; __asm__("lqc2 %0, %1" : "=j"(r) : "m"(*p)); return r; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
void func_0016DC28(S *p)
{
    int s;
    func_001317B0(p);
    qword v = Velocity(p->p10);
    do {
        s = p->n50;
        switch (s) {
        case 0:
        case 1:
            if (s == 1 && p->p10->n218) {
                func_0016E118(p, 3);
            } else if (p->p10->p48->p90 != p->p64 || p->p10->p48->p90->g1C < g_clock.t) {
                func_0016E118(p, 2);
            } else if (GetZ(v) < 0.0f && s == 0) {
                func_0016E118(p, 1);
            } else {
                func_0016DB68(p);
            }
            break;
        case 2:
            if (p->p10->n218) func_0016E118(p, 3);
            break;
        case 3:
            break;
        case 4:
        case 5: {
            OUT out;
            U a, b, t, vel, ud;
            CLOCK *clock = &g_clock;
            a.q = Matrix(p->p10)->r[3];
            b.q = Velocity(p->p10);
            func_0028F680(p->p5C->p1AA4->p50, 0, &out, 0, clock->dt);
            t.q = out.v;
            t.f[2] += 35.0f;
            qword tq = t.q;
            qword *pm = &Matrix(p->p10)->r[3];
            __asm__ __volatile__(""); /* barrier: tq reload must not depend on its spill store directly */
            qword c = Load(pm);
            register int dtb asm("$16") = *(int *)&clock->dt; /* register pin: target keeps dt bits in s0 */
            qword u, w;
            int four = 4;
            __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(u) : "r"(dtb), "r"(four), "r"(four), "j"(tq)); /* "j"(tq): tq reload before the qmtc2 */
            ud.q = u;
            qword dp;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(dp) : "j"(tq), "j"(c), "j"(c));
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(w) : "j"(u), "j"(dp));
            vel.q = w;
            if (p->n50 == four) {
                if (a.f[2] < t.f[2] || 0.25f < g_clock.t - p->g54) {
                    func_0016E118(p, 5);
                    break;
                }
                vel.f[2] = b.f[2];
            }
            SetVelocity(p->p10, vel.q);
            break;
        }
        case 6:
            if (p->p10->n218) func_0016E118(p, -1);
            break;
        }
    } while (p->n50 != s);
}
