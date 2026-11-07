// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3: proximity scale/angle/distance of pos to the player(s) (two-player loop when D_00475480.n4FA4).
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *(*method)(void *); };
struct POSQ { char pad[0x30]; qword pos; };
struct LO { char pad[0xC]; struct VTE *vt; };
struct G { char pad[0x4FA4]; int n4FA4; };
extern struct G D_00475480;
extern char D_0036E740[];
extern char D_00341FF0[];
struct LO *func_001A91D8(void *);
struct LO *func_00165B28(struct G *);
float func_0011EE68(void *limits, float value);
qword func_001C94E8(void *, void *, qword);
float atan2f(float y, float x);
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }

static inline float GMax(float a, float b) { return a > b ? a : b; }

void func_00245440(qword pos, float *range, float *pOut, int *pAngle, float *pDist)
{
    if (D_00475480.n4FA4) {
        float a[2];
        int i;
        for (i = 0; i < 2; i++) {
            struct LO *pl = func_001A91D8(D_0036E740 + i * 0x11C0);
            if (!pl) {
                a[i] = 0;
                continue;
            }
            {
                float d = F(Len(Sub(pos, ((struct POSQ *)VCALL(pl, 36))->pos)));
                a[i] = func_0011EE68(D_00341FF0, (range[1] - d) / (range[1] - range[0]));
            }
        }
        if (pOut) *pOut = GMax(a[0], a[1]);
        if (pAngle) {
            float t;
            if (0.0f < a[0] && 0.0f < a[1]) t = 0.0f;
            else if (0.0f < a[0]) t = -1.5707964f;
            else if (0.0f < a[1]) t = 1.5707964f;
            else t = 0.0f;
            *pAngle = (int)(t * 57.2957763671875f);
        }
        if (pDist) *pDist = 0;
    } else {
        struct LO *pl = func_00165B28(&D_00475480);
        qword v = Sub(pos, ((struct POSQ *)VCALL(pl, 36))->pos);
        float d = F(Len(v));
        float g = func_0011EE68(D_00341FF0, (range[1] - d) / (range[1] - range[0]));
        if (pOut) *pOut = g;
        if (pAngle) {
            if (0.0f < g) {
                qword q = func_001C94E8(0, pl, v);
                float ang = atan2f(-Y(q), X(q));
                if (range[1] < range[0]) ang += 3.1415927f;
                *pAngle = (int)(ang * 57.2957763671875f);
            } else {
                __asm__("" : : "j"(v)); /* zero-insn: raises v refs so it is caller-saved in its vf reg */
                *pAngle = 0;
            }
        }
        if (pDist) *pDist = d;
    }
}
