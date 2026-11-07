// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0026C420: per-frame velocity update of an SO with a partner SO at +0x270 (no Sly 2 counterpart). In states 1/4 it decays a timer, smooths the
// tilt (+0x1A8) and builds an impulse from func_0026C390; then by mode (+0x198): 2 = follow an offset point of the partner, 1 = spring
// toward the partner, 0 = brake the velocity. Finally the angular velocity is driven toward the pan/tilt orientation (+0x1DC/+0x1E0).
// Matching notes: the case-2 point is a statement temporary (VU_VECTOR(..).Q()) so its slot frees before the dt VU_FLOAT; the SMP
// initializer and unit X vector are rodata of this unit (D_00328B18, D_00328B80); dt VU_FLOATs use the A41 "=j,!r"/"r,m" form.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; VTE e128; VTE e130; VTE e138; };
struct CLOCK { float t; float dt; };
extern CLOCK g_clock;
struct VU_VECTOR { float x, y, z, w; VU_VECTOR(qword v) { *(qword *)this = v; } qword Q() const { return *(qword *)this; } } __attribute__((aligned(16)));
struct SMP { float a, b, c; };
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct SO {
    char pad[0xC]; VT *pvt; char pad10[0x190 - 0x10]; int n190; int pad194; int n198; float f19C;
    union { qword q; float f[4]; } v1A0; char pad1B0[0x1DC - 0x1B0]; float f1DC; float f1E0; float f1E4; float f1E8;
    char pad1EC[0x270 - 0x1EC]; SO *p270; float f274;
};
extern "C" {
extern VECTOR4 D_00317560;
extern const SMP D_00328B18;
extern const VECTOR4 D_00328B80;
extern char D_00341FF0[];
void func_00243738(SO *);
float func_0011EE68(void *, float);
float func_0011E598(float, float, float, SMP *, float *);
qword func_0026C390(SO *, float);
qword func_001C94E8(SO *, SO *, qword);
qword func_001C9428(SO *, SO *, qword);
void func_00244828(SO *, qword);
void func_00244890(SO *, qword);
int func_0026DE50(SO *);
float func_0011FE60(qword, qword, qword *, qword *);
M3 *func_0011CAE0(M3 *, float, float);
M3 func_0011CFC0(M4 *, M3 *);
qword func_0011D388(M3 *);
void func_0026C420(SO *p);
}
struct VU_FLOAT { qword q; VU_FLOAT() {} VU_FLOAT(CLOCK *pc) { __asm__("qmtc2.ni %1, %0" : "=j,!r"(q) : "r,m"(pc->dt)); } VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline M4 *Matrix(SO *p) { VTE *e = &p->pvt->e120; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline qword Vel(SO *p) { VTE *e = &p->pvt->e130; return ((qword (*)(void *))e->pfn)((char *)p + e->d); }
static inline qword AngVel(SO *p) { VTE *e = &p->pvt->e138; return ((qword (*)(void *))e->pfn)((char *)p + e->d); }
static inline qword operator*(qword v, VU_FLOAT f)
{ qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(f.q)); return r; }
static inline qword operator/(qword v, VU_FLOAT f)
{ qword r; __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(f.q)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline float Length(qword v)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline qword QwFromXyz(float x, float y, float z)
{
    qword q;
    int t;
    __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}

void func_0026C420(SO *p)
{
    func_00243738(p);
    if (p->n190 == 1 || p->n190 == 4) {
        qword vel = Vel(p);
        VECTOR4 dv = D_00317560;
        p->f19C = func_0011EE68(D_00341FF0, p->f19C - g_clock.dt * 2.0f);
        if (p->f19C > 0.0f) {
            if (p->n198 == 1 || p->n198 == 2) {
                SMP smp = D_00328B18;
                float a, b;
                func_0011E598(p->f1E0, p->f1E4, g_clock.dt, &smp, &a);
                func_0011E598(p->f1E0, p->f1E8, g_clock.dt, &smp, &b);
                p->v1A0.f[2] = p->v1A0.f[2] * (p->v1A0.f[2] > 0.0f ? -a : b);
            }
            *(qword *)&dv = func_001C94E8(p, 0, func_0026C390(p, p->f19C));
        }
        switch (p->n198) {
        case 2: {
            qword c = func_001C9428(p->p270, 0, VU_VECTOR(QwFromXyz(-p->f274, 0.0f, 0.0f)).Q());
            qword a = Sub(c, Matrix(p)->r[3]);
            func_00244828(p, Sub(Add(Add(a, Vel(p->p270)), *(qword *)&dv), vel) / VU_FLOAT(&g_clock));
            break;
        }
        case 1: {
            qword t = Matrix(p->p270)->r[3];
            qword d = Sub(t, Matrix(p)->r[3]);
            qword imp = func_001C94E8(p, 0, *(qword *)&D_00328B80 * VU_FLOAT(Length(d) - p->f274));
            func_00244828(p, Sub(Add(imp, *(qword *)&dv), vel) / VU_FLOAT(&g_clock));
            break;
        }
        case 0: {
            func_00244828(p, *(qword *)&dv);
            qword fwd = Matrix(p)->r[0];
            if (func_0026DE50(p) && Dot(vel, fwd) > 0.0f) {
                VECTOR4 par, perp;
                func_0011FE60(vel, fwd, (qword *)&par, (qword *)&perp);
                func_00244828(p, *(qword *)&par * VU_FLOAT(-0.9375f));
                func_00244828(p, *(qword *)&perp * VU_FLOAT(-1.875f));
            } else {
                func_00244828(p, vel * VU_FLOAT(-1.875f));
            }
            break;
        }
        }
    }
    M3 m;
    func_0011CAE0(&m, p->f1DC, p->f1E0);
    M3 m2 = func_0011CFC0(Matrix(p), &m);
    qword w = func_0011D388(&m2) / VU_FLOAT(&g_clock);
    func_00244890(p, Sub(w, AngVel(p)) / VU_FLOAT(&g_clock));
}
