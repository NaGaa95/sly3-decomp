// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
typedef struct { qword r[4]; } M4;
struct P;
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; struct VTE e120; };
struct P {
    char pad[0xC]; struct VT *pvt; char pad1[0x1AC - 0x10]; float g1AC; float g1B0; char pad2[0x1E8 - 0x1B4]; float g1E8;
    char pad3[0x2E0 - 0x1EC]; void *p2E0; void *p2E4; char pad4[0x2F4 - 0x2E8]; int x2F4; float g2F8;
    char pad5[0x400 - 0x2FC]; float g400; float g404; float g408; float g40C;
};
extern struct CLOCK { float t; } g_clock;
extern float D_0047A2AC;
static const float s_v[4] __attribute__((aligned(16))) = { 2000.0f, 0.0f, 0.0f, 0.0f };
void func_00137628(void **pp);
void func_00137588(void *anim, void *recv, int flags, void **out, float t, float rate);
float func_00144A50(struct P *p);
void func_0011CCF8(M4 *pm, void *opt, M4 *out);
qword *func_002BA818(qword *out, qword v);
qword func_001C9828(M4 *pm, const M4 *pmDst, qword v);
float func_0011E3B8(float g);

static inline M4 *Mat(struct P *p) { return p->pvt->e120.pfn((char *)p + p->pvt->e120.d); }
static inline float LengthXY(qword v)
{
    qword t;
    float g;
    int n;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=&j"(t) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(t) : "j"(t));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(n) : "j"(t));
    return g;
}

void func_00143B30(struct P *p, int st)
{
    int prev = p->x2F4;
    if (st == prev)
        return;
    if (prev == 1)
        func_00137628(&p->p2E4);
    p->x2F4 = st;
    p->g2F8 = g_clock.t;
    switch (st) {
    case 0:
        *(int *)&p->g400 = 0;
        *(int *)&p->g404 = 0;
        p->g408 = -p->g1AC * 0.7f;
        break;
    case 1:
        if (p->p2E0)
            func_00137588(p->p2E0, p, 1, &p->p2E4, 0.0f, 1.0f);
        break;
    case 2: {
        M4 m;
        VU u;
        int f;
        p->g400 = func_00144A50(p);
        p->g408 = p->g1AC * 0.6f;
        func_0011CCF8(Mat(p), 0, &m);
        { qword pos = Mat(p)->r[3]; func_002BA818(&m.r[3], pos); }
        ((VU *)&m.r[3])->f[3] = 1.0f;
        u.q = func_001C9828(&m, 0, *(const qword *)s_v);
        f = D_0047A2AC < LengthXY(u.q);
        if (f) {
            p->g40C = func_0011E3B8(p->g1E8 - 3.14159274f);
            p->g404 = p->g1B0;
        }
        break;
    }
    }
}
