// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Guard mover update: pick the nearest target, run the mode transitions (route / points / chase / side step / re-path),
// choose a heading for the mode, steer away from nearby movers (closest approach of the predicted planar positions,
// clipped by the nav path), then spring the turn rate toward the heading; hands off after 5 s in kind 4.
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; void *call; };
struct M4 { qword r[4]; };
struct SMP { float fast, slow, dtFast; };
struct Tuning { unsigned char pad0[0xC]; SMP smp; float turn; };
struct Path { unsigned char pad0[0xD8]; int count; unsigned char padDC[8]; qword *items; };
struct Frame { qword r[3]; unsigned char pad30[0xB0 - 0x30]; qword vel; };
struct Poly { float constant, linear, quadratic; };
struct Clock { float time, step; };
struct Self {
    unsigned char pad00[0xC];
    Method *methods;
    unsigned char pad10[0x4C - 0x10];
    Frame *frame;
    unsigned char pad50[0x1B0 - 0x50];
    int kind;
    float kindTime;
    int state;
    unsigned char pad1BC[0x1C0 - 0x1BC];
    int mode;
    float modeTime;
    unsigned char pad1C8[0x1DC - 0x1C8];
    Tuning *tuning;
    unsigned char pad1E0[0x218 - 0x1E0];
    float lean;
    unsigned char pad21C[0x220 - 0x21C];
    float extent;
    unsigned char pad224[0x22C - 0x224];
    float turn;
    int turnRate;
    unsigned char pad234[0x250 - 0x234];
    void *path;
    Self *target;
    Path *points;
    float settle;
    int side;
    float sideTime;
    Path *route;
    int routeFlag;
    unsigned char pad270[0x3D0 - 0x270];
    float range;
    unsigned char pad3D4[0x428 - 0x3D4];
    float reach;
    unsigned char pad42C[0x554 - 0x42C];
    Self *next;
};
struct List { Self *first; Self *last; int linkOffset; };
extern "C" {
extern List D_00479BEC;
extern Clock D_0036BB98;
extern qword D_00317530, D_00317550, D_00317560;
extern Poly D_00325C20;
Self *func_00218E98(Self *self);
void func_002171E8(Self *self, int mode);
float func_0022DFD8(Path *path);
int func_001ED170(void *path, qword pos, int flags);
void func_00217938(Self *self);
float func_00217470(Self *self, Path *path, int flag);
void func_00217328(Self *self, qword position, qword reference);
qword func_001C9428(int n, Self *self, qword v);
qword func_001C94E8(int n, Self *self, qword v);
float func_001205C8(qword v);
float func_0011E3B8(float g);
void func_00120A00(qword pos, qword p0, qword p1, qword *ppos, float *pt, float *pdist);
int func_0011E9F0(float a, float b, float eps);
int func_001ED190(void *path, qword v, qword *pv, int n);
float func_0011E560(float g, float gMax);
float func_0011E598(float gCur, float gTarget, float dt, SMP *psmp, float *pdv);
void func_00217650(Self *self);
void func_002BEE98(void *object, int flags);
}
union Vector { qword q; float f[4]; };
struct Guard {
    int storage;
    ~Guard() { func_002BEE98(this, 2); }
};
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline M4 *Matrix(Self *o)
{
    Method *m = &o->methods[36];
    return ((M4 *(*)(void *))m->call)((char *)o + m->delta);
}
static inline qword Velocity(Self *o)
{
    Method *m = &o->methods[38];
    return ((qword (*)(void *))m->call)((char *)o + m->delta);
}
static inline qword Zero() { qword r; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(r)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Scale(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s), "j"(a)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword SqrtQ(qword d) { qword l; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d)); return l; }
static inline qword Length(qword v) { return SqrtQ(Dot(v, v)); }
static inline qword LengthXY(qword v)
{
    qword d;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    return SqrtQ(d);
}
static inline qword Planar(qword v, qword up) { return Sub(v, Scale(up, Dot(v, up))); }
static inline float GetX(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline float GetY(qword q) { float g; __asm__("prot3w %0, %1" : "=r"(g) : "r"(q)); return g; }
static inline float GetZ(qword q) { float g; __asm__("pextuw %0, $0, %1" : "=r"(g) : "r"(q)); return g; }
static inline qword MulT(const Frame *m, qword v)
{
    qword q, one, a, b, c;
    q = m->r[0];
    __asm__("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "+j"(q), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return q;
}
static inline qword Div(qword d, qword l)
{
    qword dir;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(dir) : "j"(d), "j"(l));
    return dir;
}
static inline float ToFloat(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline float GetXq(qword q) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(q)); return g; }
static inline qword NormalizeSafe(Vector *out, const qword &dflt, float eps)
{
    register qword g asm("$2") = *(volatile qword *)&out->q; /* the one register pin: the target reads the vector into $v0, then qmtc2 */
    qword vv = g;
    qword l = Length(vv);
    if (GetXq(l) < eps)
        out->q = dflt;
    else
        out->q = Div(vv, l);
    return l;
}
static inline int Equal(qword a, qword b)
{
    return func_0011E9F0(GetX(a), GetX(b), 0.0001f) && func_0011E9F0(GetY(a), GetY(b), 0.0001f) && func_0011E9F0(GetZ(a), GetZ(b), 0.0001f);
}
static inline float Max(float a, float b) { return a < b ? b : a; }
static inline float Eval(const Poly *p, float t) { return p->constant + t * (p->linear + t * p->quadratic); }

static inline int IsFar(Self *self, Path *points, qword goal)
{
    return self->extent < GetX(LengthXY(Sub(points->items[points->count - 1], goal)));
}
extern "C" void func_00216680(Self *self)
{
    qword goal;
    qword pos = Matrix(self)->r[3];
    float dist;
    Self *target = func_00218E98(self);
    self->target = target;
    if (target) {
        goal = Matrix(target)->r[3];
        dist = GetX(LengthXY(Sub(goal, pos)));
    } else {
        goal = pos;
        dist = 0.0f;
    }
    int mode;
    do {
        mode = self->mode;
        switch (mode) {
        case 0:
            if (self->target && self->target->state != 2 && dist < self->target->reach)
                func_002171E8(self, 2);
            break;
        case 1:
            if (self->target && self->target->state != 2 && dist < self->target->reach)
                func_002171E8(self, 2);
            else if (func_0022DFD8(self->points) - self->settle < self->extent)
                func_002171E8(self, 0);
            break;
        case 2:
            if (!self->target && self->route)
                func_002171E8(self, 1);
            else if (self->path && !func_001ED170(self->path, pos, 0))
                func_002171E8(self, 4);
            else if (self->kind == 4 && dist < self->range * 0.75f)
                func_002171E8(self, 3);
            break;
        case 4:
            if (!self->path || func_001ED170(self->path, pos, 0))
                func_002171E8(self, 2);
            break;
        case 3:
            if (!self->target && self->route)
                func_002171E8(self, 1);
            else if (self->path && !func_001ED170(self->path, pos, 0))
                func_002171E8(self, 4);
            else if (self->range < dist)
                func_002171E8(self, 2);
            else {
                switch (self->side) {
                case 0:
                case 1:
                    if (D_0036BB98.time - self->sideTime > 45.0f)
                        func_00217938(self);
                    break;
                default:
                    func_00217938(self);
                    break;
                }
                switch (self->side) {
                case 0:
                case 1:
                    break;
                default:
                    func_002171E8(self, 0);
                    break;
                }
            }
            break;
        }
    } while (self->mode != mode);

    float heading = 0.0f;
    switch (self->mode) {
    case 0:
        heading = func_00217470(self, self->route, self->routeFlag);
        break;
    case 1:
        heading = func_00217470(self, self->points, 1);
        break;
    case 2:
    case 4: {
        Path *points = self->points;
        if (points->count < 2 || IsFar(self, points, goal))
            func_00217328(self, pos, goal);
        heading = func_00217470(self, self->points, 1);
        break;
    }
    case 3:
        if (self->target) {
            float offset;
            switch (self->side) {
            case 0:
                offset = -1.5707964f;
                break;
            case 1:
                offset = 1.5707964f;
                break;
            default:
                offset = 0.0f;
                break;
            }
            Vector local;
            local.q = func_001C9428(0, self, Matrix(self->target)->r[3]);
            heading = func_0011E3B8(offset + func_001205C8(local.q));
        }
        break;
    }

    qword ahead;
    qword accum = Zero();
    ahead = AddScaled(pos, Velocity(self), VU_FLOAT(0.5f));
    Guard guard;
    for (Self *o = D_00479BEC.first; o; o = o->next) {
        if (o == self)
            continue;
        if (o->state != 2)
            continue;
        Vector opos;
        opos.q = Matrix(o)->r[3];
        qword away = Sub(pos, opos.q);
        qword rel = Sub(ahead, AddScaled(opos.q, Velocity(o), VU_FLOAT(0.5f)));
        qword up = D_00317550;
        Vector closest;
        func_00120A00(D_00317560, Planar(away, up), Planar(rel, up), &closest.q, 0, 0);
        qword len = NormalizeSafe(&closest, D_00317530, 0.0001f);
        float gap = Max(0.0f, ToFloat(len) - o->extent - self->extent);
        float k = 0.5f;
        if (gap < self->extent)
            accum = AddScaled(accum, closest.q, VU_FLOAT((1.0f - gap / self->extent) * k * 6000.0f));
    }
    qword flat = Planar(accum, D_00317550);
    qword zero = D_00317560;
    accum = flat;
    int avoid = !Equal(zero, accum);
    if (avoid) {
        Vector dest;
        dest.q = Add(pos, accum);
        Vector hit;
        if (self->path && func_001ED190(self->path, dest.q, &hit.q, 1)) {
            dest = hit;
            accum = Sub(dest.q, pos);
        }
        Vector local;
        local.q = func_001C94E8(0, self, accum);
        heading = func_001205C8(local.q);
    }
    Tuning *tuning = self->tuning;
    float turn = tuning->turn;
    SMP smp = tuning->smp;
    if (avoid) {
        float g = Eval(&D_00325C20, GetX(Length(accum)));
        smp.fast *= g;
        turn *= g;
    } else {
        switch (self->mode) {
        case 0:
            turn *= 10.0f;
            smp.fast *= 10.0f;
            break;
        case 4:
            turn *= 5.0f;
            smp.fast *= 5.0f;
            if (1.5707964f <= __builtin_fabsf(heading))
                self->lean = 0.5f;
            break;
        default: {
            union { qword q; float f[4]; } local;
            local.q = MulT(self->frame, self->frame->vel);
            if (local.f[2] * heading < 0.0f)
                smp.fast *= 2.5f;
            break;
        }
        }
    }
    self->turn = func_0011E598(self->turn, func_0011E560(heading, turn), D_0036BB98.step, &smp, 0);
    self->turnRate = 0;
    if (self->kind == 4 && D_0036BB98.time - self->kindTime > 5.0f)
        func_00217650(self);
}
/* Limit pair read by func_00217040 (same original translation unit). The original keeps it right after this function's two
   jump tables (0x325C30 / 0x325C50, 8-byte aligned at 0x325C68); defining it here makes the whole .rodata block 0x325C30..0x325C70
   one verifiable section (the assembler pads the table section to 16 bytes). */
struct Limit { float minimum, maximum; };
extern const Limit D_00325C68 = { -3.5f, -1.0f };
