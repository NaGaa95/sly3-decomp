// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002734E8: actor state setter (exit actions per old state, facing/velocity reset, per-state anim + flags, then play anim via func_00137588).
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct O {
    int a[3]; VTE *vt; char pad10[0x130 - 0x10]; int x130; int pad134[2]; int x13C; char pad140[0x1A0 - 0x140];
    int x1A0, x1A4, x1A8; char pad1AC[0x1B8 - 0x1AC]; int x1B8; char pad1BC[0x1F0 - 0x1BC]; qword x1F0;
};
struct O2 { char pad[0x134]; int x134; char pad138[0x144 - 0x138]; int x144; };
struct P {
    O *x0; int st; float t; int padC; O *x10; char pad14[0x40 - 0x14]; float x40; int pad44[2]; float x4C;
    int pad50[2]; int x58, x5C, x60, x64; char pad68[0x98 - 0x68]; int x98, x9C, xA0; char padA4[0xBC - 0xA4];
    int xBC, xC0, xC4, xC8; qword xD0; qword padE0; qword xF0; char pad100[0x134 - 0x100]; int pad134; int x138; int x13C;
    float x140, x144; O *x148; float x14C;
};
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern char D_00475480[];
extern qword D_00317560;
int func_0013B500(O *, int);
void func_002091B0(void *, O *);
void func_001F4B00(void *, int, O *);
void func_0013CD10(void *, void *);
float atan2f(float, float);
void func_0024E878(O *, float);
void func_0024E8E8(O *, qword);
void func_00273278(P *);
void func_00148938(int);
qword func_001C9428(O *, O *, qword);
void func_00272628(P *, int);
void func_00154460(O *, int);
void func_0023AC58(void *);
int func_00137588(int, O *, float, float, int, void *);
void func_002734E8(P *p, int st);
}
static inline float *PosV(O *o) { VTE *v = &o->vt[36]; return (float *)v->pf((char *)o + v->d); }
static inline qword Pos(O *o) { return *(qword *)((char *)PosV(o) + 0x30); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }

extern "C" void func_002734E8(P *p, int st)
{
    if (st == p->st)
        return;
    switch (p->st) {
    case -1:
        if (!func_0013B500(p->x10, 0x33))
            func_002091B0((char *)p->x0 + 0x940, p->x10);
        if (func_0013B500(p->x10, 0x71)) {
            VTE *e = &p->x10->vt[80];
            e->pf((char *)p->x10 + e->d, 0);
        }
        {
            O *o = p->x0;
            int *pa = &o->x1A0;
            pa[2] = 0;
            pa[1] = 0;
            pa[0] = 0;
        }
        break;
    case 3:
        if (st != 4)
            func_001F4B00(D_00475480, p->x0->x130, p->x10);
        break;
    }
    int stPrev = p->st;
    p->st = st;
    p->t = g_clock.t;
    func_0013CD10(D_00475480, p->x0);
    switch (p->st) {
    case -1: {
        float *pv = PosV(p->x0);
        func_0024E878(p->x0, atan2f(pv[1], pv[0]));
        p->x0->x1B8 = 0;
        break;
    }
    case 7:
        if (!p->xC4) {
            qword a = p->xF0;
            func_0024E8E8(p->x0, Sub(a, Pos(p->x0)));
        } else {
            float *pv = PosV(p->x0);
            func_0024E878(p->x0, atan2f(pv[1], pv[0]));
        }
        p->x0->x1B8 = 0;
        break;
    default:
        p->x0->x1F0 = D_00317560;
        p->x0->x1B8 = 1;
        break;
    }
    int anim = 0;
    int k = 1;
    switch (p->st) {
    case -1:
        func_00273278(p);
        p->x10 = 0;
        p->xC0 = 0;
        p->xC4 = 0;
        return;
    case 0:
        if (stPrev != 1 && stPrev != 2) {
            p->x4C = 0.5f;
            p->x40 = 0.5f;
            func_00148938(p->x58);
        }
        anim = p->x58;
        k = 9;
        break;
    case 1:
        anim = p->x5C;
        break;
    case 2:
        anim = p->x60;
        break;
    case 3:
        anim = p->xC0;
        if (!anim)
            anim = p->x64;
        func_001F4B00(D_00475480, p->x10->x130, p->x0);
        p->xC8 = 0;
        break;
    case 4: {
        float z = 0.0f;
        p->x13C = 0;
        p->x144 = z;
        p->x140 = z;
        O2 *o = (O2 *)p->x148;
        if (o) {
            o->x134 = 1;
            ((O2 *)p->x148)->x144 = 0;
            VTE *e = &p->x148->vt[8];
            e->pf((char *)p->x148 + e->d);
        }
        if (stPrev != 5 && stPrev != 6) {
            p->x14C = z;
            p->xF0 = func_001C9428(p->x0, 0, p->xD0);
            func_00272628(p, 0);
        }
        anim = p->x98;
        k = 9;
        p->x138 = 0;
        break;
    }
    case 5:
        anim = p->x9C;
        break;
    case 6:
        anim = p->xA0;
        break;
    case 7:
        anim = p->xC4;
        if (!anim)
            anim = p->xBC;
        if (func_0013B500(p->x10, 0x71))
            func_00154460(p->x0, p->x10->x13C);
        break;
    }
    func_0023AC58((char *)p->x0 + 0x1140);
    func_00137588(anim, p->x0, 0.0f, 1.0f, k, (char *)p->x0 + 0x113C);
    {
        VTE *e = &p->x0->vt[101];
        e->pf((char *)p->x0 + e->d);
    }
    func_0013CD10(D_00475480, p->x0);
}
