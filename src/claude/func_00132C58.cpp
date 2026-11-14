// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00132C58: state setter (xD0); state 1 picks a launch per xCC (jump table 0x31F790, FLT_MAX literal 0x31F780).
// Matching notes: dd/vv/w/w2/t are plain qwords live across calls, so reload spills them in declaration order
// (0x20..0x60); VU_FLOAT temps share slot 0; GetZ/case-4 reads are reloads of vv's spill slot. The sqrt asm is
// volatile + earlyclobber. Store pairs to xE0/xE4 are written in reverse order (gcc emits the last first).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR3 {
    qword q;
    VU_VECTOR3(float x, float y, float z)
    {
        qword t;
        __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    }
};
struct VTE { short delta; short pad; void *(*method)(void *); };
struct CH { char pad[0x70]; qword v70; char pad80[0xA0 - 0x80]; int nA0; };
struct X {
    char pad[0xC]; struct VTE *vt; char pad10[0x48 - 0x10]; struct CH *p48; char pad4C[0x120 - 0x4C];
    unsigned long flags; char pad128[0x134 - 0x128]; float *pg134; char pad138[0x1BC - 0x138]; float g1BC;
};
struct PA { char pad[0x14]; void *p14; char pad18[0x40 - 0x18]; float g40; };
struct PB { char pad[0x48]; float g48; float g4C; float g50; float g54; char pad58[0x60 - 0x58]; qword v60;
    char pad70[0x7C - 0x70]; float g7C; float g80; };
struct PP { int x0; struct PB *pb; struct PA *pa; };
struct P {
    char pad[0x10]; struct X *p10; char pad14[0x40 - 0x14]; struct PP *p40; char pad44[0x90 - 0x44]; qword v90;
    char padA0[0xB0 - 0xA0]; qword vB0; void *pC0; int xC4; char padC8[0xCC - 0xC8]; int xCC; int state; float gD4;
    char padD8[0xE0 - 0xD8]; float gE0; float gE4; int xE8; char padEC[0xF0 - 0xEC]; float gF0; char padF4[0xF8 - 0xF4];
    float gF8; float gFC; int x100;
};
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern float D_003457A0;
extern float D_003457A4;
extern float D_003457A8;
extern float D_003457AC;
extern char D_00475480[];
float *func_00136880(void *p, int key);
void func_00137D08(void *p, float a, float b, int c, int d);
void func_00256DF0(struct X *px);
void func_00259D10(void *pv);
void func_00259D50(void *pv);
int func_0013B500(void *p, int kind);
float func_001B83F0(float a, float b, float c, float d, qword delta, qword axis);
qword func_0028E910(int a, int n, qword q);
qword func_0028E990(int a, int n, qword q);
int func_00130348(struct X *px, struct CH *pch, int mode, float t, qword a, qword b);
void func_0013CD10(void *pv, struct X *px);
float func_00250418(struct X *px, float a, float b);
float func_002504B0(struct X *px, float a, float b, float c);
qword func_0011FD70(float a, float b, float c);
void func_00133510(struct P *p, int n);
qword func_00212480(qword a, qword b, qword c, float g);
void func_0023ED58(struct X *px, qword v);
void func_00256EB0(struct X *px, void *pv, int n);
void func_001328B0(struct P *p);
void func_00131610(struct P *p, int n);
}
#define VCALL(T, po, n) (((T (*)(void *))(po)->vt[n].method)((char *)(po) + (po)->vt[n].delta))
#define VCALLV(po, n, v) (((void (*)(void *, qword))(po)->vt[n].method)((char *)(po) + (po)->vt[n].delta, v))
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Scale(qword a, VU_FLOAT s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
static inline qword Blend(qword a, VU_FLOAT s, qword b, VU_FLOAT t)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(s.q), "j"(b), "j"(t.q));
    return r;
}
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline float GMax(float a, float b) { return a > b ? a : b; }
static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(g)); return r; }

extern "C" void func_00132C58(struct P *p, int n);
void func_00132C58(struct P *p, int n)
{
    if (n == p->state)
        return;
    p->state = n;
    struct PP *pp = p->p40;
    struct PA *pa = 0;
    struct PB *pb = 0;
    p->gD4 = g_clock.t;
    if (pp) {
        pa = pp->pa;
        pb = pp->pb;
    }
    switch (n) {
    case 1: {
        func_00137D08(pa, *func_00136880(pa->p14, 0x3D), 1.0f, 0, 0);
        func_00256DF0(p->p10);
        func_00259D10((char *)p->p10 + 0x4B0);
        p->x100 = 1;
        float r = pa->g40;
        qword pos = p->vB0;
        qword tgt = p->p10->p48->v70;
        qword dd = Sub(pos, tgt);
        qword vv = Scale(pb->v60, VU_FLOAT(r * r));
        register qword goal asm("$18") = vv; /* the one register pin: goal lives in $s2 (else regclass spills it) */
        switch (p->xCC) {
        case 1:
        case 2: {
            float a, b, c, e;
            if (p->pC0 && (func_0013B500(p->pC0, 0x26) || func_0013B500(p->pC0, 10))) {
                a = 1250.0f;
                c = 1.1f;
                b = 0.0f;
                e = 50.0f;
            } else if (p->xCC == 2) {
                a = 1500.0f;
                c = 1.33f;
                b = -1500.0f;
                e = -1.33f;
            } else {
                a = 1250.0f;
                c = 1.1f;
                b = -1250.0f;
                e = -1.1f;
            }
            float g = func_001B83F0(a, b, c, e, dd, vv);
            qword w, w2;
            w = Blend(dd, VU_FLOAT(1.0f / g), vv, VU_FLOAT(g * -0.5f));
            VCALLV(p->p10, 40, w);
            p->gE0 = g_clock.t + g;
            p->gE4 = p->gE0 - pb->g54 / r;
            w2 = AddScaled(w, vv, VU_FLOAT(g));
            qword r1 = func_0028E910(0, p->p10->p48->nA0, p->vB0);
            qword r2 = func_0028E990(0, p->p10->p48->nA0, w2);
            p->xE8 = func_00130348(p->p10, p->p10->p48, 5, p->gE0, r1, r2);
            p->p10->flags |= 0x400000000000000UL;
            func_0013CD10(D_00475480, p->p10);
            break;
        }
        case 0:
        case 7: {
            float g = pb->g50 / r;
            if (p->xCC == 0)
                g *= p->gF0;
            qword w0 = Blend(dd, VU_FLOAT(1.0f / g), vv, VU_FLOAT(g * -0.5f));
            VCALLV(p->p10, 40, w0);
            p->gE0 = g_clock.t + g;
            p->gE4 = p->gE0 - pb->g54 / r;
            break;
        }
        case 3:
        case 5: {
            float z = GetZ(vv);
            U s;
            s.q = VCALL(qword, p->p10, 38);
            s.f[2] = func_00250418(p->p10, pb->g7C, z);
            VCALLV(p->p10, 40, s.q);
            float t = SqrtF(pb->g7C * -8.0f / z);
            p->gF8 = pb->g80 / t;
            p->gE4 = 3.402823466e+38f;
            p->gE0 = 3.402823466e+38f;
            break;
        }
        case 9: {
            U s;
            float *pg = p->p10->pg134;
            s.q = VCALL(qword, p->p10, 38);
            s.f[2] = GMax(800.0f, s.f[2]);
            if (pg[2] < 0.2f) {
                qword t;
                t = s.q;
                qword off = func_0011FD70(p->p10->g1BC, 100.0f, 0.0f);
                s.q = Add(t, off);
                func_00133510(p, 3);
            }
            VCALLV(p->p10, 40, s.q);
            goal = VU_VECTOR3(0.0f, 0.0f, -2275.0f).q;
            p->gF8 = D_003457A0 * 0.6f;
            p->gE4 = 3.402823466e+38f;
            p->gE0 = 3.402823466e+38f;
            break;
        }
        case 8: {
            float z = GetZ(vv);
            float g = func_002504B0(p->p10, D_003457A8, D_003457AC, z);
            U s;
            s.q = VCALL(qword, p->p10, 38);
            s.f[2] = g;
            VCALLV(p->p10, 40, s.q);
            float t = SqrtF(z * -0.00043956045f);
            p->gE4 = 3.402823466e+38f;
            p->gE0 = 3.402823466e+38f;
            p->gF8 = t * D_003457A4;
            break;
        }
        case 4: {
            U s;
            s.q = func_00212480(tgt, pos, vv, p->gFC);
            VCALLV(p->p10, 40, s.q);
        }
        case 6:
            p->gE4 = 3.402823466e+38f;
            p->gE0 = 3.402823466e+38f;
            break;
        }
        func_0023ED58(p->p10, goal);
        break;
    }
    case 2:
        func_00137D08(pa, pb->g48, 1.0f, 0, 0);
        break;
    case 3:
        func_00137D08(pa, pb->g4C, 1.0f, 0, 0);
        if (p->pC0)
            func_00256EB0(p->p10, p->pC0, p->xC4);
        break;
    case 4:
        func_001328B0(p);
        func_0023ED58(p->p10, p->v90);
        if (p->x100) {
            p->x100 = 0;
            func_00259D50((char *)p->p10 + 0x4B0);
        }
        func_00131610(p, 1);
        break;
    }
}
