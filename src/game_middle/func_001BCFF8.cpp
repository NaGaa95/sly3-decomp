// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001BCFF8: sphere-vs-moving-plane sweep test (ballistic body vs a HIT {object, radius, plane, vec}).
// predicts the body (position + velocity + gravity * dt), moves the plane into world space, finds the penetration depth and
// the correction offset; writes the cost, the predicted position and the corrected velocity.
// Match keys: g (gravity) is read through a flagless qword ref so that the dead VU_FLOAT temp stores get a true dependence on the g load (sched1 priority) and come out first;
// asm helper operand numbering (Xform r0 first, Scale scalar first) orders the reload vf registers; GFromVfJ/GFromVfJ3 (allocation-only "j" operands) give the recognised qmfc2 reload
// and the original vf numbering; the splat of dt for the second gravity use is a named VU_FLOAT before the g load.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M4 { U r[4]; };
struct VTE { short d; short pad; void *fn; };
struct ACCEL { char pad0[0x80]; qword g; };
struct BODY { char pad0[0xC]; VTE *vt; char pad10[0xD8 - 0x10]; ACCEL *accel; };
struct HOLDER { BODY *body; };
struct SPACEOBJ { char pad0[0xC]; VTE *vt; };
struct HIT { int pad0; SPACEOBJ *object; float radius; qword *plane; qword vec; };
extern "C" {
extern qword D_00317560;
extern float D_003457C4;
void func_0028F730(void *, void *, float, float *, float *);
void *func_002BA008(void *);
void *func_002BA000(void *);
qword *func_002B9FF0(qword *, qword);
void func_00119ED8(qword *, qword, float);
}

struct VECTOR { qword q; VECTOR() { (void)func_002BA008(this); } };
struct VUF { qword q; VUF() { (void)func_002BA000(this); } };
struct PLANE { U u; void Assign(qword v) { func_002B9FF0(&u.q, v); } void Set(qword n, float d) { func_00119ED8(&u.q, n, d); } };
static inline qword Position(BODY *b) { VTE &e = b->vt[36]; return ((M4 *(*)(void *))e.fn)((char *)b + e.d)->r[3].q; }
static inline qword Velocity(BODY *b) { VTE &e = b->vt[38]; return ((qword (*)(void *))e.fn)((char *)b + e.d); }
static inline void *GetSpace(SPACEOBJ *o, M4 *out) { VTE &e = o->vt[37]; return ((void *(*)(void *, M4 *))e.fn)((char *)o + e.d, out); }
struct VU_FLOAT { qword q; VU_FLOAT() {} VU_FLOAT(float f) { __asm__("mfc1 %0,%1" : "=r,j"(q) : "f,f"(f)); } };
struct VF2 { qword q; };
static inline VF2 VuFloat(float g) { VF2 v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword AddScaled(qword base, VU_FLOAT s, qword v)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0
	vmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(v), "j"(s.q));
    return r;
}
static inline qword AddScaled2(qword base, qword v1, VF2 s1, qword v2, VF2 s2)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0
	vmaddax.xyzw $ACC,%2,%3x
	vmaddx.xyzw %0,%4,%5x" : "=j"(r) : "j"(base), "j"(v1), "j"(s1.q), "j"(v2), "j"(s2.q));
    return r;
}
static inline qword AddScaled3(qword base, VU_FLOAT s1, qword v1, qword v2, VF2 s2)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0
	vmaddax.xyzw $ACC,%2,%3x
	vmaddx.xyzw %0,%4,%5x" : "=j"(r) : "j"(base), "j"(v1), "j"(s1.q), "j"(v2), "j"(s2.q));
    return r;
}
static inline qword AddScaledB(qword base, qword v, VF2 s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0
	vmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(v), "j"(s.q));
    return r;
}
static inline float GFromVf(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GFromVf2(qword q) { float x; __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(q)); return x; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword SqDot(qword v)
{
    qword one, d;
    __asm__("vmul.xyz %0,%2,%2
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    return d;
}
static inline qword LengthDot(qword v)
{
    qword one, d, l;
    __asm__("vmul.xyz %0,%2,%2
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword ScaleRecip(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%1x
	vwaitq
	vmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword Rot(const M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%2,%1x
	vmadday.xyz $ACC,%3,%1y
	vmaddz.xyz %0,%4,%1z" : "=j"(r) : "j"(v), "j"(m->r[0].q), "j"(m->r[1].q), "j"(m->r[2].q));
    return r;
}
static inline qword Xform(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%2x
	vmadday.xyz $ACC,%3,%2y
	vmaddaz.xyz $ACC,%4,%2z
	vmaddw.xyz %0,%5,$vf0w" : "=j"(r) : "j"(m.r[0].q), "j"(v), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT s) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(s.q), "j"(v)); return r; }
/* float readback of a VU register through a GPR (qmfc2 + mtc1); the repeated "j" input operands are allocation-only: they keep q a VU-class pseudo
   (so its stores stay sqc2) and set the local-alloc priority/numbering of the VU temporaries. */
static inline float GFromVfJ(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q), "j"(q)); return x; }
static inline float GFromVfJ3(qword q, qword o) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q), "j"(q), "j"(o), "j"(o)); return x; }
struct V4 { qword q; V4() {} V4(const qword &a) { q = a; } };
static inline qword Zero() { qword r; __asm__("vsub.xyzw %0,$vf0,$vf0" : "=j"(r)); return r; }
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float fabsf_(float x) { return x < 0 ? -x : x; }
static inline float SqrtF(float x) { float r; __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(x)); return r; }

extern "C" void func_001BCFF8(HOLDER *self, float dt, HIT *h, float *cost, qword *outPos, qword *outVel)
{
    U delta0;
    qword position = Position(self->body);
    qword velocity = Velocity(self->body);
    M4 frame;
    M4 *pf = &frame;
    qword v2 = AddScaled(velocity, VU_FLOAT(dt), *(qword *)((char *)self->body->accel + 0x80));
    qword pred = AddScaled2(position, velocity, VuFloat(dt * 0.5f), v2, VuFloat(dt * 0.5f));
    func_0028F730(GetSpace(h->object, pf), 0, dt, (float *)pf, 0);
    float depth;
    qword push;
    if (h->plane) {
        qword plane = *h->plane;
        VECTOR pv;
        pv.q = plane;
        qword n = Rot(pf, plane);
        qword nn = ScaleRecip(n, LengthDot(n));
        qword lq;
        {
            PLANE lp;
            lp.Assign(plane);
            lp.Set(nn, lp.u.f[3] + GFromVf(Dot(frame.r[3].q, nn)));
            lq = lp.u.q;
        }
        VUF d, one;
        qword ov, dv;
        __asm__("vmul.xyz %0,%2,%3
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddaz.x $ACC,%1,%0z
	vmsubw.x %0,%1,%2w" : "=&j"(dv), "=&j"(ov) : "j"(lq), "j"(pred));
        one.q = ov;
        d.q = dv;
        float dist = GFromVfJ3(dv, ov);
        depth = -dist;
        if (depth > 0.0f) {
            VU_FLOAT ds(depth);
            VECTOR v;
            push = Scale(lq, ds);
            v.q = lq;
        } else {
            depth = 0.0f;
            push = Zero();
        }
    } else {
        depth = 0.0f;
        push = Zero();
    }
    qword A = Sub(Xform(frame, h->vec), pred);
    delta0.q = A;
    V4 dd(A);
    qword delta = dd.q;
    float radius = h->radius;
    float len2 = GFromVfJ(SqDot(delta));
    if (len2 < radius * radius && depth == 0.0f) {
        if (cost) *cost = SqrtF(len2) - radius;
        if (outPos) *outPos = pred;
        if (outVel) *outVel = v2;
        return;
    }
    float adz = fabsf_(delta0.f[2]);
    if (radius < adz || dt == 0.0f) {
        if (cost) *cost = adz + 1010000.0f;
        if (outPos) *outPos = position;
        if (outVel) *outVel = v2;
        return;
    }
    U dir;

    dir.q = Sub(delta, push);
    const qword *zp = &D_00317560;
    dir.f[2] = 0.0f;

    qword len = LengthDot(dir.q);
    if (GFromVf2(len) < 0.0001f)
        dir.q = *zp;
    else
        dir.q = ScaleRecip(dir.q, len);
    float t = GFromVf(len) - SqrtF(h->radius * h->radius - adz * adz);
    qword offset = AddScaledB(push, dir.q, VuFloat(t));
    VU_FLOAT s1(dt);
    qword g3 = *(qword *)((char *)self->body->accel + 0x80);
    qword v3 = AddScaled3(velocity, s1, g3, offset, VuFloat(2.0f / dt));
    V4 ovv(v3);
    if (cost) *cost = GMin(D_003457C4 * 2.0f * GFromVf(LengthDot(offset)) / dt, 1000000.0f);
    if (outPos) *outPos = AddScaled2(position, velocity, VuFloat(dt * 0.5f), v3, VuFloat(dt * 0.5f));
    if (outVel) *outVel = ovv.q;
}
