// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00132438: steering update for states 2-9 when xD0 is 1 or 2 (jump table at 0x31F760).
// Matching notes: v is a spilled qword (0x40); w/u/t are memory unions; VU_FLOAT by value (homes 0x10/0x30);
// the vmulx helper carries a "memory" clobber so the VU_FLOAT(-1) home store stays ahead of the transform;
// FV() holds the one register pin ($a0) for the normalize-test readback.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { qword r[3]; } M3;
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VTE { short delta; short pad; void *(*method)(void *); };
struct OBJ { char pad[0xC]; struct VTE *vt; };
struct XY { float x, y; };
struct X {
    char pad[0xC]; struct VTE *vt; char pad10[0x134 - 0x10]; float *pg134; char pad138[0x1A0 - 0x138];
    qword v1A0; char pad1B0[0x1BC - 0x1B0]; float g1BC; M3 m1C0; char pad1F0[0x11CC - 0x1F0]; int x11CC;
};
struct SELF {
    char pad[0x10]; struct X *p10; char pad14[0x38 - 0x14]; struct OBJ *p38; char pad3C[0xA0 - 0x3C]; qword qA0;
    char padB0[0xCC - 0xB0]; int xCC; int xD0; char padD4[0xE8 - 0xD4]; int xE8; int xEC; char padF0[4]; float gF4; float gF8;
};
extern "C" {
extern qword D_00317530;
float func_001205C8(qword v);
void func_0024E878(struct X *px, float g);
void *func_001F4A80(struct X *px);
float func_00168108(void *pv, float a, float b, float c);
void func_00257D78(struct X *px, int n);
float atan2f(float y, float x);
qword func_0011FD70(float a, float b, float c);
float func_0011FE60(qword a, qword b, int n, qword *pout);
qword func_001205F0(qword v, float g);
void func_00132930(struct SELF *p, qword v);
}
#define VCALL(T, po, n) (((T (*)(void *))(po)->vt[n].method)((char *)(po) + (po)->vt[n].delta))
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword LenXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline float FV(qword q) { register qword t __asm__("$4"); /* the one register pin: $a0 */ __asm__("qmfc2.ni %0, %1" : "=r"(t) : "j"(q)); float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(t)); return g; }
static inline qword DivQ(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(l));
    return r;
}
static inline qword MulT(const M3 *m, qword v)
{
    qword r, a, b, c, one;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
            "vadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
static inline qword MulS(VU_FLOAT b, qword a) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(b.q), "j"(a) : "memory"); return r; }
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}

extern "C" void func_00132438(struct SELF *p);
void func_00132438(struct SELF *p)
{
    if (p->xD0 != 1 && p->xD0 != 2)
        return;
    switch (p->xCC) {
    case 3: case 4: case 5: case 6: case 8: case 9: {
        U w;
        qword v;
        float yaw, g, gs;
        float *pg;
        yaw = p->p10->g1BC;
        v = VCALL(qword, p->p10, 38);
        if (200.0f < F(LenXY(v)))
            yaw = func_001205C8(v);
        func_0024E878(p->p10, yaw);
        void *pr = func_001F4A80(p->p10);
        pg = p->p10->pg134;
        g = func_00168108(pr, pg[0], pg[1], yaw);
        gs = pg[2];
        if (p->xCC == 5) {
            struct X *px = p->p10;
            int n = px->x11CC;
            if ((unsigned)n < 2 || n == 3)
                gs = 1.0f;
            if (n == 3) {
                func_00257D78(px, 1);
                struct XY *pxy = VCALL(struct XY *, p->p10, 36);
                yaw = atan2f(pxy->y, pxy->x);
                func_0024E878(p->p10, yaw);
                g = yaw;
            }
        }
        w.q = func_0011FD70(g, gs * p->gF4 * p->gF8, 0.0f);
        {
            struct X *px = p->p10;
            px->v1A0 = MulS(VU_FLOAT(-1.0f), MulT(&px->m1C0, w.q));
        }
        if (p->xEC == 0 && p->xCC != 4) {
            U u;
            U t;
            qword l;
            float len, f;
            u.q = v;
            u.f[2] = 0.0f;
            const qword *pd = &D_00317530;
            qword vv;
            __asm__("qmtc2.ni %1, %0" : "=j"(vv) : "r"(u.q));
            l = Len(vv);
            if (FV(l) < 1e-4f)
                u.q = *pd;
            else
                u.q = DivQ(vv, l);
            len = F(l);
            f = func_0011FE60(w.q, u.q, 0, &t.q);
            if (f < len && len * -0.25f < f)
            {
            w.q = AddScaled(t.q, u.q, VU_FLOAT(len));
            w.q = func_001205F0(w.q, p->gF8);
        }
        }
        p->qA0 = w.q;
        break;
    }
    case 2:
        if (p->xE8 && p->p38) {
            struct OBJ *po = p->p38;
            func_00132930(p, ((U *)((char *)VCALL(void *, po, 36) + 0x30))->q);
        }
        break;
    }
}
