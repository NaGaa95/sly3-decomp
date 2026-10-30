// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct LM { float gMin, gMax; };
struct P;
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; char pad2[0x130 - 0x128]; VTE e130; char pad3[0x140 - 0x138]; VTE e140; };
struct H { char pad[0x8]; float g8; };
struct P {
    char pad[0xC]; VT *pvt; char pad1[0x134 - 0x10]; H *p134; char pad2[0x20C - 0x138]; void *p20C; char pad3[0x2B8 - 0x210];
    int x2B8; float g2BC; char pad4[0x2CC - 0x2C0]; float g2CC; float g2D0; char pad5[0x400 - 0x2D4]; float g400;
};
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern qword D_00317550;
extern LM D_00341FF0;
extern const float D_00320094; /* FLT_MAX, defined in func_00142AE0.c (same original unit) */
extern LM D_003201F8;
void func_001434A8(P *p, int st);
M3 func_0011CBF0(qword a, qword b);
float func_0011EE68(LM *plm, float g);
void func_002261A0(void *p, int n);
void func_00143230(P *p, int st);
}
struct VU_FLOATM { qword q; VU_FLOATM(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
struct VU_FLOAT { qword q; VU_FLOAT(const VU_FLOAT &s) { q = s.q; } VU_FLOAT(float f) { qword t; __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(f)); q = t; } };
static inline qword Scale(VU_FLOATM s, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
static inline qword Scale(qword a, VU_FLOAT s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
struct VU_VECTOR { qword q; VU_VECTOR(const VU_VECTOR &s) { q = s.q; } VU_VECTOR(const qword &v) { q = v; } };
static inline qword AddR2(qword b, qword a) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(b), "j"(a)); return r; }
typedef qword *(*PFNV)(void *);
typedef qword (*PFNQ)(void *);
typedef void (*PFNS)(void *, qword);
static inline void Push(P *p, VU_VECTOR dv)
{
    VTE *e = &p->pvt->e140;
    void *po = (char *)p + e->d;
    ((PFNS)e->pfn)(po, AddR2(((PFNQ)p->pvt->e130.pfn)((char *)p + p->pvt->e130.d), dv.q));
}
static inline float GFrac(float g, const LM *plm)
{
    if (plm->gMin == plm->gMax)
        return 0.0f;
    return (g - plm->gMin) / (plm->gMax - plm->gMin);
}

void func_00143230(P *p, int st)
{
    if (st == p->x2B8)
        return;
    switch (p->x2B8) {
    case 1:
    case 2: {
            VT *vt = p->pvt;
            VTE *e = &vt->e140;
            void *po = (char *)p + e->d;
            ((PFNS)e->pfn)(po, Scale(VU_FLOATM(p->g400), *((PFNV)vt->e120.pfn)((char *)p + vt->e120.d)));
            func_001434A8(p, -1);
        break;
    }
    case 3:
    case 4:
    case 5:
        func_001434A8(p, -1);
        break;
    }
    p->x2B8 = st;
    p->g2BC = g_clock.t;
    p->g2CC = D_00320094;
    switch (st) {
    case 1:
    case 2: {
        float g = 2352.94092f;
        M3 m;
        m = func_0011CBF0(*((PFNV)p->pvt->e120.pfn)((char *)p + p->pvt->e120.d), D_00317550);
        if (p->x2B8 == 2)
            g = -2352.94092f;
        g *= func_0011EE68(&D_00341FF0, GFrac(p->p134->g8, &D_003201F8));
        {
            Push(p, Scale(m.r[1], VU_FLOAT(g)));
        }
        if (p->p20C)
            func_002261A0(p->p20C, 0x780);
        p->g2D0 = p->x2B8 == 1 ? -6.28318548f : 6.28318548f;
        func_001434A8(p, 1);
        break;
    }
    case 3:
    case 4:
    case 5:
        func_001434A8(p, 0);
        break;
    }
}
