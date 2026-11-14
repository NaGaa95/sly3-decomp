// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Launch item hit response (vtable slot 7 of the item class, called from func_0020C1C0 with (this, shape, hit point, hit normal,
// segment end); the sibling slot 8 is func_0020D208). A shape owner of kind 0x65 just pulls the item velocity half way towards the
// owner's velocity at the hit point. Otherwise this is a rigid-body impulse like Sly 2 func_001CEB08: contact arm offset =
// -normal * radius (radius = radius * curve(t) clamped to at least 10), the owner's point velocity from func_0028BCD0, a normal
// impulse from the restitution, a friction impulse along (normal - friction * normalised tangent), func_00120A00 splits the two by
// the static fraction, velocity/angular velocity are updated, velocity.z is raised to 200 and the item is pushed out along the
// normal by max((point - end) . normal, 0) + 1.
// Matching notes: the mtc1 of a dot product has a "j" alternative so that the product stays a VU-class pseudo (vf1) while its
// qmfc2 stays an ordinary reload (same trick as H() in func_0011CDC8; the "x" output alternative can never match a float, so the
// alternative is never selected). Madd takes its origin as a VEC by value (the compiler copies it: vmove vf9,vf7), and Sub takes
// its second operand by const reference, which puts the incoming "end" quad in the last spill slot like the original.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct CLQ { float g0, g1, g2, gUnused; };
struct Self {
    char pad0[0x14]; float start, duration; char pad1C[4]; CLQ clqA; char pad30[0x40]; qword pos;
    char pad80[0x10]; U velocity; U acceleration; char padB0[0x20]; U angular; char padE0[0x10];
    float radius, restitution, friction;
};
struct Shape { void *frame; void *owner; };
struct Clock { float time, dt; };
extern Clock D_0036BB98;
extern qword D_00317530, D_00317560;
extern "C" {
int func_0013B500(void *, int);
void func_00280598(void *, qword, qword *, int);
void func_0020BE68(Self *, float);
qword func_0028BCD0(void *, void *, qword);
void func_00120A00(qword pos, qword p0, qword p1, qword *ppos, float *pt, float *pdist);
}
struct VEC { qword q; };
static inline VEC V(qword q) { VEC v; v.q = q; return v; }
// float splat (x used)
struct VF { qword q; VF(float g) { __asm__("qmtc2 %1,%0" : "=j"(q) : "r"(g)); } };
static inline qword Sub(qword a, const qword &b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Scale(qword a, VF s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
static inline qword ScaleQ(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
static inline qword Cross(qword a, qword b) { qword r; __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
// origin + axis * s.x
static inline qword AddScaled(qword origin, qword axis, VF s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(origin), "j"(axis), "j"(s.q));
    return r;
}
// origin + v * s.x
static inline qword Madd(VEC origin, VF s, qword v)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(origin.q), "j"(v), "j"(s.q));
    return r;
}
// a * s.x + b * t.x
static inline qword Blend(qword a, VF s, qword b, VF t)
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(s.q), "j"(b), "j"(t.q));
    return r;
}
static inline qword DotV(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline float GetX(qword q) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q)); return g; }
// "r,j": the j alternative only steers the register class of q; "=f,x": it can never match, so it is never selected
static inline float GetXVu(qword q) { float g; __asm__("mtc1 %1,%0" : "=f,x"(g) : "r,j"(q)); return g; }
static inline float Dot(qword a, qword b) { return GetXVu(DotV(a, b)); }
static inline qword Length(qword v)
{
    qword l = DotV(v, v), r;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(l));
    return r;
}
static inline qword Divide(qword v, VF s) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(s.q)); return r; }
static inline VEC Normalize(qword v)
{
    qword l = Length(v);
    VEC k;
    k.q = D_00317530;
    VEC dir;
    if (GetX(l) < 0.0001f) {
        dir = k;
    } else {
        qword d;
        __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(d) : "j"(v), "j"(l));
        dir.q = d;
    }
    return dir;
}
static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
static inline float Max(float a, float b) { return a < b ? b : a; }

extern "C" int func_0020CD88(Self *self, Shape *shape, qword point, qword normal, qword end)
{
    if (func_0013B500(shape->owner, 0x65)) {
        U sample;
        func_00280598(shape->owner, point, &sample.q, 0);
        float k = 0.5f;
        qword velocity = AddScaled(self->velocity.q, Sub(sample.q, self->velocity.q), k);
        self->velocity.q = velocity;
        self->acceleration.q = Divide(Sub(sample.q, velocity), k);
        func_0020BE68(self, k);
        return 1;
    }
    float t = (D_0036BB98.time - self->start) / self->duration;
    float radius = Max(self->radius * Curve(self->clqA, t), 10.0f);
    qword offset = Scale(normal, -radius);
    qword torque = Cross(offset, normal);
    qword other = func_0028BCD0(shape->frame, 0, point);
    float inertia = 2.5f / (radius * radius);
    qword relative = Sub(Add(self->velocity.q, Cross(self->angular.q, offset)), other);
    float factor = -1.0f - self->restitution;
    qword response = AddScaled(normal, Cross(torque, offset), inertia);
    float impulse = Dot(relative, normal) * factor / Dot(response, normal);
    qword after = AddScaled(relative, response, impulse);
    qword tangent = Sub(after, ScaleQ(normal, DotV(after, normal)));
    qword axis = Madd(V(normal), -self->friction, Normalize(tangent).q);
    float factor2 = -1.0f - self->restitution;
    qword frictionResponse = AddScaled(axis, Cross(Cross(offset, axis), offset), 2.5f / (radius * radius));
    float frictionImpulse = Dot(relative, normal) * factor2 / Dot(frictionResponse, normal);
    qword slide = AddScaled(relative, frictionResponse, frictionImpulse);
    slide = Sub(slide, ScaleQ(normal, DotV(slide, normal)));
    float along, distance;
    func_00120A00(D_00317560, tangent, slide, 0, &along, &distance);
    float unit = 1.0f;
    float second = along * frictionImpulse;
    float first = (unit - along) * impulse;
    self->velocity.q = Add(self->velocity.q, Blend(normal, first, axis, second));
    self->angular.q = AddScaled(self->angular.q, Blend(torque, first, Cross(offset, axis), second), 2.5f / (radius * radius));
    if (self->velocity.f[2] < 200.0f) {
        self->velocity.f[2] = 200.0f;
        func_0020BE68(self, 0.25f);
    }
    float lift = Max(GetX(DotV(Sub(point, end), normal)), 0.0f) + unit;
    self->pos = AddScaled(self->pos, normal, lift);
    return 1;
}
