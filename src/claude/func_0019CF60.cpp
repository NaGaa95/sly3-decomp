// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0019CF60: Sly 3 version of Sly 2 func_00180668 (adds state 5 and a 6-entry dispatch table).
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
typedef union U { qword q; float f[4]; int i[4]; } U;
struct NODE;
struct VTE { short delta, pad; void *fn; };
struct M4 { U r[4]; };
struct FRAME { char pad0[0xA0]; void *space; };
struct NODE { char pad0[0xC]; VTE *vt; char pad10[0x18]; struct { ulong lo : 56; ulong hi : 8; } flags; char pad30[0x1C]; FRAME *frame; char pad50[0x8C]; void *group; };
struct LM { float low, high; };
struct RULE { int distanceEnabled, angleEnabled; LM enterDistance, stayDistance, enterAngle, stayAngle; };
struct POLY { float a, b, c; };
struct CLOCK { float t, dt; };
struct P {
    NODE node; char padE0[0x1C8 - 0xE0];
    NODE *target; int x1CC; char pad1D0[0x20];
    int state; float stateTime; int cooldown, active; void *binding; void *curve; float progress; int pad20C;
    qword previousSelf, previousTarget; float stamp, heading; char pad238[8]; qword output; char pad250[0x60];
    RULE rules[6]; float scale; char pad3A4[0xC]; POLY remaining; char pad3BC[4]; POLY angle; char pad3CC[4];
    POLY simpleAngle; char pad3DC[4]; LM simpleClamp;
};
struct VU_FLOAT { qword qw; };
extern "C" {
extern qword D_00317560, D_00317530;
extern POLY D_00321FE0, D_00321FF0, D_00322010;
extern LM D_00322000, D_00341FF0;
extern CLOCK g_clock;
extern char D_0036BD20[], D_00475480[];
void func_0023C660(P *);
int func_0019BAA0(P *);
void func_0019DC10(P *, int);
NODE *func_0019BC68(P *);
qword func_001C94E8(void *, P *, qword);
float func_001205C8(qword);
float func_0011E3B8(float);
int func_0011EE30(LM *, float);
qword func_0028E990(void *, void *, qword);
void func_001EC688(void *, qword, qword, void *);
void func_0022EEA0(void *, qword, void *, qword *, float, qword *, float *, float *);
float func_0022DFD8(void *);
float func_00171C98(void *);
int func_0017E208(void *, int, int, void *, int, NODE **);
qword func_001205F0(qword, float);
}
static inline M4 *Matrix(NODE *p) { VTE *e = &p->vt[36]; return ((M4 * (*)(void *)) e->fn)((char *)p + e->delta); }
static inline qword Pos(NODE *p) { return Matrix(p)->r[3].q; }
static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.qw) : "r"(g)); return v; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwDot(qword a, qword b) { qword r, one; __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b)); return r; }
static inline qword QwSqrt(qword a) { qword r; __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(r) : "j"(a)); return r; }
static inline qword QwDivide(qword v, qword len) { qword r; __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q" : "=j"(r) : "j"(v), "j"(len)); return r; }
static inline qword QwAddScaled(qword base, qword v, VU_FLOAT g) { qword r; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(v), "j"(g.qw)); return r; }
static inline qword QwScaleX(qword v, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(g.qw)); return r; }
static inline float GXOfQw(qword qw) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(qw)); return x; }
static inline float Length(qword v) { return GXOfQw(QwSqrt(QwDot(v, v))); }
static inline int Alive(NODE *p) { return (int)p->flags.hi & 1; }
static inline float Evaluate(POLY *p, float t) { return p->a + t * (p->b + t * p->c); }
static inline float Limit(float f, LM *p) { float low = p->low, high = p->high, r; if (f < low) r = low; else if (high < f) r = high; else r = f; return r; }
static inline qword QwNormalizeSafe(qword v, qword fallback, float eps)
{
    qword r = QwSqrt(QwDot(v, v));
    if (GXOfQw(r) < eps) r = fallback; else r = QwDivide(v, r);
    return r;
}
static inline float GXOfVf(qword qw) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(qw), "j"(qw)); return x; }
static inline qword NormalizeInPlace(U *pv, const qword *pfallback, void *own)
{
    float eps = 0.0001f;
    qword g = pv->q;
    qword v;
    qword d, one;
    __asm__("" : "=j"(v) : "0"(g), "r"(own));
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v), "j"(v), "r"(g));
    qword len = QwSqrt(d);
    if (GXOfVf(len) < eps) pv->q = *pfallback;
    else { qword r; __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q" : "=j"(r) : "j"(v), "j"(len)); pv->q = r; }
    return len;
}

static inline qword RSub(const qword&a,const qword&b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword RDot(const qword&a,const qword&b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));return r;}
static inline qword RAddScaled(const qword&base,const qword&v,const VU_FLOAT&g){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(v),"j"(g.qw));return r;}
static inline float REvaluate(const POLY&p,const float&t){return p.a+t*(p.b+t*p.c);}
static inline float RLimit(float f,const LM&p){float low=p.low,high=p.high,r;if(f<low)r=low;else if(high<f)r=high;else r=f;return r;}
static inline float RGXOfQw(const qword&qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw));return x;}
static inline float RGXOfVf(const qword&qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw),"j"(qw));return x;}
static inline VU_FLOAT RVuFloat(const float&g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(g));return v;}

extern "C" void func_0019CF60(P *p)
{
    U nearest, direction, unit;
    func_0023C660(p);
    switch (p->state) {
    case 2:
    case 4:
        if (func_0019BAA0(p))
            func_0019DC10(p, 0);
        break;
    case 5:
        if (func_0019BAA0(p)) {
            VTE *e = &p->node.vt[9];
            ((void (*)(void *))e->fn)((char *)p + e->delta);
            return;
        }
        break;
    }
    if (!p->active && !p->x1CC) {
        NODE *t = func_0019BC68(p);
        if (t != p->target) {
            func_0019DC10(p, 0);
            p->target = t;
        }
    }
    switch (p->state) {
    case 0:
    case 4:
    case 5:
        break;
    default:
        if (!p->target || !Alive(p->target))
            func_0019DC10(p, 0);
        break;
    }
    if (!p->active && p->target && Alive(p->target)) {
        RULE *rule = &p->rules[p->state];
        qword target = Pos(p->target);
        qword delta = QwSub(target, Pos(&p->node));
        float distance = Length(delta);
        float heading = func_0011E3B8(func_001205C8(func_001C94E8(0, p, delta)));
        int accept;
        if (!rule->distanceEnabled) accept = rule->angleEnabled;
        else accept = func_0011EE30(&rule->stayDistance, distance);
        if (accept) {
            if (!rule->angleEnabled) goto dispatch;
            if (func_0011EE30(&rule->stayAngle, heading)) goto dispatch;
        }
        {
            int state;
            for (state = 5; state > 0; state--) {
                rule = &p->rules[state];
                if (!rule->distanceEnabled) accept = rule->angleEnabled;
                else accept = func_0011EE30(&rule->enterDistance, distance);
                if (!accept) continue;
                if (!rule->angleEnabled) break;
                if (func_0011EE30(&rule->enterAngle, heading)) break;
            }
            func_0019DC10(p, state);
        }
    }
dispatch:
    switch (p->state) {
    case 0:
    case 4:
    case 5:
        break;
    case 1:
    case 2: {
        if (p->cooldown) break;
        FRAME *frame = p->node.frame;
        qword target = Pos(p->target);
        qword self = Pos(&p->node);
        float heading = func_0011E3B8(func_001205C8(func_0028E990(0, frame->space, QwSub(target, self))));
        p->heading = Limit(Evaluate(&p->simpleAngle, heading), &p->simpleClamp);
        break;
    }
    case 3: {
        qword target = Pos(p->target);
        qword self = Pos(&p->node);
        VTE *vte = &p->node.vt[38];
        ((void (*)(void *))vte->fn)((char *)p + vte->delta);
        int refresh = 0;
        if (100.0f < Length(QwSub(target, p->previousTarget))) refresh = 1;
        else if (100.0f < Length(QwSub(self, p->previousSelf))) refresh = 1;
        else if (5.0f < g_clock.t - p->stamp) refresh = 1;
        if (refresh) {
            func_001EC688(p->binding, self, target, p->curve);
            p->progress = 0.0f;
            p->previousTarget = target;
            p->previousSelf = self;
            p->stamp = g_clock.t;
        }
        func_0022EEA0(p->curve, self, 0, &nearest.q, p->progress, &direction.q, 0, &p->progress);
        {
            float eps = 0.0001f;
            qword d = QwSub(QwAddScaled(nearest.q, direction.q, VuFloat(200.0f)), self);
            unit.q = QwNormalizeSafe(d, D_00317560, eps);
        }
        float remaining = func_0022DFD8(p->curve) - p->progress;
        float turn = func_001205C8(func_001C94E8(0, p, unit.q));
        float response = func_00171C98(D_0036BD20);
        float speed = Limit(Evaluate(&p->remaining, remaining), &D_00341FF0) * Limit(Evaluate(&p->angle, turn), &D_00341FF0) * Limit(Evaluate(&D_00321FE0, response), &D_00341FF0) * p->scale;
        qword force = QwScaleX(unit.q, VuFloat(speed));
        NODE *objects[128];
        int n = func_0017E208(D_00475480, 0x105, 0x4B, 0, 128, objects);
        for (int i = 0; i < n; i++) {
            NODE *object = objects[i];
            if (object != &p->node && object->group != p->node.group) {
                U scalar;
                scalar.q = RSub(self, Pos(object));
                scalar.f[2] = 0.0f;
                qword len = NormalizeInPlace(&scalar, &D_00317530, p);
                float weight = RLimit(REvaluate(D_00321FF0, RGXOfVf(len)), D_00322000);
                weight *= RLimit(REvaluate(D_00322010, RGXOfQw(RDot(scalar.q, unit.q))), D_00341FF0);
                force = RAddScaled(force, scalar.q, RVuFloat(weight));
            }
        }
        p->output = func_001205F0(force, speed);
        p->heading = func_001205C8(unit.q);
        break;
    }
    }
}
