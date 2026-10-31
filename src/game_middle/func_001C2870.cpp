// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Push the actor's velocity against its reference frame depending on the movement state
// (same routine as Sly 2 func_001A1148; offsets and callees differ in Sly 3).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct VE { short d; short pad; void *pfn; };
struct X { char pad[0x80]; qword v80; };
struct O {
    char pad[0xC]; struct VE *vt; char pad1[0xD8 - 0x10]; struct X *xD8; char pad2[0x1A8 - 0xDC]; float f1A8;
    void Set(qword v) __asm__("func_00244828");
    void Negate(U &u);
};
struct P { struct O *o; int state; };
struct CLOCK { float t, dt; };
extern "C" {
extern qword D_00317560;
extern float D_003235E0[];
extern struct CLOCK g_clock;
void func_0023F180(struct O *p, qword a, int n, qword b, float *c);
}
static inline qword Broadcast(float g) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(g)); return q; }
static inline qword Scale(qword a, qword b) { qword q; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(q) : "j"(a), "j"(b)); return q; }
static inline float GetZ(qword v) { float g; __asm__("pextuw %0,$0,%1" : "=r"(g) : "r"(v)); return g; }
inline void O::Negate(U &u) { qword v = xD8->v80; qword k = Broadcast(-1.0f); u.q = k; Set(Scale(v, k)); }
extern "C" void func_001C2870(struct P *p)
{
    U u, v, u2;
    float zero;
    switch (p->state) {
    case 1: case 2:
        p->o->Negate(u);
        func_0023F180(p->o, D_00317560, 0, D_00317560, D_003235E0);
        break;
    case 5: case 12:
        p->o->Negate(u2);
        v.i[2] = 0; v.i[1] = 0; v.i[0] = 0;
        zero = v.f[2];
        if (p->o->f1A8 != zero)
            v.f[2] = GetZ(((qword (*)(void *))p->o->vt[38].pfn)((char *)p->o + p->o->vt[38].d));
        func_0023F180(p->o, D_00317560, 0, v.q, D_003235E0);
        if (p->o->f1A8 != zero) {
            u.f[2] = zero; u.f[1] = zero; u.f[0] = zero;
            u.f[2] = (-p->o->f1A8 - v.f[2]) / g_clock.dt;
            p->o->Set(u.q);
        }
        break;
    }
}
