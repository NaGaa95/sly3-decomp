// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// State 22 per-frame update (mode transitions, blend curve, body matrix wobble, holder sound).
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Poly { float constant, linear, quadratic; };
struct Limits { float minimum, maximum; };
struct M4 { qword row[4]; };
struct Params { unsigned char pad0[0x88]; float coefficient; };
struct Input { unsigned char prefix[8]; float strength; unsigned char gap0C[0xC]; unsigned flags; };
struct Target { unsigned char pad0[0x28]; unsigned long flags; };
struct Object { unsigned char prefix0[0xC]; struct Method *methods; };
struct Sound { unsigned char pad0[0x44]; int busy; unsigned char gap48[0x14]; unsigned short flags; unsigned short count; };
struct SndRef { Sound *p; };
struct Clock { float time, step; };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); }
};
union Vector { qword q; float f[4]; };
struct Ring { qword direction; float time; float reach; unsigned char gap18[8]; };
struct Body { unsigned char pad0[0x8]; struct Link *link; };
struct Frame { unsigned char pad0[0x40]; M4 matrix; };
struct Link { unsigned char pad0[0xA0]; Frame *frame; };
union MatrixU { M4 m; float f[16]; };
struct Holder { unsigned char pad0[0x10]; qword value; unsigned char pad20[0x20]; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0xD8 - 0x10];
    struct Params *params;
    unsigned char gapDC[0x134 - 0xDC];
    struct Input *input;
    unsigned char gap138[0x1BC - 0x138];
    float turn;
    unsigned char gap1C0[0x260 - 0x1C0];
    Vector spin;
    unsigned char gap270[0x320 - 0x270];
    unsigned char context320[0x110C - 0x320];
    float heading;
    unsigned char gap1110[0x1AD4 - 0x1110];
    int mode;
    float entered;
    unsigned char gap1ADC[0x1AE8 - 0x1ADC];
    Object *partner;
    Target *target;
    unsigned char gap1AF0[0x1AFC - 0x1AF0];
    void *anchor;
    Holder *holder;
    int slot;
    float x1B08;
    int x1B0C;
    Body *body;
    float x1B14;
    float blend;
    float height;
    float timer;
    SndRef sound;
    unsigned char gap1B28[0x1B38 - 0x1B28];
    float rise;
    unsigned char gap1B3C[4];
    qword gather;
    unsigned char gap1B50[0];
    int count;
    unsigned head;
    unsigned char gap1B58[8];
    Ring ring[8];
};
extern "C" {
extern Clock D_0036BB98;
extern struct World { unsigned char pad0[0x4FF0]; float ground; } D_00475480;
extern char D_0036C700[];
extern Poly D_00324A40, D_00324A50, D_00324A60, D_00324A70, D_00324A80;
extern Limits D_00324A90, D_00341FF0;
extern float D_00324AA0;
extern float D_00324A98[2];
void func_0024E878(Actor *self, float angle);
int func_001A7A80(void *input, int mask, float threshold);
qword func_0011FD70(float a, float b, float c);
qword func_001205F0(qword v, float limit);
Sound *func_002459F8(int id);
void func_00244F08(Sound *s, Actor *owner);
void func_00244E08(Sound *s, float v);
void func_00244ED0(Sound *s, float v);
void func_00244CA8(Sound *s, float fade);
void func_002BBCD8(SndRef *ref, Sound *s);
void func_001E33E0(Actor *self);
void func_001E2A20(Actor *self, void *anchor);
void func_001E2E88(Actor *self, int k);
void func_002412C8(Target *t, float v);
void func_00241338(Target *t, float v);
void func_00173E00(struct World *world, int a, qword position, Actor *self);
void func_001854C8(void *context, int event, int value);
void func_001B7268(void *context, int kind, void *resource, void *record, float gain);
void func_001DCCF0(Actor *self, float v);
void func_001E3298(qword a, qword b, M4 *out, float g);
void func_0011D558(M4 *out, M4 *a, M4 *b);
void func_0011D768(M4 *out, M4 *in);
void func_0012F670(Body *body, M4 *m);
void *func_00292034(void *p, int c, unsigned n);
float func_002A4010(float v);
float func_002A35F8(float v);
float func_0011E940(float a, float b);
}
static inline qword Position(Actor *a)
{
    Method *m = &a->methods[36];
    return ((qword *)((qword *(*)(void *))m->function)((char *)a + m->adjustment))[3];
}
static inline qword Velocity(Actor *a)
{
    Method *m = &a->methods[38];
    return ((qword (*)(void *))m->function)((char *)a + m->adjustment);
}
static inline qword Spin(Actor *a)
{
    Method *m = &a->methods[39];
    return ((qword (*)(void *))m->function)((char *)a + m->adjustment);
}
static inline void SetSpin(Actor *a, qword v)
{
    Method *m = &a->methods[41];
    ((void (*)(void *, qword))m->function)((char *)a + m->adjustment, v);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulAdd(qword a, VU_FLOAT s, qword b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.qw));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x
	vwaitq
	vmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(l.qw));
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
/* dot product of the xyz lanes into lane x; two operands even for v.v (the second operand changes the reload needs,
   which reproduces the original VU spill register set) */
static inline qword DotQ(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword SqrtQ(qword d)
{
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    return d;
}
static inline qword LengthQ(qword v) { return SqrtQ(DotQ(v, v)); }
static inline qword PlanarLengthQ(qword v)
{
    qword d;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    return SqrtQ(d);
}
static inline float ToFloat(qword q) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q)); return g; }
/* lane x as a float kept in a GPR (the FPU copy is made by reload where it is needed) */
static inline float ToFloatG(qword q) { float g; __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(q)); return g; }
static inline float Length(qword v) { return ToFloat(LengthQ(v)); }
static inline float PlanarLength(qword v) { return ToFloat(PlanarLengthQ(v)); }
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float TopZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
/* volatile: keeps the extraction after the preceding sqrt.s (scheduling barrier, as in the original) */
static inline float GetZv(qword q) { float z; __asm__ __volatile__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword MakeW(float x, float y, float z)
{
    Vector w;
    w.q = Make(x, y, z);
    return w.q;
}
/* volatile: the original issues the lane extraction only after the sqrt chain (scheduling barrier) */
static inline float GetYv(qword q) { float y; __asm__ __volatile__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
/* earlyclobber result: keeps local-alloc from giving sqrt.s the register of its dying operand */
static inline float SqrtA(float v) { float r; __asm__("sqrt.s %0,%1" : "=&f"(r) : "f"(v)); return r; }
static inline float maxf(float a, float b) { return a > b ? a : b; }
static inline float minf(float a, float b) { return a < b ? a : b; }
static inline float Eval(const Poly *p, float t) { return p->constant + t * (p->linear + t * p->quadratic); }
static inline float Clamp(float value, const Limits *lim)
{
    float low = lim->minimum;
    float high = lim->maximum;
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
static inline void Stop(SndRef *r)
{
    if (r && r->p) {
        func_00244CA8(r->p, 0.0f);
        func_002BBCD8(r, 0);
    }
}
static inline int CanFire(Actor *self, qword vel)
{
    int go = 0;
    if (__builtin_fabsf(GetZ(vel)) < 600.0f && PlanarLength(vel) < 600.0f && Length(Spin(self)) < 8.0f
        && 0.9f < *(float *)((char *)*(void **)((char *)self + 0x50) + 0x68))
        go = 1;
    return go;
}
extern "C" void func_001E3488(Actor *self)
{
    int mode;
    func_0024E878(self, self->heading);
    qword pos = Position(self);
    qword vel = Velocity(self);
    Target *target = self->target;
    if (target) {
        float planar = PlanarLength(vel);
        if ((int)(target->flags >> 56) & 1) {
            if (self->mode == 0 && self->holder && planar < 500.0f && __builtin_fabsf(GetZ(vel)) < 1000.0f)
                func_002412C8(target, 1.0f);
        } else if (850.0f < planar || GetZ(vel) < -2000.0f) {
            func_00241338(target, 0.2f);
        } else {
            self->height = D_00324AA0;
        }
    }
    {
        float vz = GetZ(vel);
        self->height = maxf(self->height, GetZ(pos) + vz * vz / (self->params->coefficient * -2.0f));
        if (self->holder) {
            /* index term first: the original adds (1 - slot) * 0x40 to the holder base in this operand order */
            Holder *h = (Holder *)(((1 - self->slot) << 6) + (int)self->holder);
            self->height = maxf(self->height, GetZ(h->value) - self->spin.f[2] + 562.0f);
        }
    }
    do {
        mode = self->mode;
        if (mode < 2) {
          if (mode >= 0) {
            if (func_001A7A80(self->input, 0x80, 0.0f)) {
                self->x1B14 = D_0036BB98.time;
                qword base = Spin(self);
                qword dir = func_0011FD70(self->turn + 1.5707964f, self->input->strength * 14.0f, 0.0f);
                SetSpin(self, Add(base, func_001205F0(Sub(dir, base), 4.0f)));
                Sound *s = func_002459F8(0x5F);
                func_00244F08(s, self);
                func_00244E08(s, 1.0f);
                func_00244ED0(s, -0.7f);
            }
          }
        }
        switch (self->mode) {
        case 0:
            if (D_0036BB98.time - self->x1B08 < 0.15f && func_001A7A80(self->input, 0x40, 0.25f)
                && __builtin_sqrtf(self->params->coefficient * -630.0f) > GetZv(vel)) {
                Method *set = &self->methods[40];
                void (*fn)(void *, qword) = (void (*)(void *, qword))set->function;
                int adj = set->adjustment;
                fn((char *)self + adj, vel = MakeW(GetX(vel), GetY(vel), __builtin_sqrtf(self->params->coefficient * -630.0f)));
                func_001E33E0(self);
                func_001E2A20(self, self->anchor);
            }
            break;
        case 1:
            if (0.15f < D_0036BB98.time - self->entered) {
                int played = 0;
                float rise = self->rise * self->rise / (self->params->coefficient * -2.0f);
                if (func_001A7A80(self->input, 0x40, 0.4f)) {
                    rise = Eval(&D_00324A40, rise);
                    func_001E2A20(self, self->anchor);
                    played = 1;
                } else {
                    if (self->input->flags & 0x20)
                        rise = Eval(&D_00324A60, rise);
                    else
                        rise = Eval(&D_00324A50, rise);
                    Sound *s = func_002459F8(0x1B);
                    func_00244F08(s, 0);
                    func_00244E08(s, 0.7f);
                }
                rise = minf(rise, minf(self->height, D_00475480.ground) - TopZ(pos));
                if (rise > 0.0f) {
                    float p = rise * -2.0f;
                    float z = SqrtA(self->params->coefficient * p);
                    float y = GetYv(vel);
                    Method *set = &self->methods[40];
                    void (*fn)(void *, qword) = (void (*)(void *, qword))set->function;
                    int adj = set->adjustment;
                    float x = GetX(vel);
                    fn((char *)self + adj, vel = MakeW(x, y, z));
                }
                if (850.0f < rise)
                    func_00173E00(&D_00475480, 0, Position(self), self);
                func_001E2E88(self, 0);
                func_001E33E0(self);
                if (played)
                    func_001854C8(D_0036C700, 0x5E, self->x1B0C);
            }
            break;
        case 2:
            if (1.0f < D_0036BB98.time - self->entered || CanFire(self, vel))
                func_001B7268(self->context320, self->holder ? 0 : 8, 0, 0, 1.0f);
            break;
        }
    } while (self->mode != mode);
    if (self->mode != -1) {
        float t = D_0036BB98.time - self->x1B14;
        self->blend = Clamp(Eval(&D_00324A70, t), &D_00341FF0);
        func_001DCCF0(self, (1.0f - self->blend) * 1.0f + self->blend * 2.0f);
        if (self->mode == 0) {
            if (1250.0f < __builtin_fabsf(GetZ(vel))) {
                if (self->partner) {
                    Method *m = &self->partner->methods[8];
                    ((void (*)(void *))m->function)((char *)self->partner + m->adjustment);
                }
            } else if (0.5f < D_0036BB98.time - self->entered && self->holder && self->partner) {
                Method *m = &self->partner->methods[9];
                ((void (*)(void *))m->function)((char *)self->partner + m->adjustment);
            }
        }
        if (self->body) {
            MatrixU m;
            M4 out;
            M4 product;
            M4 t2;
            M4 t1;
            M4 inverse;
            func_00292034(&m, 0, 0x40);
            int last = -1;
            float *mf = m.f;
            mf[0] = mf[5] = mf[10] = mf[15] = 1.0f;
            for (int i = 0; i < self->count; i++) {
                int back = i - 7;
                Ring *r = &self->ring[(self->head - back) & 7];
                float age = D_0036BB98.time - r->time;
                float k = func_002A4010(age * -5.0f);
                if (__builtin_fabsf(k) < 0.05f)
                    continue;
                last = i;
                float strength = k * r->reach;
                strength = strength * func_002A35F8(age * 15.0f);
                float g = func_002A4010(strength * -0.7f);
                qword d = r->direction;
                func_001E3298(MulAdd(pos, VU_FLOAT(-75.0f), d), d, &out, g);
                func_0011D558(&product, &out, &m.m);
                m.m = product;
            }
            self->count = last + 1;
            qword old = self->gather;
            qword delta = func_001205F0(Sub(Velocity(self), self->gather), D_0036BB98.step * 20000.0f);
            self->gather = Add(old, delta);
            float len = ToFloatG(LengthQ(self->gather));
            float f = Clamp(Eval(&D_00324A80, len * 0.00066666668f), &D_00324A90);
            if (1.0f < f) {
                func_001E3298(pos, Scale(self->gather, VU_FLOAT(len)), &out, f);
                func_0011D558(&product, &m.m, &out);
                m.m = product;
            }
            M4 *inv = &inverse;
            M4 *cur = &out;
            M4 *mid = &t1;
            M4 *res = &t2;
            out = self->body->link->frame->matrix;
            func_0011D768(inv, cur);
            func_0011D558(mid, inv, &m.m);
            func_0011D558(res, mid, cur);
            product = t2;
            func_0012F670(self->body, &product);
        }
        if (self->holder) {
            float len = PlanarLength(Cross(Spin(self), self->spin.q));
            if (150.0f < len)
                self->timer -= len * D_0036BB98.step;
            if (self->timer < 0.0f) {
                Stop(&self->sound);
                Sound *s = func_002459F8(0x6F);
                func_00244F08(s, 0);
                func_002BBCD8(&self->sound, s);
                func_00244E08(self->sound.p, 0.8f);
                func_00244ED0(self->sound.p, -0.5f);
                self->timer += func_0011E940(D_00324A98[0], D_00324A98[1]);
            } else if (self->sound.p) {
                Sound *s = self->sound.p;
                int v = 0;
                if (s->busy == 0) {
                    v = s->count != 0 || (s->flags & 1);
                    v ^= 1;
                }
                if (v)
                    Stop(&self->sound);
            }
        }
    }
}
