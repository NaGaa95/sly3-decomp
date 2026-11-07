// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002403F0 (agent A76, from A53/A67 drafts): particle-style Verlet step over p->n88 points (pos += vel*dt,
// prev blended with dt*0.5), flags motion when |prev - new| > 1, stores sqrt of the max squared length in p->f8.
// Keys: volatile sqrt.s inline (otherwise sched1 moves 'a0 = p' above the p->f8 store, p conflicts with a0 and
// lands in a1), and the init order maxv / prev / pos / vel / moved. No pins.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct Q { int n0; qword *pos; qword *vel; };
struct P { char pad[8]; float f8; char padC[0x14 - 0xC]; Q *q; char pad18[0x88 - 0x18]; int n88; qword *prev; char pad90[0xBC - 0x90]; int nBC; int nC0; };
extern "C" void func_00240538(P *);
static inline qword AddScaled(qword a, qword v, VU_FLOAT k)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(k.q));
    return r;
}
static inline qword AddScaled2(qword a, qword b, qword c, VU_FLOAT k)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %4x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(b), "j"(c), "j"(k.q));
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Dot(qword a)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "0"(a));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
static inline float DotC(qword a)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(a));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
static inline float SqrtF(float f) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(f)); return r; }
extern "C" void func_002403F0(P *p, float dt)
{
    Q *q = p->q;
    if (q->n0)
        return;
    {
        float maxv = 0.0f;
        qword *prev = p->prev;
        qword *pos = q->pos;
        qword *vel = q->vel;
        int moved = 0;
        int i;
        for (i = 0; i < p->n88; i++) {
            qword P0 = pos[i];
            qword R0 = prev[i];
            qword np = AddScaled(P0, vel[i], VU_FLOAT(dt));
            qword nprev = AddScaled2(R0, P0, np, VU_FLOAT(dt * 0.5f));
            float len2;
            if (!moved && 1.0f < Dot(Sub(R0, nprev)))
                moved = 1;
            len2 = DotC(nprev);
            prev[i] = nprev;
            pos[i] = np;
            if (maxv < len2)
                maxv = len2;
        }
        if (moved) {
            p->nBC = -1;
            p->nC0 = -1;
        }
        p->f8 = SqrtF(maxv);
        func_00240538(p);
    }
}
