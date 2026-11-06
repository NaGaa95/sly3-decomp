// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_00225BA0 (aim at the target or integrate the stick input).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union V { qword q; float f[4]; };
struct BOUND { float lo, hi; };
struct PO { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; void *pfn; };
struct CONTROL { float x, y, pad8, z; char pad10[0x2C - 0x10]; VTE *vt; };
struct INV { int flipX, flipY; float gx, gy; };
struct S { int a[3]; VTE *vt; char pad[0x134 - 0x10]; CONTROL *control; char pad138[0x190 - 0x138]; S *target; int aim; int pad198;
           float pitch, yaw, vpitch, vyaw; BOUND yawRange, pitchRange; char pad1bc[0x1CC - 0x1BC]; float strength; char pad1d0[0xC];
           int output; char pad1e0[8]; void *rotation; };
struct CLOCK { float t, dt; };
extern "C" {
extern CLOCK g_clock;
extern char D_00329468[];
M3 func_0011CBA0(qword);
void func_0011D048(const M3 *, float *, float *);
float func_0011E598(float, float, const void *, int, float);
INV *func_001A7B20(int);
float func_0011EE68(const BOUND *, float);
void func_0012F4F8(void *, qword);
}
float GLimitAbs(float, float);
static inline PO *Pos(S *o) { PO *(*pf)(void *) = (PO *(*)(void *))o->vt[36].pfn; return pf((char *)o + o->vt[36].d); }
static inline int Query(CONTROL *c, int i, int k) { int (*pf)(void *, int) = (int (*)(void *, int))c->vt[i].pfn; return pf((char *)c + c->vt[i].d, k); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
extern "C" void func_0027CD78(S *p)
{
    if (p->target && p->aim) {
        M3 m;
        float pitch, yaw;
        qword target;
        m = func_0011CBA0((target = Pos(p->target)->pos, Sub(target, Pos(p)->pos)));
        func_0011D048(&m, &pitch, &yaw);
        float dp = pitch - p->pitch;
        float dy = yaw - p->yaw;
        p->pitch = pitch; p->yaw = yaw;
        p->vpitch = dp; p->vyaw = dy;
    } else {
        if (p->control) {
            float x = GLimitAbs(p->control->x + p->control->z, 1.0f);
            float y = GLimitAbs(p->control->y, 1.0f);
            float strength = p->strength;
            float gain = (1.0f - strength) * 0.5f + strength;
            float limit = strength * 1.3f;
            INV *inv = func_001A7B20(3);
            float cubic = -x * x;
            cubic = cubic * x;
            float ax = cubic * inv->gx * gain;
            int flip = inv->flipX;
            if (Query(p->control, 4, 3))
                flip = !flip;
            if (flip)
                ax = -ax;
            if (ax * p->vpitch <= 0.0f)
                p->vpitch = 0.0f;
            float cubeY = y * y;
            cubeY = cubeY * y;
            float ay = cubeY * inv->gy * gain;
            flip = inv->flipY;
            if (Query(p->control, 5, 3))
                flip = !flip;
            if (flip)
                ay = -ay;
            if (ay * p->vyaw <= 0.0f)
                p->vyaw = 0.0f;
            CLOCK *clock = &g_clock;
            const void *damping = D_00329468;
            p->vpitch = func_0011E598(p->vpitch, 0.0f, damping, 0, clock->dt);
            p->vyaw = func_0011E598(p->vyaw, 0.0f, damping, 0, clock->dt);
            p->vpitch = GLimitAbs(p->vpitch + ax * clock->dt, limit * 0.9f);
            p->vyaw = GLimitAbs(p->vyaw + ay * clock->dt, limit * 0.8f);
            p->pitch += p->vpitch * clock->dt;
            p->yaw += p->vyaw * clock->dt;
        }
    }
    p->pitch = func_0011EE68(&p->pitchRange, p->pitch);
    p->yaw = func_0011EE68(&p->yawRange, p->yaw);
    if (p->output) {
        V v;
        v.q = Make(0.0f, -p->yaw, p->pitch);
        func_0012F4F8(p->rotation, v.q);
    }
}
