// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00142E18 (A46): A12 draft fixed: both speed profiles use the Sly-style "if (dt<half) {} else {v0=a*half; dt-=half; a=-a;} v0+a*dt" (shared mul cross-jumped), stick deflection scaled inside each branch.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } VU;
struct LM { float gMin, gMax; };
struct H2 { char pad[0xC]; float gC; float g10; };
struct H { float g0; float g4; char pad[0x18 - 8]; int x18; char pad1[0x134 - 0x1C]; struct H2 *p134; };
struct A { char pad[0x18]; int x18; };
struct AN { char pad[0x14]; struct A *p14; };
struct P {
    char pad[0x134]; struct H *p134; char pad0[0x19C - 0x138]; float g19C; char pad1[0x1AC - 0x1A0]; float g1AC; float g1B0; float g1B4; float g1B8;
    char pad2[0x1C8 - 0x1BC]; char x1C8[0x1E4 - 0x1C8]; float g1E4; float g1E8; char pad3[0x214 - 0x1EC]; void *p214;
    char pad4[0x22C - 0x218]; struct A *p22C; struct A *p230; struct AN *p234; char pad5[0x284 - 0x238]; float g284;
    char pad6[0x2A0 - 0x288]; int x2A0; char pad7[0x2B8 - 0x2A4]; int x2B8; float g2BC; int x2C0; int x2C4; float g2C8;
    float g2CC; float g2D0; float g2D4; int x2D8; float g2DC; char pad8[0x3CC - 0x2E0]; int x3CC; int x3D0;
    char pad9[0x400 - 0x3D4]; float g400; float g404; float g408; float g40C; int x410; float g414; int x418;
    char padA[0x4BC - 0x41C]; struct H *p4BC;
};
extern struct CLOCK { float t; float dt; } g_clock;
extern struct LM D_00341FF0;
void func_00143628(struct P *p);
float func_00144A50(struct P *p);
float func_00144A70(struct P *p);
float func_0011EE68(struct LM *plm, float g);
float func_0011E3B8(float g);
float func_0011E560(float a, float b);
float func_0011E840(void *psmp, float *pdg, float gCur, float gTarget, float dt);
void func_0023D9D0(struct P *p, qword v);
void func_0023D938(struct P *p, qword v);
void func_00146D08(struct P *p);
int func_001F4430(struct P *p);
void func_00144E40(struct P *p);
void func_00137588(void *anim, void *recv, int flags, void **out, float t, float rate);
void func_00137628(void *pp);
void func_001421C0(struct P *p);

void func_00142E18(struct P *p)
{
    int prev;
    int f;
    float u, g;
    func_00143628(p);
    prev = p->x410;
    p->x418 = 0;
    p->x410 = 0;
    if (p->x2B8 < 6) if (p->x2B8 >= 0) {
        float gy, gx;
        f = 0;
        if (p->x2B8 == 0 || p->x2D8)
            f = 1;
        if (f && !p->p4BC && (p->p134->x18 & 0x40)) {
            p->g400 = func_00144A50(p);
            p->x410 = p->x3CC;
            if (!prev && p->x410)
                p->g414 = g_clock.t;
        } else if (f && !p->p4BC && (p->p134->x18 & 0x80)) {
            p->g400 = func_00144A70(p);
            p->x418 = p->x3D0;
        } else {
            p->g400 = p->g19C;
        }
        if (p->x2D8)
            u = func_0011EE68(&D_00341FF0, (g_clock.t - p->g2DC) / (p->g2C8 + p->g2D4 - p->g2DC));
        else {
            u = 0.0f;
            if (f)
                u = 1.0f;
        }
        if (p->p4BC && p->p4BC->p134) {
            gx = p->p4BC->p134->gC * u;
            gy = p->p4BC->p134->g10 * u;
        } else {
            gx = p->p134->g0 * u;
            gy = p->p134->g4 * u;
        }
        {
        if (__builtin_fabsf(gx) < 0.2f)
            gx = 0.0f;
        if (__builtin_fabsf(gy) < 0.2f)
            gy = 0.0f;
        p->g404 = gx * p->g1B0;
        p->g40C = func_0011E3B8(p->g1E8 + -gx * p->g1B8);
        g = func_0011E560(func_0011E3B8(p->g1E4 + gy * p->g1B4), p->g1AC);
        }
        switch (p->x2C0) {
        case 0:
        case 1: {
            float half = p->g2D4 * 0.5f;
            float dt = g_clock.t - p->g2C8;
            float a = p->g2D0 / (half * half);
            float v0 = 0.0f;
            VU v;
            if (dt < half) {
            } else {
                v0 = a * half;
                dt = dt - half;
                a = -a;
            }
            v.f[1] = 0.0f;
            v.f[2] = 0.0f;
            v.f[0] = v0 + a * dt;
            func_0023D9D0(p, v.q);
            break;
        }
        case 2: {
            float half = p->g2D4 * 0.5f;
            float dt = g_clock.t - p->g2C8;
            float a = p->g2D0 / (half * half);
            float v0 = 0.0f;
            float x2;
            if (dt < half) {
            } else {
                v0 = a * half;
                dt = dt - half;
                a = -a;
            }
            x2 = v0 + a * dt;
            if (p->x2D8) {
                float gA = p->g1E4 + x2 * g_clock.dt;
                g = (1.0f - u) * gA + u * func_0011E840(p->x1C8, 0, p->g1E4, g, g_clock.dt);
            } else {
                VU w, v;
                v.f[1] = x2;
                v.f[0] = 0.0f;
                v.f[2] = 0.0f;
                func_0023D9D0(p, v.q);
                w.f[1] = 0.0f;
                w.f[0] = p->g400;
                w.f[2] = 0.0f;
                func_0023D938(p, w.q);
            }
            break;
        }
        }
        p->g408 = g;
    }
    func_00146D08(p);
    if (p->p134->x18 & 8) {
        int fPos = func_001F4430(p) > 0;
        struct A *pa;
        func_00144E40(p);
        pa = fPos ? p->p22C : p->p230;
        if (!p->p234 || pa->x18 != p->p234->p14->x18)
            func_00137588(pa, p->p214, 9, (void **)&p->p234, 0.0f, 1.0f);
    } else {
        p->g284 = g_clock.t;
        p->x2A0 = 0;
        func_00137628(&p->p234);
    }
    func_001421C0(p);
}
