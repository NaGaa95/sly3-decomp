// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct OBJ { char pad[0xC]; VTE *pvt; };
struct ITEM { char pad[0x1C]; VTE *pvt; };
struct SMP { float a[3]; } __attribute__((aligned(16)));
struct CM {
    char pad0[0xC]; VTE *pvt; char pad10[0x90 - 0x10]; qword dir;
    char padA0[0xE0 - 0xA0]; OBJ *pobjTarget; char padE4[0x118 - 0xE4];
    float g118, g11C, g120; float g124; char pad128[0x144 - 0x128]; float g144;
    char pad148[0x2F4 - 0x148]; int f2F4; char pad2F8[0x300 - 0x2F8]; ITEM *pitem;
    char pad304[0x410 - 0x304]; float g410, g414, g418;
};
struct CLOCK { float t; float dt; float pad8[2]; float dt10; };
struct FLAGS { int grf; };
static const SMP D_00320D80 = { { 20.0f, 10.0f, 0.5f } };
static const SMP D_00320D90 = { { 200.0f, 100.0f, 5.0f } };
extern "C" {
extern CLOCK g_clock;
extern FLAGS D_0036DBEC;
extern int D_004C4090;
extern float D_0036BC98;
void func_00167960(CM *p, float g);
float func_0011E730(float g, float gTarget, float gMax, float dt, float *pa, float *pb);
void func_00166A40(CM *p);
float func_0011E598(float g, float gTarget, float dt, const SMP *psmp, float *pr);
}
static inline void *VCall(OBJ *p, int i)
{
    VTE *e = &p->pvt[i];
    return e->pfn((char *)p + e->d);
}
static inline qword Pos(void *p) { return ((qword *)VCall((OBJ *)p, 36))[3]; }
static inline float Dot(qword a, qword b)
{
    qword d, one;
    __asm__ __volatile__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    int i;
    __asm__("qmfc2.ni %0, %1" : "=r"(i) : "j"(d));
    union { int i; float f; } u; u.i = i; return u.f;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__ __volatile__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float GMin(float a, float b) { return b < a ? b : a; }
class LOCK {
    CM *m_p;
public:
    LOCK(CM *p) { m_p = p; VCall((OBJ *)p, 1); }
    ~LOCK() { VCall((OBJ *)m_p, 2); }
};
extern "C" void func_001662C0(CM *p)
{
    LOCK lock(p);
    ITEM *pitem;
    while ((pitem = p->pitem) != 0) {
        VTE *e = &pitem->pvt[3];
        e->pfn((char *)pitem + e->d);
        if (p->pitem == pitem)
            break;
    }
    int fReset = p->f2F4 != 0;
    if (fReset) {
        func_00167960(p, p->g11C);
        p->f2F4 = 0;
    } else {
        if (p->g11C != p->g118) {
            p->g118 = func_0011E730(p->g118, p->g120, p->g11C, g_clock.dt, &p->g124, &p->g120);
            VCall((OBJ *)p, 55);
        }
        p->f2F4 = 0;
    }
    func_00166A40(p);
    if ((D_0036DBEC.grf >> 1) & 1) {
        float g = 0.0f;
        if (p->g418 != 0.0f) {
            g = p->g418;
        } else if (p->pobjTarget) {
            qword d = Sub(Pos(p->pobjTarget), Pos(p));
            float r = p->g144 + p->g144;
            float dist = Dot(d, p->dir);
            float rMax = r + 1500.0f;
            if (r <= dist)
                g = GMin(rMax, dist);
        }
        float h;
        if (g == 0.0f)
            g = p->g144 * 4.0f;
        if (!D_004C4090)
            h = g * p->g11C / D_0036BC98;
        else
            h = 0.0f;
        if (fReset) {
            p->g410 = h;
            p->g414 = g;
        } else {
            p->g410 = func_0011E598(p->g410, h, g_clock.dt10, &D_00320D80, 0);
            if (p->g414 != 0.0f)
                p->g414 = func_0011E598(p->g414, g, g_clock.dt10, &D_00320D90, 0);
            else
                p->g414 = g;
        }
    }
}
