// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct A64 { char pad[0x64]; float g64; };
struct ASEG { char pad[0x14]; struct A64 *pa; };
struct P {
    char pad0[0xC]; struct VTE *pvt; char pad1[0x1B0 - 0x10]; float g1B0, g1B4, g1B8;
    char pad2[0x1E4 - 0x1BC]; float g1E4, g1E8; char pad3[0x210 - 0x1EC]; void *p210;
    char pad4[0x2C0 - 0x214]; int st; int pad2C4; float g2C8; int pad2CC; float g2D0; float g2D4;
    char pad5[0x300 - 0x2D8]; struct ASEG *p300; int pad304; struct ASEG *p308; int pad30C; struct ASEG *p310;
    char pad6[0x404 - 0x314]; float g404, g408, g40C;
};
extern struct CLOCK { float t; } g_clock;
extern char D_00341FF0[];
extern char D_00341FF8[];
float func_00144A50(struct P *p);
void func_0023D9D0(void *p, qword v);
float func_0011E3B8(float g);
float func_0011EE68(void *p, float g);
void func_00137D08(struct ASEG *p, int a, float g, float h, int b);
static const float s_range[2] = { 0.0f, 31.415928f };
static inline float Length(qword v)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "0"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline void Apply(struct ASEG *pa, float g)
{
    func_00137D08(pa, 0, g * pa->pa->g64, 0.0f, 0);
}

static inline float Pulse(struct P *p)
{
    void *pr = D_00341FF0;
    float g = func_0011EE68(pr, (g_clock.t - p->g2C8) / p->g2D4);
    g = __builtin_fabsf(g - 0.5f);
    if (0.0f < p->g2D0)
        return func_0011EE68(pr, g + 1.0f);
    return func_0011EE68(pr, g);
}

void func_00145AC0(struct P *p)
{
    float g;
    if (p->p210) {
        qword v = ((qword (*)(void *))p->pvt[38].pfn)((char *)p + p->pvt[38].d);
        float t = Length(v);
        struct VECTOR c;
        const float *k;
        t = t / func_00144A50(p);
        c.y = 0.0f;
        c.z = 0.0f;
        k = s_range;
        c.x = (1.0f - t) * k[0] + t * k[1];
        func_0023D9D0(p->p210, *(qword *)&c);
    }
    if (p->p300) {
        switch (p->st) {
        case 1: case 2:
            g = 0.5f;
            break;
        default: {
            void *pr = D_00341FF8;
            g = func_0011E3B8(p->g40C - p->g1E8);
            g = func_0011EE68(pr, g / p->g1B8);
            g = func_0011EE68(D_00341FF0, (g + 1.0f) * 0.5f);
            break;
        }
        }
        Apply(p->p300, g);
    }
    if (p->p308) {
        switch (p->st) {
        case 2:
            g = Pulse(p);
            break;
        case 1:
            g = 0.5f;
            break;
        default: {
            void *pr = D_00341FF8;
            g = func_0011E3B8(p->g408 - p->g1E4);
            g = func_0011EE68(pr, g / p->g1B4);
            g = func_0011EE68(D_00341FF0, (g + 1.0f) * 0.5f);
            break;
        }
        }
        Apply(p->p308, g);
    }
    if (p->p310) {
        switch (p->st) {
        case 1:
            g = Pulse(p);
            break;
        case 2:
            g = 0.5f;
            break;
        default:
            g = func_0011EE68(D_00341FF8, p->g404 / p->g1B0);
            g = func_0011EE68(D_00341FF0, (g + 1.0f) * 0.5f);
            break;
        }
        Apply(p->p310, g);
    }
}
