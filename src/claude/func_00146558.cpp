// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; char pad2[0x140 - 0x128]; VTE e140; };
struct P {
    char pad[0xC]; VT *pvt; char pad10[0x4C - 0x10]; void *p4C; char pad50[0xDC - 0x50]; int xDC;
    char padE0[0x1AC - 0xE0]; float g1AC; float g1B0; char pad1B4[0x1E8 - 0x1B4]; float g1E8; char pad1EC[0x1F4 - 0x1EC];
    float g1F4; char pad1F8[0x200 - 0x1F8]; float g200; char pad204[0x400 - 0x204]; float g400; float g404; float g408; float g40C;
};
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
extern "C" {
extern char D_00475480[];
void func_0025CE90();
void func_0025D0D8(void *psw, qword pos, void (*pfn)(), int k, float r, int *pa, int *pb);
void func_0011CCF8(void *pm, void *p, M3 *pm);
qword func_0011FDD8(float pan, float tilt, float r);
void *func_00165000(int flags, qword a, qword b, int count, int recs, void *out);
void func_00120BA8(qword v, float *pa, float *pb, int n);
float func_0011E3B8(float g);
int func_0023E130(P *p);
}
float GLimitAbs(float g, float lim);
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline M4 *Matrix(P *p) { VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline qword operator*(VU_FLOAT f, qword v)
{ qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(v)); return r; }
static inline qword Add(qword a, qword b)
{ qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    int t;
    __asm__("qmfc2.ni %0, %1" : "=r"(t) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(t));
    return g;
}
static inline float Dot1(qword a, qword b)
{
    register qword d __asm__("vf2"); /* pin: dot result in vf2 */
    qword one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static inline qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword Normalize(qword v)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(Len(v)));
    return r;
}
static inline float Clamp(float g, float lo, float hi) { return g < lo ? lo : (hi < g ? hi : g); }
static const float s_atilt[9] = { -1.2f, -0.9f, -0.6f, -0.3f, 0.0f, 0.3f, 0.6f, 0.9f, 1.2f };
static const int s_cpan[9] = { 7, 9, 10, 11, 12, 11, 10, 9, 7 };

extern "C" void func_00146558(P *p)
{
    FRAME frame;
    qword pos = Matrix(p)->r[3];
    int a, b;
    func_0025D0D8(D_00475480, pos, func_0025CE90, p->xDC, 1500.0f, &a, &b);
    if (!a)
        return;
    M3 mat;
    func_0011CCF8(p->p4C, 0, &mat);
    qword dir = mat.r[0];
    qword best;
    float gBest;
    {
        qword t = VU_FLOAT(-1.0f) * dir;
        gBest = Dot1(dir, t);
        best = t;
    }
    for (unsigned int i = 0; i < 9; i++) {
        for (int j = 0; j < s_cpan[i]; j++) {
            qword d = func_0011FDD8(j * 6.2831855f / s_cpan[i], s_atilt[i], 1500.0f);
            if (!func_00165000(0, pos, Add(pos, d), a, b, 0)) {
                qword n = Normalize(d);
                float g = Dot(dir, n);
                if (gBest < g) {
                    gBest = g;
                    best = n;
                }
            }
        }
    }
    func_00120BA8(best, &p->g40C, &p->g408, 0);
    p->g408 = GLimitAbs(p->g408, p->g1AC);
    p->g400 = p->g200;
    float d = func_0011E3B8(p->g1E8 - p->g40C);
    float lo = -3.1415927f, hi = 3.1415927f, r;
    if (d < lo)
        r = lo;
    else if (hi < d)
        r = hi;
    else
        r = d;
    p->g404 = r / 3.1415927f * p->g1B0;
    if (func_0023E130(p)) {
        VTE *e = &p->pvt->e140;
        char *self = (char *)p + e->d;
        qword r0 = Matrix(p)->r[0];
        ((void (*)(void *, qword))e->pfn)(self, VU_FLOAT(-p->g1F4) * r0);
    }
}
