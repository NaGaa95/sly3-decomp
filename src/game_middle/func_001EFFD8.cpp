// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_AS: gnu-2.9
// Per-frame state action of the character controller: runs the shared updates, then the action of the current
// state (play the state's animation, steer by the move vector, ...), and finishes with func_001F02D8.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct M3 { qword r[3]; };
struct PO { char pad0[8]; float g8; };
struct Ground { char pad0[0x1C]; float g1C; };
struct Gain { char pad0[0x40]; float g40; };
struct P {
    char pad0[0xC]; VTE *vt; char pad10[0x28 - 0x10]; unsigned long flags; char pad30[0x134 - 0x30]; PO *po;
    char pad138[0x1A0 - 0x138]; qword velocity; char pad1B0[0x1C0 - 0x1B0]; M3 basis;
    char pad1F0[0x320 - 0x1F0]; char a320[0x500 - 0x320]; char a500[0xE40 - 0x500]; char aE40[0x110C - 0xE40];
    float time; char pad1110[0x113C - 0x1110]; Gain *gain; char pad1140[0x1144 - 0x1140]; int x1144;
    char pad1148[0x11B4 - 0x1148]; int x11B4; char pad11B8[0x1470 - 0x11B8]; int state; char pad1474[0x1480 - 0x1474];
    char a1480[0x1530 - 0x1480]; char a1530[0x15F0 - 0x1530]; char a15F0[0x1620 - 0x15F0]; qword planar;
    char pad1630[0x16F0 - 0x1630]; int x16F0;
};
extern "C" {
void func_00152A48(P *);
void func_001F0268(P *);
void func_001F0388(P *);
void func_0024E878(P *, float);
void func_00258CF0(void *, float);
void func_00258DA0(void *);
void func_0024E920(P *, int);
qword func_0011FD70(float, float, float);
void func_001C1550(P *, void *, int);
void func_001B9C48(void *);
void func_001B30E8(void *);
void func_001C2B48(void *);
Ground *func_00156AB0(P *);
qword func_0024F278(P *, Ground *, float);
void func_00138B68(Ground *, float);
void func_001F02D8(P *);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline qword MulX(qword a, VU_FLOAT b) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(b.q)); return r; }
static inline qword Len2(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float LaneX(qword q) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q)); return g; }
static inline qword MulT(const M3 *m, qword v)
{
    qword r, a, b, c, one;
    __asm__("vmul.xyzw %2,%5,%8\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%8\n\tvmul.xyzw %4,%7,%8\n\t"
            "vadday.x ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "=j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
extern "C" void func_001EFFD8(P *p)
{
    func_00152A48(p);
    int flagged = (p->flags & (1UL << 56)) != 0;
    if (flagged) {
    func_001F0268(p);
    func_001F0388(p);
    switch (p->state) {
    case 0: {
        VTE *e = &p->vt[110];
        ((void (*)(void *))e->pfn)((char *)p + e->d);
        break;
    }
    case 1: {
        void *s = p->a1480;
        func_0024E878(p, p->time);
        func_00258CF0(s, 1.0f);
        func_00258DA0(s);
        break;
    }
    case 2: {
        void *s = p->a1530;
        func_0024E878(p, p->time);
        func_00258CF0(s, p->po->g8);
        func_00258DA0(s);
        break;
    }
    case 3:
        func_0024E920(p, p->x11B4);
        break;
    case 4: {
        func_0024E920(p, p->x11B4);
        float g = p->po->g8 * LaneX(Len2(p->planar)) * p->gain->g40;
        qword v = func_0011FD70(p->time + 3.14159265f, g, 0.0f);
        p->velocity = v;
        p->velocity = MulT(&p->basis, v);
        p->x1144 = -1;
        func_001C1550(p, p->a15F0, p->x16F0);
        break;
    }
    case 5:
        func_001B9C48(p->a320);
        break;
    case 6:
        func_001B30E8(p->a500);
        break;
    case 7:
        func_001C2B48(p->aE40);
        break;
    case 8:
        break;
    case 9: {
        Ground *g = func_00156AB0(p);
        p->velocity = MulX(func_0024F278(p, g, g->g1C), VU_FLOAT(-1.0f));
        break;
    }
    case 10: {
        Ground *g = func_00156AB0(p);
        p->velocity = MulX(func_0024F278(p, g, g->g1C), VU_FLOAT(-1.0f));
        func_00138B68(g, p->po->g8);
        func_0024E878(p, p->time);
        break;
    }
    }
    func_001F02D8(p);
    }
}
