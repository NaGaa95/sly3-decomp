// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct LM { float gMin, gMax; };
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct S {
    char pad0[0xC]; VTE *pvt; char pad10[0x50 - 0x10]; void *p50; char pad54[0x198 - 0x54]; int x198; float g19C;
    char pad1A0[0x1AC - 0x1A0]; float g1AC; float g1B0; char pad1B4[0x1B8 - 0x1B4]; float g1B8; char pad1BC[0x1E8 - 0x1BC];
    float g1E8; char pad1EC[0x388 - 0x1EC]; S *p388; float t38C; int x390; int state; float t398; char pad39C[0x3A0 - 0x39C];
    qword v3A0; float t3B0; float t3B4; S *p3B8; float t3BC; char pad3C0[0x400 - 0x3C0]; float g400; float g404; float g408;
    float g40C; char pad410[0x41C - 0x410]; S *pnext;
};
struct Scope { unsigned char unused[16]; };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern struct SW { char pad[0x4E18]; float g4E18, g4E1C, g4E20, g4E24; } D_00475480;
extern char D_00341FF0[];
extern S *D_00479BD4;
void func_001448B0(S *s);
void func_00144640(S *s);
void func_00144628(S *s, int n);
float func_00144A50(S *s);
float func_00144A70(S *s);
void func_00144E40(S *s);
int func_001469B0(S *s);
void func_00146AD0(S *s);
float func_0011E940(float a, float b);
int func_0011E8F0(int a, int b);
float func_0011E3B8(float g);
float func_0011EE68(void *pclq, float g);
void func_00120BA8(qword v, float *pa, float *pb, float *pc);
void func_0011D768(M4 *pm, M4 *pmSrc);
void func_0028F680(void *p, int a, void *pv, float g, int b);
qword func_001C9828(void *pv, int a, qword v);
int func_0027F298(S *p, qword v);
void func_002BC350(void *p, int n);
}
float GLimitAbs(float g, float lim);
static const LM s_lm0 = { 0.25f, 1.5f };
static const LM s_lm1 = { 0.25f, 0.5f };
static const VECTOR s_v0 = { -1500.0f, 0.0f, 0.0f, 0.0f };
static const VECTOR s_v1 = { 4500.0f, 0.0f, 0.0f, 0.0f };
static inline M4 *Matrix(S *p) { VTE *e = &p->pvt[36]; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline bool Below(float a, float b) { return a < b; }
static inline float GParam(float g, float a, float b)
{
    if (a == b)
        return 0.0f;
    return (g - a) / (b - a);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Xform(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}

extern "C" void func_00143E50(S *s)
{
    if (g_clock.t > s->t3BC) {
        for (; s->t3BC < g_clock.t; s->t3BC += 0.5f)
            ;
        func_001448B0(s);
    }
    if (g_clock.t > s->t398) {
        for (; s->t398 < g_clock.t; s->t398 += 0.25f)
            ;
        func_00144640(s);
    }
    switch (s->state) {
    case 0:
        s->g400 = s->g19C;
        break;
    case 1:
        if (s->p3B8) {
            M4 m;
            float ang[4];
            if (s->t3B0 <= g_clock.t) {
                int f = !s->p3B8->x198;
                const LM *plm = f ? &s_lm1 : &s_lm0;
                const VECTOR *pv = f ? &s_v1 : &s_v0;
                float dt = func_0011E940(plm->gMin, plm->gMax);
                func_0028F680(s->p3B8->p50, 0, &m, dt, 0);
                s->v3A0 = func_001C9828(&m, 0, *(qword *)pv);
                s->t3B0 = g_clock.t + dt;
            }
            qword v = s->v3A0;
            func_00120BA8(Sub(v, Matrix(s)->r[3]), &ang[1], &ang[2], &ang[3]);
            s->g408 = GLimitAbs(func_0011E3B8(-ang[2]), s->g1AC);
            s->g40C = func_0011E3B8(ang[1]);
            float u = func_0011EE68(D_00341FF0, ang[3] * 0.0001f);
            s->g400 = (1.0f - u) * s->g19C + u * func_00144A50(s);
        } else {
            func_00144628(s, 0);
        }
        break;
    case 2:
        if (s->t3B4 < g_clock.t) {
            float dt;
            int n, f;
            s->g408 = 0.0f;
            dt = 2.0f;
            n = func_0011E8F0(0, 8);
            f = func_0011E8F0(0, 3) == 0;
            if (n % 3 == 0)
                s->g40C = func_0011E3B8(s->g40C + s->g1B8 * 0.6f);
            else if (n % 3 == 2)
                s->g40C = func_0011E3B8(s->g40C - s->g1B8 * 0.6f);
            if (n < 3)
                s->g408 = -s->g1AC;
            else if (n >= 6)
                s->g408 = s->g1AC;
            float a = func_00144A70(s);
            s->g400 = func_0011E940(a, func_00144A50(s));
            if (f)
                dt = 1.0f;
            s->t3B4 = g_clock.t + dt;
        }
        break;
    }
    if (s->t38C < g_clock.t || s->x390) {
        for (; g_clock.t > s->t38C; s->t38C += 0.25f)
            ;
        s->x390 = 0;
        if (s->p388) {
            M4 m;
            Scope scope;
            func_0011D768(&m, Matrix(s->p388));
            for (S *p = D_00479BD4; p; p = p->pnext) {
                if (p == s)
                    continue;
                if (func_0027F298(s->p388, Xform(m, Matrix(p)->r[3]))) {
                    float z = GetZ(Matrix(p)->r[3]);
                    int f = GetZ(Matrix(s)->r[3]) < z;
                    if (f)
                        s->g408 = s->g1AC;
                    else
                        s->g408 = -s->g1AC;
                    s->x390 = 1;
                    break;
                }
            }
            func_002BC350(&scope, 2);
        }
    }
    if (func_001469B0(s)) {
        func_00146AD0(s);
    } else if (Below(GetZ(Matrix(s)->r[3]), D_00475480.g4E1C)) {
        float u = func_0011EE68(D_00341FF0, GParam(GetZ(Matrix(s)->r[3]), D_00475480.g4E18, D_00475480.g4E1C));
        float g = u * s->g1AC;
        s->g408 = s->g408 < g ? s->g408 : g;
    } else {
        int f = 0;
        if (D_00475480.g4E20 < GetZ(Matrix(s)->r[3]))
            f = !s->x390;
        if (f) {
            float u = func_0011EE68(D_00341FF0, GParam(GetZ(Matrix(s)->r[3]), D_00475480.g4E20, D_00475480.g4E24));
            float g = (1.0f - u) * -s->g1AC;
            s->g408 = s->g408 > g ? s->g408 : g;
        }
    }
    s->g404 = GLimitAbs(func_0011E3B8(s->g1E8 - s->g40C), s->g1B0);
    func_00144E40(s);
}
