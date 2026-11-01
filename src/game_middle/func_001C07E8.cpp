// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Score (smaller is better) of one candidate entry for the owner `p` (same routine as Sly 2 func_0019F7D0): flag 1 rejects entries that
// are already taken, flag 2 requires a valid sub-object at the entry position, a raised ground probe (several vertical segment tests around the
// position) penalises positions without clear ground or head room, and flag 4 keeps the owner itself in the crowd penalty: every other
// object of `apo` adds a clamped quadratic distance term (D_003234D0 / D_003234E0); the worst penalty wins.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct HIT { qword pos; char pad[0x18]; float x28; char pad2[0x14]; float x40; char pad3[0x1C]; };
struct LO2 { char pad[0x218]; qword *x218; };
struct O { char pad[0xDC]; int xdc; };
struct S { O *x0; };
struct Q { int x0, x4, x8; };
typedef struct { float g, gFirst, gSecond; } CLQ;
typedef struct { float gMin, gMax; } LM;
extern "C" {
void func_001D2770(void *p);
void func_001D2798(void *p, int n);
qword func_001C03A0(O *p, Q *q, float g);
void func_0025D0D8(void *g, qword pos, void *pfn, int x, int *pi, int *pj, float r);
int func_00165000(int z, qword a, qword b, int i, int j, HIT *phit);
void func_0025CDD0(void);
void *func_001ED678(qword pos, int n);
int func_001ED170(void *obj, qword pos, int n);
qword func_00250600(LO2 *p);
extern char D_00475480[];
extern float D_003234E8;
extern qword D_00323450[8];
extern CLQ D_003234D0;
extern LM D_003234E0;
}
class FRAME { int a[4]; public: FRAME() { func_001D2770(this); } ~FRAME() { func_001D2798(this, 2); } };
static inline float GMax(float a, float b) { return a > b ? a : b; }
static inline float GFromClq(CLQ *pclq, float g) { return pclq->g + g * (pclq->gFirst + g * pclq->gSecond); }
static inline float GClamp(float g, float lo, float hi) { if (g < lo) g = lo; else if (g > hi) g = hi; return g; }
extern "C" float func_001C07E8(S *p, Q *q, int flags, int n, LO2 **apo)
{
    float g;
    qword pos;
    if ((flags & 1) && q->x4)
        return D_003234E8;
    g = 0.0f;
    pos = func_001C03A0(p->x0, q, g);
    if (flags & 2) {
        void *obj = func_001ED678(pos, 1);
        if (!obj || !func_001ED170(obj, pos, 0))
            return D_003234E8;
    }
    if (q->x8) {
        FRAME frame;
        U a, b;
        HIT hit;
        int i0, i1;
        func_0025D0D8(D_00475480, pos, (void *)func_0025CDD0, p->x0->xdc, &i0, &i1, 500.0f);
        a.q = pos;
        b.q = pos;
        a.f[2] += 125.0f;
        b.f[2] -= 175.0f;
        if (!func_00165000(0, a.q, b.q, i0, i1, &hit) || hit.x40 == 0.0f || hit.x28 < 0.7f)
            g = GMax(g, 2000.0f);
        else
            pos = hit.pos;
        b.q = pos;
        a.q = pos;
        a.f[2] += 180.0f;
        b.f[2] += 5.0f;
        if (func_00165000(0, a.q, b.q, i0, i1, &hit))
            g = GMax(g, 2000.0f);
        for (unsigned k = 0; k < 8; k++) {
            qword v;
            __asm__("vadd.xyzw %0, %1, %2" : "=j"(v) : "j"(pos), "j"(D_00323450[k]));
            b.q = v;
            a.q = v;
            a.f[2] += 50.0f;
            b.f[2] -= 30.0f;
            if (!func_00165000(0, a.q, b.q, i0, i1, &hit)) {
                g = GMax(g, 1500.0f);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        LO2 *lo = apo[i];
        if (!(flags & 4) && lo == (LO2 *)p->x0)
            continue;
        qword d, t;
        float dist;
        d = func_00250600(lo);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(d), "j"(pos));
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(t));
        __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(d));
        g = GMax(g, GClamp(GFromClq(&D_003234D0, dist), D_003234E0.gMin, D_003234E0.gMax));
    }
    return g;
}
