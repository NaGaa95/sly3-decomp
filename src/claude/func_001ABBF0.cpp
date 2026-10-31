// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M4 { U r[4]; };
struct VTE { short d; short pad; void *fn; };
struct ACTOR { char pad[0xC]; VTE *vt; char pad10[0x148 - 0x10]; void *x148; };
struct B { char pad[0xD4]; int xD4; char padD8[0x1CC - 0xD8]; int x1CC; };
struct C110 { char pad[0x10]; float g10; };
struct C { char pad[0x110]; C110 *p110; };
struct S {
    ACTOR *p0; int x4; int x8; int padC[2]; B *p14; int pad18[2]; float g20; int pad24[3]; int x30; int pad34; int x38; int pad3C;
    U v40; float g50; int pad54[5]; C *p68;
};
struct R { U v0; int pad10[4]; U v20; int pad30[9]; int x54; float g58; int pad5C; int x60; float g64; float g68; unsigned int x6C; };
struct SMP { float a, b, c; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
extern "C" {
extern float D_0036BB9C;
extern SMP D_00322480;
float func_002A3EE8(float y, float x);
int func_0013B500(void *p, int n);
float func_0022DFD8(B *p);
float func_0022DFB0(B *p);
void func_0022E330(B *p, U *pv, void *q, float g);
}
float GSmooth(float a, float b, float c, SMP *psmp, float *pg) __asm__("GSmooth__FfffP3SMPPf");
static inline M4 *Matrix(ACTOR *p)
{
    VTE *e = &p->vt[36];
    return ((M4 *(*)(void *))e->fn)((char *)p + e->d);
}
static inline float Clamp(float g, float lo, float hi) { float t; if (g < lo) t = lo; else if (hi < g) t = hi; else t = g; return t; }
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline float GMax(float a, float b) { return a > b ? a : b; }
static inline qword AddScaled(qword a, qword s, const U &b)
{
    qword t, r;
    __asm__("vmulx.xyzw %0, %1, %0x" : "=j"(t) : "j"(b.q), "0"(s));
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(t));
    return r;
}
static inline qword SubScaled(qword a, qword s, const U &b)
{
    qword t, r;
    __asm__("vmulx.xyzw %0, %1, %0x" : "=j"(t) : "j"(b.q), "0"(s));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(t));
    return r;
}
static inline qword ToVf(float f) { qword q; __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); return q; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
extern "C" void func_001ABBF0(S *ps, R *pr)
{
    U s;
    qword fwd, rev;
    float lift, height;
    if (ps->x8 != 0)
        return;
    {
        float *v = Matrix(ps->p0)->r[0].f;
        pr->g58 = func_002A3EE8(v[1], v[0]);
    }
    pr->x54 = 0;
    switch (ps->x38) {
    case 1:
        pr->g64 = 1.0f;
        pr->g68 = -10.0f;
        break;
    case 2:
        pr->g64 = 5.0f;
        pr->g68 = -3.5f;
        break;
    }
    if (ps->p0->x148 != ps->p68)
        return;
    if (ps->x30 >= 3) goto tail;
    if (ps->x30 > 0) goto a12;
    if (ps->x30 == 0) goto c0;
    goto tail;
a12:
    if (func_0013B500(ps->p14, 0xB)) {
        B *pb = ps->p14;
        float g;
        if (ps->x30 == 1) {
            g = ps->g20 + ps->g50 * 125.0f * ps->g50;
            if (pb->xD4 == 0) {
                float h = func_0022DFD8(pb);
                if (pb->x1CC & 2)
                    h += 100.0f;
                g = GMin(g, h);
            }
        } else {
            g = ps->g20 - ps->g50 * 125.0f * ps->g50;
            if (pb->xD4 == 0) {
                float h = func_0022DFB0(pb);
                if (pb->x1CC & 1)
                    h -= 100.0f;
                g = GMax(g, h);
            }
        }
        func_0022E330(pb, &ps->v40, 0, g);
        lift = 125.0f;
        height = ps->v40.f[2];
        goto liftValue;
    } else if (ps->x30 == 1) {
        fwd = Matrix(ps->p0)->r[3].q;
        {
            ACTOR *pa = ps->p0;
            VTE *e = &pa->vt[36];
            int dd = e->d;
            M4 *(*fn)(void *) = (M4 *(*)(void *))e->fn;
            qword t0 = ToVf(ps->g50 * 125.0f * ps->g50); // VU_FLOAT value: caller-saved in its vf reg across the Matrix() call (sp+0x30)
            s.q = t0;
            ps->v40.q = AddScaled(fwd, t0, fn((char *)pa + dd)->r[1]);
        }
    } else {
        rev = Matrix(ps->p0)->r[3].q;
        {
            ACTOR *pa = ps->p0;
            VTE *e = &pa->vt[36];
            int dd = e->d;
            M4 *(*fn)(void *) = (M4 *(*)(void *))e->fn;
            qword t0 = ToVf(ps->g50 * 125.0f * ps->g50);
            s.q = t0;
            ps->v40.q = SubScaled(rev, t0, fn((char *)pa + dd)->r[1]);
        }
    }
    lift = 50.0f;
    height = ps->v40.f[2];
    goto liftValue;
c0:
    ps->v40 = Matrix(ps->p0)->r[3];
    lift = 50.0f;
    height = ps->v40.f[2];
liftValue:
    ps->v40.f[2] = height + lift;
tail:
    pr->v20.q = Sub(ps->v40.q, pr->v0.q);
    if (func_0013B500(ps->p14, 0xB) && ps->p14->xD4 == 0) {
        float k, t;
        float c = 30.0f;
        float h = func_0022DFD8(ps->p14) - c;
        float d = GMin(300.0f, (h - c) * 0.5f);
        float e = d + c;
        float x = ps->g20;
        float h2 = h - d;
        if (x < e) {
            {
                float hi = 1.0f, lo = 0.0f, r = (e - x) / d;
                if (r < lo) t = lo; else if (hi < r) t = hi; else t = r;
            }
            k = -t * t * 150.0f;
        } else if (h2 < x) {
            {
                float hi = 1.0f, lo = 0.0f, r = (x - h2) / d;
                if (r < lo) t = lo; else if (hi < r) t = hi; else t = r;
            }
            k = t * t * 150.0f;
        } else {
            k = 0.0f;
        }
        ps->p68->p110->g10 = GSmooth(ps->p68->p110->g10, k, D_0036BB9C, &D_00322480, 0);
    }
    switch (ps->x8) {
    case 0:
    case 0xD:
        pr->x60 = 1;
        break;
    case 1:
    case 3:
    case 4:
        break;
    default:
        pr->x6C |= 1;
        break;
    }
}
