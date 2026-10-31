// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
/* A20b draft; A26: case 15 -1 scale passed as an in/out vmulx operand so its home store follows the result store. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { qword r[3]; } M3;
struct VTE { short delta; short pad; void *pfn; };
struct X134 { float g0, g4, g8; };
struct X113C { char pad[0x1C]; float g1C; char pad20[0x40 - 0x20]; float g40; };
struct X11B4 { char pad[0x4AC]; int x4AC; };
struct OBJ { char pad[0xC]; struct VTE *vt; };
struct X218 { char pad[0x4C]; struct OBJ *p4C; };
struct POLY { float a, b, c; };
struct LIM { float gMin, gMax; };
struct PO {
    char pad0[0xC];
    struct VTE *vt;
    char pad10[0x1F];
    unsigned long b2F : 8;
    char pad30[0x104];
    struct X134 *p134;
    char pad138[0x68];
    qword v1A0;
    int x1B0;
    char pad1B4[0x8];
    float g1BC;
    M3 m1C0;
    char pad1F0[0x28];
    struct X218 *p218;
    char pad21C[0x104];
    char a320[1];
    char pad321[0x1DF];
    char a500[1];
    char pad501[0x93F];
    char aE40[1];
    char padE41[0x2C7];
    void *p1108;
    float g110C;
    char pad1110[0x2C];
    struct X113C *p113C;
    char pad1140[0x4];
    int x1144;
    char pad1148[0x6C];
    struct X11B4 *p11B4;
    char pad11B8[0x2B8];
    char a1470[1];
    char pad1471[0xAF];
    int x1520;
    float g1524;
    char pad1528[0x8];
    char a1530[1];
    char pad1531[0x8F];
    qword v15C0;
    char pad15D0[0x60];
    int x1630;
    char pad1634[0x2C];
    char a1660[1];
    char pad1661[0x2F];
    qword v1690;
    char pad16A0[0xC0];
    int x1760;
    char pad1764[0xC];
    char a1770[1];
    char pad1771[0xAF];
    int x1820;
    char pad1824[0xC];
    char a1830[1];
    char pad1831[0x10F];
    int x1940;
};
extern struct CLOCK { float t; float dt; } g_clock;
extern struct { float dt; } D_0036BB9C;
extern struct LIM D_00341FF0;
static const struct POLY D_0031FB30 = { -1.0f, 2.0f, 0.0f };
static const struct POLY D_0031FB40 = { 1.0f, 0.0f, 0.0f };
static const float D_0031FB50[4][4] = { { 60.0f, 0.0f, -45.0f, 0.0f }, { -15.0f, 40.0f, -45.0f, 0.0f }, { -15.0f, -40.0f, -45.0f, 0.0f }, { -65.0f, 65.0f, 0.0f, 0.0f } };
void func_00152A48(struct PO *p);
void func_0013DDE8(struct PO *p);
void func_0013D518(struct PO *p);
void func_0024E878(struct PO *p, float g);
void func_00258CF0(void *pv, float g);
void func_00258DA0(void *pv);
int func_00173428(void *pv);
void *func_00173408(void *pv);
void func_001B9C48(void *pv);
void func_001B30E8(void *pv);
void func_0024E920(struct PO *p, void *pv);
qword func_0011FD70(float a, float b, float c);
void func_001C1CA8(struct PO *p, void *pv, int n);
qword func_0024F278(struct PO *p, void *pv, float g);
float func_0011E3B8(float g);
float func_0011E560(float g, float gMax);
void func_001C1550(struct PO *p, void *pv, int n);
void func_0017EF78(void *pv);
struct X113C *func_00156AB0(struct PO *p);
void func_00138B68(struct X113C *px, float g);
void func_001C2B48(void *pv);
void func_0013F300(struct PO *p);
void func_0024FCA0(struct PO *p, const void *pv);
#define VCALL(T, po, n) (((T (*)(void *))(po)->vt[n].pfn)((char *)(po) + (po)->vt[n].delta))
static inline int FIsX(void *pv) { return pv && func_00173428(pv); }
static inline float GEval(const struct POLY *pp, float t) { return pp->a + t * (pp->b + t * pp->c); }
static inline float GClamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword LenXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword MulT(const M3 *m, qword v)
{
    qword r, a, b, c, one;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
            "vadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
static inline qword Neg(qword v)
{
    U s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(-1.0f));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
static inline void SetVel(struct PO *p, qword w)
{
    p->v1A0 = w;
    p->v1A0 = MulT(&p->m1C0, w);
}

void func_0013DE58(struct PO *p)
{
    func_00152A48(p);
    if (!(p->b2F & 1))
        return;
    func_0013DDE8(p);
    func_0013D518(p);
    switch (p->x1520) {
    case 0:
        if (p->x1940)
            func_0024E878(p, 0.5f);
        else
            VCALL(void, p, 110);
        if (0.15f < g_clock.t - p->g1524)
            p->x1B0 = 0;
        break;
    case 1:
        func_0024E878(p, p->g110C);
        func_00258CF0(p->a1470, 1.0f);
        func_00258DA0(p->a1470);
        break;
    case 9: {
        void *pv;
        func_0024E878(p, p->g110C);
        pv = 0;
        if (FIsX(p->p1108))
            pv = func_00173408(p->p1108);
        if (!pv)
            pv = p->a1770;
        func_00258CF0(pv, p->p134->g8);
        func_00258DA0(pv);
        break;
    }
    case 2:
        func_001B9C48(p->a320);
        break;
    case 3:
        func_001B30E8(p->a500);
        break;
    case 5:
        func_0024E920(p, p->p11B4);
        SetVel(p, func_0011FD70(p->g110C + 3.14159265f, p->p134->g8 * F(LenXY(p->v15C0)) * p->p113C->g40, 0.0f));
        func_001C1CA8(p, p->a1530, p->x1630);
        break;
    case 6:
    case 7: {
        float g;
        qword v;
        func_0024E920(p, p->p11B4);
        g = p->g110C + 3.14159265f;
        v = func_0024F278(p, p->p113C, p->p113C->g1C);
        SetVel(p, func_0011FD70(g, p->p134->g8 * F(LenXY(v)), 0.0f));
        break;
    }
    case 8:
        switch (p->x1820) {
        case 1: {
            struct X134 *px = p->p134;
            float gSpeed = GClamp(GEval(&D_0031FB30, p->p134->g8), D_00341FF0.gMin, D_00341FF0.gMax);
            float gTurn = GClamp(GEval(&D_0031FB40, p->p134->g8), D_00341FF0.gMin, D_00341FF0.gMax);
            float gZero = 0.0f;
            if (gZero < p->p134->g8)
                func_0024E878(p, p->g1BC + func_0011E560(func_0011E3B8(p->g110C - p->g1BC), gTurn * (D_0036BB9C.dt * 5.0f)));
            {
                qword w = func_0011FD70(p->g110C + 3.14159265f, gSpeed * F(LenXY(p->v1690)) * p->p113C->g40, gZero);
                p->v1A0 = w;
                p->v1A0 = MulT(&p->m1C0, w);
                p->x1144 = -1;
            }
            func_001C1550(p, p->a1660, p->x1760);
            break;
        }
        case 3:
        case 4:
            func_0024E920(p, (void *)p->p11B4->x4AC);
            break;
        }
        break;
    case 16:
        func_0017EF78(p->a1830);
        break;
    case 12: {
        struct X113C *px = func_00156AB0(p);
        p->v1A0 = Neg(func_0024F278(p, px, px->g1C));
        break;
    }
    case 13: {
        struct X113C *px = func_00156AB0(p);
        p->v1A0 = Neg(func_0024F278(p, px, px->g1C));
        func_00138B68(px, p->p134->g8);
        func_0024E878(p, p->g110C);
        break;
    }
    case 15: {
        qword v = func_0024F278(p, p->p113C, p->p113C->g1C);
        register qword r __asm__("vf1"); /* register pin: the result lives in vf1 */
        qword t;
        U s;
        __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(-1.0f));
        __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r), "+j"(t) : "j"(v));
        p->v1A0 = r;
        s.q = t;
        if (0.0f < p->p134->g8)
            func_0024E878(p, p->g110C);
        break;
    }
    case 4:
        func_001C2B48(p->aE40);
        break;
    case 18:
        if (p->p218) {
            struct OBJ *po = p->p218->p4C;
            U u;
            u.q = VCALL(qword, po, 39);
            u.f[2] = func_0011E560(u.f[2], 10.0f);
            func_0024E878(p, p->g1BC + u.f[2] * D_0036BB9C.dt);
        }
        break;
    }
    func_0013F300(p);
    switch (p->x1520) {
    case 2:
    case 4:
    case 10:
        break;
    default:
        func_0024FCA0(p, D_0031FB50);
        break;
    }
}
