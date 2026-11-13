// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 counterpart: /home/claude/sly2-decomp src/hand/func_0017B9C0.cpp (JOBB2::Choose), rewritten without asm bodies.
// origin, bestPoint and candidate are plain qwords that reload spills (VU class, slots 0x10/0x20/0x30 in declaration
// order), so their uses reload with lqc2/lq and the GPR value of candidate feeds the qmtc2 reload directly.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct P {
    char pad[0xC]; VT *pvt; char pad10[0x28 - 0x10];
    unsigned long flags; char pad30[0x1104 - 0x30];
    int count; P *choices[4]; int nearCount; P *near[1];
};
struct C { char pad[0x10]; P *actor; char pad14[0x38 - 0x14]; P *preferred; P *near; P *selected; float time; };
struct RANGE { float lo, hi; };
struct POLY { float a, b, c; };
struct CLOCK { float time, dt; };
extern "C" {
extern CLOCK g_clock;
extern RANGE D_00322260;
extern POLY D_00322270, D_00322280;
extern RANGE D_00322290;
extern float D_00322298;
float func_0011E940(float lo, float hi);
void func_00120938(qword a, qword b, qword c, qword *pv, float *pt, float *pd);
void func_001A5138(C *p);
}
static inline M4 *Matrix(P *p) { VTE *e = &p->pvt->e120; return e->pfn((char *)p + e->d); }
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Length(qword v)
{
    qword d = v, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return X(d);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Load(qword *p) { qword r; __asm__("lqc2 %0, %1" : "=j"(r) : "m"(*p)); return r; }
static inline qword To(qword a) { qword r; __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(a)); return r; }
static inline qword Zero() { qword r; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(r)); return r; }
void func_001A5138(C *p)
{
    float t, d, t2, d2;
    qword origin, bestPoint, candidate;
    float now = g_clock.time;
    if (now < p->time) return;
    bestPoint = Zero();
    int i = 0;
    P *best = 0;
    p->time = now + func_0011E940(D_00322260.lo, D_00322260.hi);
    origin = Matrix(p->actor)->r[3];
    float bestCost = D_00322298;
    P *actor = p->actor;
    if (actor->count > 0) {
        do {
            P *choice = actor->choices[i];
            if ((int)(choice->flags >> 56) & 1) {
                candidate = Matrix(choice)->r[3];
                float cost = Length(Sub(origin, candidate));
                if (choice == p->preferred) cost = D_00322270.a + cost * (D_00322270.b + cost * D_00322270.c);
                for (int j = 0; j < p->actor->nearCount; j++) {
                    func_00120938(Matrix(p->actor->near[j])->r[3], origin, candidate, 0, &t, &d);
                    if (t < 0.0f) continue;
                    if (t > 1.0f) continue;
                    float pen = D_00322280.a + d * (D_00322280.b + d * D_00322280.c);
                    float lo = D_00322290.lo, hi = D_00322290.hi;
                    if (pen < lo) pen = lo;
                    else if (hi < pen) pen = hi;
                    cost += pen;
                }
                if (cost < bestCost) { bestCost = cost; best = choice; bestPoint = candidate; }
            }
            i++;
            actor = p->actor;
        } while (i < actor->count);
    }
    p->preferred = best;
    P *nearest = 0;
    float distance = 800.0f;
    for (int k = 0; k < p->actor->nearCount; k++) {
        P *choice = p->actor->near[k];
        qword position = Load(&Matrix(choice)->r[3]);
        float f = Length(Sub(position, origin));
        if (distance < f) continue;
        if (best) {
            func_00120938(To(position), origin, bestPoint, 0, &t2, &d2);
            if (t2 < 0.0f) continue;
            if (t2 > 1.0f) continue;
            if (d2 > 500.0f) continue;
        }
        nearest = choice;
        distance = f;
    }
    p->near = nearest;
    p->selected = nearest ? nearest : p->preferred;
}
