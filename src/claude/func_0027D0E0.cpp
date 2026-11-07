// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0027D0E0 (agents A54/A60/A73): adapted from Sly 2 func_00225E98 (zoom from the target's bounds or the controller).
// Length() reads its lane with an mtc1 lane asm taking the qword "r" so gcc emits the qmfc2 itself; that moves the
// saved-future lq/sq ahead of the VU chain as in the target. No register pins.
typedef int qword __attribute__((mode(TI)));
union V { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct RANGE { float lo, hi; };
struct SMP { float a, b, c, d; };
struct XF { M3 mat; qword pos; };
struct VTE { short d; short pad; XF *(*pfn)(void *); };
struct SHAPE { char pad[0x30]; float radius; };
struct O { int a[3]; VTE *vt; char pad[0x50 - 0x10]; void *component; char pad54[0xDC - 0x54]; SHAPE *shape; };
struct CONTROL { char pad[0x10]; float zoom; };
struct CM { char pad[0x134]; float aspect; };
struct S { int a[3]; VTE *vt; char pad[0x134 - 0x10]; CONTROL *control; char pad138[0x190 - 0x138]; O *target; int aim, follow;
           char pad19c[0x1BC - 0x19C]; RANGE range; float blend, velocity, strength; };
struct CLOCK { float t, dt; };
extern "C" {
void func_0028F680(void *, int, M4 *, float, M4 *);
float func_002A3160(float);
float func_0011EE68(void *, float);
float func_0011E730(float, float, float, float, SMP *, float *);
CM *func_001F4A80(void *);
extern CLOCK g_clock;
extern char D_00341FF0[];
extern float D_00329478[2], D_00329490[3];
extern SMP D_00329480;
}
static inline XF *Xf(void *o) { O *b = (O *)o; return b->vt[36].pfn((char *)b + b->vt[36].d); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Length(qword d)
{
    qword r, one;
    float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(d));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(r));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(r));
    return f;
}
static inline qword DifferenceR(qword b, const qword &a) { qword r; __asm__("vsub.xyzw %0,%2,%1" : "=j"(r) : "j"(b), "j"(a)); return r; }
static inline qword InverseRotate(const M3 &m, qword v)
{
    qword r = m.r[0], one, a, b, c;
    __asm__("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "+j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m.r[1]), "j"(m.r[2]), "j"(v));
    return r;
}
static inline qword ToVU(const qword &q) { qword r; __asm__("" : "=j"(r) : "0"(q)); return r; }
static inline float Max(float a, float b) { return a > b ? a : b; }
static inline float Min(float a, float b) { return a < b ? a : b; }
static inline float Abs(float x) { return __builtin_fabsf(x); }
static inline float Fraction(RANGE *range, float f) { if (range->lo == range->hi) return 0.0f; return (f - range->lo) / (range->hi - range->lo); }
static inline float Blend(RANGE *range, float u) { return (1.0f - u) * range->lo + u * range->hi; }
extern "C" void func_0027D0E0(S *p)
{
    if (p->target && p->follow) {
        M4 m;
        V future, offset, local, swapped;
        SMP spring;

        float radius = p->target->shape ? p->target->shape->radius : 0.0f;
        qword here = ToVU(Xf(p)->pos);
        float angle = func_002A3160(radius / (Length(Sub(here, Xf(p->target)->pos)) * 0.5f));
        angle = angle + angle;
        CLOCK *clock = &g_clock;
        angle = Max(angle, p->range.lo);
        func_0028F680(p->target->component, 0, &m, clock->dt, 0);
        qword end = ToVU(m.r[3]);
        future.q = end;
        offset.q = Sub(end, Xf(p->target)->pos);
        qword saved = future.q;
        float extent = radius + Length(offset.q);
        local.q = DifferenceR(Xf(p)->pos, saved);
        local.q = InverseRotate(Xf(p)->mat, local.q);
        swapped.f[0] = -local.f[1];
        swapped.f[1] = local.f[2];
        swapped.f[2] = local.f[0];
        CM *pcm = func_001F4A80(p);
        float desired;
        if (swapped.f[2] > 0.0001f) {
            float horizontal = func_002A3160((Abs(swapped.f[0]) + extent) / (swapped.f[2] * pcm->aspect));
            horizontal = horizontal + horizontal;
            float vertical = func_002A3160((Abs(swapped.f[1]) + extent) / swapped.f[2]);
            vertical = vertical + vertical;
            desired = Min(Max(horizontal, vertical), p->range.hi);
        } else
            desired = p->range.hi;
        desired = Max(desired, angle);
        float target = func_0011EE68(D_00341FF0, 1.0f - Fraction(&p->range, desired));
        float delta = Abs(target - p->blend);
        spring = D_00329480;
        float rate = (1.0f - delta) * D_00329478[0] + delta * D_00329478[1];
        spring.d *= rate; spring.a *= rate; spring.b *= rate;
        p->blend = func_0011E730(p->blend, p->velocity, target, g_clock.dt, &spring, &p->velocity);
    } else {
        if (p->control) {
            float blend = p->blend, zoom = p->control->zoom;
            p->velocity = (D_00329490[0] + blend * (D_00329490[1] + blend * D_00329490[2])) * zoom * Abs(zoom);
            p->blend = func_0011EE68(D_00341FF0, blend + p->velocity * g_clock.dt);
        }
    }
    p->strength = Blend(&p->range, 1.0f - p->blend);
}
