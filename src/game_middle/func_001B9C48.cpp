// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Shares one .rodata section with func_001BADF8 below (the jump tables of func_001B9C48 are followed by the FLT_MAX literal that func_001BADF8 loads),
// so both functions live in this file; func_001BADF8 is the former src/game_middle/func_001BADF8.cpp with D_00323238 replaced by its literal.
// func_001B9C48: per-frame movement / jump-target update of the hero's air context (Sly 2 func_00197F98 relative).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { qword r[3]; };
struct M4 { U r[4]; };
struct VTE { short delta, pad; void *fn; };
struct VU_FLOAT { qword q; };
extern "C" void func_002BE4E0(void *, int);
class Scope { public: ~Scope() { func_002BE4E0(this, 2); } };

static inline VU_FLOAT VuFloatHomed(float g) { union { volatile qword home; } u; qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(g)); u.home = q; VU_FLOAT v; v.q = q; return v; }
static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwMul(qword a, qword b) { qword r; __asm__("vmul.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwAddScaled(qword a, qword b, VU_FLOAT g) { qword r; __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(g.q)); return r; }
static inline qword QwScale2(qword a, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(g.q), "j"(a), "j"(g.q)); return r; }
static inline float GFromVf(qword v) { float g; __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(v)); return g; }
static inline float GFromQw(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float GLengthSqXY(qword v) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(v)); return GFromVf(r); }
static inline float GLengthSqXYQ(qword v) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(v)); return GFromQw(r); }
static inline qword QwSqrt(qword v) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(v)); return r; }
static inline float GLengthXY(qword v) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(v)); return GFromVf(QwSqrt(r)); }
static inline qword QwDot(qword a, qword b) { qword r, one; __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b)); return r; }
static inline float GLengthQ(qword v) { return GFromQw(QwSqrt(QwDot(v, v))); }
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Transform(const M4 &m, qword v)
{
    qword q;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(q) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(v));
    return q;
}
static inline M3 MulM3(const M3 &a, const M3 &b) return r
{
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[0]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[1]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[2]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
}
static inline qword QwScaleQ(qword a, qword g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(g)); return r; }
// QwCombine with the 0.5f scalar passed as an extra (unused) operand: it keeps the float constant live as an operand of the combine,
// which fixes the scheduling/spill order of the constant load (the compiler then needs only two spill registers).
static inline qword QwCombineF(qword a, qword b, VU_FLOAT g0, qword c, VU_FLOAT g1, float f) { qword r; __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x" : "=j"(r) : "j"(a), "j"(b), "j"(g0.q), "j"(c), "j"(g1.q), "f"(f)); return r; }
static inline qword QwDivQ(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
static inline float GNormalize(U &v, const qword &vDefault)
{
    qword l = QwSqrt(QwDot(v.q, v.q));
    if (GFromVf(l) < 0.0001f)
        v.q = vDefault;
    else
        v.q = QwDivQ(v.q, l);
    return GFromQw(l);
}
struct LM { float low, high; };
static inline float GLerp(const LM &lm, float u) { return (1.0f - u) * lm.low + u * lm.high; }
static inline float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (hi < g) return hi; return g; }

struct SMP { float a, b, c; };
struct BASE_24 { char data[0x24]; };
struct SAMPLER { BASE_24 data; virtual void f1(); virtual void f2(); virtual void Sample(struct ACTOR *, U *, float *, float); };
struct BASE_D0 { char data[0xD0]; };
struct BASE_130 { char data[0x130]; };
struct BASE_180 { char data[0x180]; };
struct PATH : BASE_D0, SAMPLER {};
struct SPLINE : BASE_180, SAMPLER {};
struct FIELD : BASE_130, SAMPLER {};

static inline qword RotateTranspose(const M3 &m, qword v)
{
    qword q, one, a, b, c;
    __asm__("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "=j"(q), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m.r[1]), "j"(m.r[2]), "j"(v), "0"(m.r[0]));
    return q;
}

struct SPACE;
struct CLIP;
struct PCTL { char pad0[8]; float amount; };
struct PHYSICS { char pad0[0x88]; float gravity; };
struct BODY { char pad0[0x30]; U position; char pad40[0x60]; SPACE *frame; char padA4[4]; float deadline; char padAC[4]; U velocity; U goal; U velocityGoal; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x48 - 0x10]; BODY *body; char pad4C[0xD8 - 0x4C]; PHYSICS *physics;
    char padDC[0x134 - 0xDC]; PCTL *pctl; char pad138[0x148 - 0x138]; void *focusRef; char pad14C[0x1A0 - 0x14C];
    U velocity; char pad1B0[0x1BC - 0x1B0]; float heading; M3 local; char pad1F0[0x260 - 0x1F0]; U offset;
    char pad270[0x370 - 0x270]; U facing; char pad380[0x940 - 0x380]; char sub[0x10]; char pad950[0x110C - 0x950]; float stick;
};
struct OBJECT { char pad0[0xC]; VTE *vt; char pad10[0x138 - 0x10]; float height; char pad13C[0x170 - 0x13C]; OBJECT *next; char pad174[4]; int state; };
struct DATA { char pad0[4]; float amount; };
struct FOCUS { char pad0[0x110]; DATA *data; };
struct TRACK { int id; float weight; float pad; };
struct CONTEXT {
    ACTOR *actor; char pad4[4]; int variant; void *source; float parameter; float value; char pad18[4]; int mode; float time; int jump;
    int stage; char pad2C[8]; float scale; float height; int combo; float tRelease; float tPress; float tRelease2; char pad4C[4];
    U desired; float lastHeading; float blend; float speedLimit; char pad6C[0x118 - 0x6C]; OBJECT *velocitySource; char pad11C[4];
    qword velocityScale; char pad130[4]; void *focus; void *other; int focused; char pad140[4]; float scriptedGain; char pad148[4]; TRACK tracks[4]; char pad17C[4];
    void *multi; FOCUS *scriptFocus; float blend0, blend1;
};
struct CLOCK { float t, dt; };

extern "C" {
extern CLOCK g_clock;
extern OBJECT *D_00479B08;
extern ACTOR *D_0036B250;
extern ACTOR *D_00370AC0;
extern qword D_00317530, D_00317550, D_00317560, D_003457B0;
extern float D_003457A0;
extern float D_003233B8[];
extern float D_00323138[];
extern LM D_00323110, D_00323118, D_00323130, D_003233D0;
extern SMP D_00323120;
void func_001BB228(CONTEXT *, qword, void *, qword, qword, float *, float *, qword *, qword *);
void func_00120A00(qword, qword, qword, qword *, float *, float *);
qword func_0028E910(int, SPACE *, qword);
qword func_0028E990(int, SPACE *, qword);
void func_001B77F8(CONTEXT *, int, void *);
void func_0028F680(SPACE *, int, M4 *, float, M4 *);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, qword *);
float func_002A3EE8(float, float);
float func_0011E3B8(float);
void func_0011EB28(float, float *, float *);
float func_0011E598(float, float, float, SMP *, float *);
void func_00148938(void *);
void func_0022E148(void *, float, qword *, qword *);
void func_00208378(void *);
void func_0024E8E8(ACTOR *, qword);
M3 func_0011C8C0(qword, float);
M3 func_0011CDC8(qword, qword);
float func_001205C8(qword);
void func_0024E878(ACTOR *, float);
float func_002A3408(float);
qword func_0011FD70(float, float, float);
float func_0011FE60(qword, qword, qword *, qword *);
qword func_001205F0(qword, float);
void func_001F47C8(ACTOR *, void *);
}

static inline qword MatrixPos(void *p) { VTE &v = ((OBJECT *)p)->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.delta)->r[3].q; }
static inline qword GetVelocity(void *p) { VTE &v = ((OBJECT *)p)->vt[38]; return ((qword (*)(void *))v.fn)((char *)p + v.delta); }
static inline SPACE *GetFrame(void *p) { VTE &v = ((OBJECT *)p)->vt[37]; return ((SPACE *(*)(void *, void *))v.fn)((char *)p + v.delta, 0); }

extern "C" void func_001B9C48(CONTEXT *p)
{
    PCTL *input = p->actor->pctl;
    float stick = p->actor->stick;
    switch (p->combo) {
    case 0:
        if (0.9f < input->amount) {
            p->combo = 1;
            p->tPress = g_clock.t;
        } else if (0.07f < g_clock.t - p->tRelease)
            p->jump = 1;
        break;
    case 1:
        if (input->amount < 0.9f) {
            p->combo = 2;
            p->tRelease2 = g_clock.t;
            if (g_clock.t - p->tPress < 0.3f)
                p->jump = 1;
        }
        break;
    case 3:
        if (0.2f < input->amount)
            p->jump = 1;
        break;
    }

    U pos;
    pos.q = MatrixPos(p->actor);
    U vel;
    vel.q = GetVelocity(p->actor);
    float t, score;

    switch (p->mode) {
    case 0: case 2: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17:
    case 19: case 20: case 21: case 22:
        break;
    default: {
        U point, posBest, velHit, velBest;
        OBJECT *srcBest = 0;
        float scoreBest = 1500.0f;
        float tBest;
        {
            Scope e;
            for (OBJECT *src = D_00479B08; src; src = src->next) {
                if (src->state != 0)
                    continue;
                qword posSrc = MatrixPos(src);
                if (360000.0f < GLengthSqXY(QwSub(posSrc, pos.q)))
                    continue;
                if (GetZ(posSrc) + src->height < pos.f[2])
                    continue;
                func_001BB228(p, vel.q, src, QwSub(posSrc, p->actor->offset.q), D_00317560, &t, &score, &point.q, &velHit.q);
                if (scoreBest < score)
                    continue;
                float alpha, dist;
                U delta;
                delta.q = QwSub(pos.q, posSrc);
                qword v = vel.q;
                U rel;
                rel.q = QwSub(v, GetVelocity(src));
                U end;
                end.q = QwAddScaled(delta.q, rel.q, VuFloat(GMin(0.25f, t)));

                delta.f[2] = end.f[2] = 0.0f;
                func_00120A00(D_00317560, delta.q, end.q, 0, &alpha, &dist);
                if (!((dist <= 100.0f && alpha != 0.0f) || (dist <= 25.0f && vel.f[2] <= 0.0f)))
                    continue;

                srcBest = src;
                posBest = point;
                velBest = velHit;
                tBest = t;
                scoreBest = score;
            }
        }
        if (srcBest) {
            BODY *body = p->actor->body;
            body->deadline = g_clock.t + tBest;
            body->goal.q = func_0028E910(0, body->frame, posBest.q);
            SPACE *frame = body->frame;
            U v;
            ACTOR *actor = p->actor;
            v.q = Make(velBest.f[0], velBest.f[1], vel.f[2] + tBest * actor->physics->gravity);
            body->velocityGoal.q = func_0028E990(0, frame, v.q);
            func_001B77F8(p, 8, srcBest);
        }
        break;
    }
    }

    U point;
    float headingSample = p->actor->heading;
    SAMPLER *psampler;

    switch (p->mode) {
    case 8:
        point.q = QwSub(MatrixPos(p->source), p->actor->offset.q);
    predict: {
        BODY *body = p->actor->body;
        float dt = body->deadline - g_clock.t;
        SPACE *frame = GetFrame(p->source);
        M4 forecast, derivative;
        func_0028F680(frame, 0, &forecast, dt, &derivative);
        qword local = func_0028E910(0, frame, point.q);
        body->goal.q = func_0028E910(0, body->frame, Transform(forecast, local));
        if (p->mode != 11) {
            U v;
            v.q = Transform(derivative, local);
            v.f[2] = vel.f[2] + dt * p->actor->physics->gravity;
            body->velocityGoal.q = func_0028E990(0, body->frame, v.q);
        }
        break;
    }
    case 11: case 12:
        psampler = (SPLINE *)p->source;
    sample:
        psampler->Sample(p->actor, &point, &headingSample, p->value);
        goto predict;
    case 10:
        psampler = (PATH *)p->source;
        goto sample;
    case 13:
        psampler = (PATH *)p->source;
        goto sample;
    case 14:
        psampler = (PATH *)p->source;
        goto sample;
    case 19:
        point.q = MatrixPos(p->source);
        goto predict;
    case 17:
        psampler = (FIELD *)p->source;
        goto sample;
    }

    switch (p->mode) {
    case 8: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 19: {
        BODY *body = p->actor->body;
        float dt = body->deadline - g_clock.t + g_clock.dt;
        U accel0, accel1;
        func_00118558(dt, 0.0f, 1.0f, body->position.q, body->velocity.q, body->goal.q, body->velocityGoal.q, 0, 0, &accel0.q);
        func_00118558(dt, dt, 1.0f, body->position.q, body->velocity.q, body->goal.q, body->velocityGoal.q, 0, 0, &accel1.q);
dt *= 0.5f;
        if (10000.0f < (GLengthQ(accel0.q) + GLengthQ(accel1.q)) * dt)
            func_001B77F8(p, 6, 0);
        break;
    }
    }

    float offset = D_003233B8[p->variant];
    float heading = p->actor->heading;
    switch (p->mode) {
    case 0:
        if (0.2f < input->amount)
            heading = stick + offset;
        break;
    case 12: case 13: case 14:
        heading = headingSample;
        break;
    case 21: {
        M4 *m = ((M4 *(*)(void *))p->actor->vt[36].fn)((char *)p->actor + p->actor->vt[36].delta);
        float headingOld = func_002A3EE8(m->r[0].f[1], m->r[0].f[0]);
        float s, c;
        func_0011EB28(func_0011E3B8(stick - headingOld), &s, &c);
        float lateral = s * input->amount;
        float forward = c * input->amount;
        float mix = (forward + 1.0f) * 0.5f;
        if (p->scriptFocus) {
            DATA *data = p->scriptFocus->data;
            data->amount = func_0011E598(data->amount, GLerp(D_003233D0, mix), g_clock.dt, &D_00323120, 0);
        }
        float turn = GLerp(D_00323130, mix) * lateral * g_clock.dt;
        p->blend0 = GLerp(D_00323110, mix);
        p->blend1 = GLerp(D_00323118, mix);

        p->scriptedGain = 1.0f - input->amount;
        heading = headingOld + turn;
        if (input->amount != 0.0f) {
            float scale = input->amount / (__builtin_fabsf(lateral) + __builtin_fabsf(forward));
            if (lateral < 0.0f) {
                p->tracks[0].weight = 0.0f;
                p->tracks[1].weight = -lateral * scale;
            } else {
                p->tracks[1].weight = 0.0f;
                p->tracks[0].weight = lateral * scale;
            }
            if (0.0f < forward) {
                p->tracks[3].weight = 0.0f;
                p->tracks[2].weight = forward * scale;
            } else {
                p->tracks[2].weight = 0.0f;
                p->tracks[3].weight = -forward * scale;
            }
        } else {
            p->tracks[0].weight = 0.0f;
            p->tracks[1].weight = 0.0f;
            p->tracks[2].weight = 0.0f;
            p->tracks[3].weight = 0.0f;
        }
        func_00148938(p->multi);
        break;
    }
    case 15: case 16: {
        U target;
        if (p->mode == 16)
            func_0022E148(p->source, p->parameter, &target.q, 0);
        else
            target.q = MatrixPos(p->source);
        if (p->actor != D_00370AC0)
            func_00208378(p->actor->sub);
        func_0024E8E8(p->actor, QwSub(target.q, pos.q));
        heading = p->actor->heading;
        break;
    }
    case 18: case 20:
        break;
    default: {
        qword velocity = vel.q;
        qword base;
        if (p->velocitySource) {
            qword k = p->velocityScale;
            base = QwMul(k, GetVelocity(p->velocitySource));
        } else
            base = D_00317560;
        qword rel = QwSub(velocity, base);
        if (p->actor == D_0036B250 && (unsigned)(p->mode - 2) < 4) {
            M3 rot;
            float hv;
            VU_FLOAT half;
            {
                M3 ret = func_0011C8C0(D_00317550, p->actor->heading);
                hv = 0.5f;
                half = VuFloatHomed(hv);
                // copy of the returned basis into rot, row by row
                register qword r0 asm("$3") = ret.r[0];  // the one register pin: first row temp in $v1 like the target (the rows then get v1/a1/v0)
                rot.r[0] = r0;
                qword r1 = ret.r[1];
                rot.r[1] = r1;
                qword r2 = ret.r[2];
                rot.r[2] = r2;
            }
            qword up = D_00317550;
            qword a = rel;
            qword b = p->actor->facing.q;
            a = QwSub(a, QwScaleQ(up, QwDot(a, up)));
            b = QwSub(b, QwScaleQ(up, QwDot(b, up)));
            M3 turned;
            turned = func_0011CDC8(up, QwCombineF(D_003457B0, a, half, b, half, hv));
            ACTOR *actor = p->actor;
            actor->local = MulM3(turned, rot);
            goto speed;
        } else if (200.0f < GLengthXY(rel)) {
            heading = func_001205C8(rel) + offset;
        }
        break;
    }
    }
    func_0024E878(p->actor, heading);
speed:

    switch (p->mode) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 9: {
        float speed;
        switch (p->mode) {
        case 2: case 3: case 4: case 5:
            speed = D_00323138[p->stage - 1];
            break;
        case 7:
            if (0.2f < input->amount) {
                p->blend = GClamp(func_002A3408(stick - p->lastHeading), 0.0f, p->blend);
            }
            if (D_003457A0 < p->speedLimit)
                speed = (1.0f - p->blend) * D_003457A0 + p->blend * p->speedLimit;
            else
                speed = D_003457A0;
            break;
        default:
            speed = D_003457A0;
            break;
        }
        speed *= p->scale;
        U desired;
        desired.q = func_0011FD70(stick, input->amount * speed, 0.0f);
        ACTOR *actor = p->actor;
        actor->velocity.q = QwScale2(RotateTranspose(actor->local, desired.q), VuFloat(-1.0f));
        if ((p->mode != 0 || p->combo == 3) && !p->jump) {
            U dir;
            dir.q = GetVelocity(p->actor);
            dir.f[2] = 0.0f;
            float g = GNormalize(dir, D_00317530);

            U perp;
            float proj = func_0011FE60(desired.q, dir.q, 0, &perp.q);
            if (proj < g && g * -0.25f < proj) {
                desired.q = QwAddScaled(perp.q, dir.q, VuFloat(g));
                desired.q = func_001205F0(desired.q, speed);
            }
        }
        p->desired = desired;
        break;
    }
    }
    if (pos.f[2] > p->height)
        p->height = pos.f[2];

    if (p->focused && p->focus && p->other && p->actor->focusRef == p->focus && vel.f[2] < 200.0f)
        func_001F47C8(p->actor, p->other);
}


// Support test for an actor standing on its contacts: after the clock/stamp throttle, builds the Gram matrix of the
// (owner-flipped) contact normals, solves for weights against "down" (func_0011BA98) and reports whether the
// weighted normals cancel down well enough (z of the residual above -0.1).
#include "../P2/packed_matrix_intrinsics.h"
#include "../P2/vector_intrinsics.h"

struct ContactActor;
struct Contact {
    char prefix[8]; ContactActor *owner;
    char gap0C[0x80 - 0xC]; qword normal;
    char gap90[0xAC - 0x90]; Contact *next;
};
struct ContactGroup { Contact *first; ContactGroup *next; };
struct ContactContainer { char prefix[0x64]; ContactGroup *groups; };
struct ContactActor { char prefix[0xDC]; ContactContainer *collision; };
struct ContactClock { float time, delta; };
struct ContactRequest { int bytes, alignment; };
union ContactWorkspace { ContactRequest request; qword scalar; };
union ContactVector { qword packed; float components[4]; };
union ContactFloatWord { unsigned int bits; float value; };
extern "C" {
extern ContactClock D_0036BB98;
extern qword D_00317550;
int func_001BADC0(void *actor);
void *func_001D2770(void *scope);
void func_001D2798(void *scope, int flags);
void *func_001D25B0(ContactRequest *request);
void func_0011BA98(int count, float limit, float *matrix, float *rhs, float *weights);
}
struct ContactAllocationScope {
    ContactAllocationScope() { func_001D2770(this); }
    ~ContactAllocationScope() { func_001D2798(this, 2); }
};

static inline qword ContactScalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline float ContactZ(qword vector)
{
    qword bits;
    float result;
    asm("qmfc2.ni %1,%2\n\tpextuw %1,$zero,%1\n\tmtc1 %1,%0"
        : "=f"(result), "=&r"(bits) : "j"(vector));
    return result;
}
static inline void ContactNormalInto(qword &normal, ContactActor *actor, Contact *contact,
                                     ContactWorkspace *workspace)
{
    normal = contact->normal;
    if (contact->owner != actor) {
        workspace->scalar = ContactScalar(-1.0f);
        asm("vmulx.xyzw %0,%0,%1x" : "+j"(normal) : "j"(workspace->scalar));
    }
}
static inline void ContactStoreDot(float *out, qword a, qword b)
{
    qword one, d;
    asm("vmul.xyz %2,%3,%4
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%2,%2y
	vmaddz.x %2,%1,%2z
	qmfc2.ni %0,%2" : "=&rV"(*out), "=j"(one), "=j"(d) : "j"(a), "j"(b));
}
static inline qword ContactAddScaled(qword sum, qword normal, float weight,
                                     ContactWorkspace *workspace)
{
    workspace->scalar = ContactScalar(weight);
    qword result;
    asm("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
        : "=j"(result) : "j"(sum), "j"(normal), "j"(workspace->scalar));
    return result;
}

extern "C" int func_001BADF8(ContactActor *actor, float previous, float *stamp)
{
    float now = D_0036BB98.time;
    if (now - previous < 1.0f)
        return 0;
    if (stamp) {
        if (now - *stamp < 1.0f)
            return 0;
        *stamp = now;
    }
    if (func_001BADC0(actor))
        return 0;
    int count = 0;
    ContactGroup *group;
    Contact *contact;
    for (group = actor->collision->groups; group; group = group->next)
        for (contact = group->first; contact; contact = contact->next)
            ++count;
    if (!count)
        return 0;

    ContactAllocationScope scope;
    ContactWorkspace workspace;
    qword down;
    int rowBytes = count * 4;
    workspace.scalar = ContactScalar(-1.0f);
    down = ScalePackedMatrixRow(D_00317550, workspace.scalar);
    ContactRequest *request = &workspace.request;
    request->bytes = count * count * 4;
    request->alignment = 16;
    float *matrix = (float *)func_001D25B0(request);
    request->bytes = rowBytes;
    request->alignment = 16;
    float *rhs = (float *)func_001D25B0(request);
    request->bytes = rowBytes;
    request->alignment = 16;
    float *weights = (float *)func_001D25B0(request);

    ContactFloatWord *cursor = (ContactFloatWord *)matrix;
    for (group = actor->collision->groups; group; group = group->next) {
        for (contact = group->first; contact; contact = contact->next) {
            qword normal;
            ContactNormalInto(normal, actor, contact, &workspace);
            for (ContactGroup *other = actor->collision->groups; other; other = other->next) {
                Contact *second = other->first;
                if (!second)
                    continue;
                do {
                    { qword other; ContactNormalInto(other, actor, second, &workspace); ContactStoreDot((float *)cursor, normal, other); cursor++; }
                } while ((second = second->next) != 0);
            }
        }
    }
    cursor = (ContactFloatWord *)rhs;
    for (group = actor->collision->groups; group; group = group->next) {
        contact = group->first;
        if (!contact)
            continue;
        do {
            { qword n; ContactNormalInto(n, actor, contact, &workspace); ContactStoreDot((float *)cursor, n, down); cursor++; }
        } while ((contact = contact->next) != 0);
    }
    func_0011BA98(count, 3.4028235e38f /* FLT_MAX: the float literal shares the .rodata after the jump tables above */, matrix, rhs, weights);
    qword sum = down;
    cursor = (ContactFloatWord *)weights;
    for (group = actor->collision->groups; group; group = group->next) {
        contact = group->first;
        if (!contact)
            continue;
        do {
            qword normal;
            ContactNormalInto(normal, actor, contact, &workspace);
            float weight = (cursor++)->value;
            contact = contact->next;
            sum = ContactAddScaled(sum, normal, weight, &workspace);
        } while (contact);
    }
    int supported = 1;
    if (-0.1f < PackedVectorZ(sum)) {
    } else {
        supported = 0;
    }
    return supported;
}
