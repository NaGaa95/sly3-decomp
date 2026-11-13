// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Mode change of a hero's action context (Sly 3 version of Sly 2 func_00195FB8): leaves the old mode, picks the entry state and the
// animation clip of the new mode and starts it. Mode 22 ("jump to the goal") solves the launch velocity of a ballistic jump and starts the motion event.
// Match keys: SLY3_AS gnu-2.9 (the four jump tables are followed by foreign .rodata, so the section must not be padded; VU asm then spells ACC/Q
// without `$` and vadda with vf0 first). Mode 22 uses plain locals: bodyPosition, goal, delta, accel, velocity and endVelocity are spilled by reload
// (slots 0x50..0xA0, and the unforwarded `lq a0/a1` argument reloads come from that); goal goes straight into the vsub asm (a "j" operand) so it is not
// local-allocated into s0. The splat helper arguments are by-value VF2 structs: their stack temps give the dead `sqc2 vfN,..($sp)` stores
// (mode 18 `negative` and mode 22 full/half/full) and the extra refs make the caller-save of the full splat profitable. `HANDLE *h = &p->fx` is
// defined before the `if (!p->fx.obj)` branch so the address lives in s3 (a block-local pseudo would be allocated s1).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U row[3]; };
struct TWO_ROWS { U row[2]; };
struct VTE { short d; short pad; void *fn; };
struct DATA { char pad0[4]; float amount; };
struct SOURCE { char pad0[0x110]; DATA *data; char pad114[0x178 - 0x114]; int state; };
struct CLIP { char pad0[0x64]; float duration; };
struct ANIMATION { char pad0[0x14]; CLIP *clip; };
struct SPACE;
struct BODY { char pad0[0x70]; U position; char pad80[0x20]; SPACE *frame; };
struct MOTION { char pad0[0x80]; U acceleration; };
struct EFFECT;
struct HANDLE { void *obj; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x38]; BODY *body; char pad4C[0xD8 - 0x4C]; MOTION *motion; char padDC[0x1A0 - 0xDC]; U velocity;
    char pad1B0[0x1BC - 0x1B0]; float heading; char pad1C0[0x508 - 0x1C0]; int category; char pad50C[0x940 - 0x50C]; char secondary[0x30];
    CLIP *secondaryClip; char pad974[0x1108 - 0x974]; void *x1108; char pad110C[0x1120 - 0x110C]; U offset; char pad1130[0x113C - 0x1130];
    ANIMATION *animation; char pad1140[0x1654 - 0x1140]; CLIP *clip1654; CLIP *clip1658;
};
struct LINK { SPACE *space; void *target; };
struct QUERY { ACTOR *object; };
struct CTX {
    ACTOR *actor; int state; int variant; SOURCE *source; char pad10[0xC]; int mode; float time; char pad24[4]; int flags28; int flags2C;
    char pad30[0x6C - 0x30]; int field6C; char pad70[0x80 - 0x70]; LINK *link; char pad84[0x90 - 0x84]; U relative; U direction; U offset;
    CLIP *base[5]; CLIP *alternate[5]; CLIP *alt2[3]; CLIP *special0F4; char padF8[4]; CLIP *special0FC; CLIP *special100; CLIP *special104;
    CLIP *special108; CLIP *special10C; CLIP *special110; CLIP *special114; char pad118[0x130 - 0x118]; float oldScale; char pad134[8];
    int focused; CLIP *special140; float scriptedGain; char pad148[0x150 - 0x148]; int control150; char pad154[8]; int control15C; char pad160[8];
    int control168; char pad16C[8]; int control174; char pad178[8]; CLIP *multi; SOURCE *scriptFocus; char pad188[8]; int copy190;
    void *object194; void *object198; void *object19C; HANDLE fx; char pad1A4[0x1B0 - 0x1A4]; QUERY query; char pad1B4[0x1D0 - 0x1B4]; void *event;
};
struct SCENE;
struct CLOCK { float time, dt; };
struct WORK { U temp; M3 basis; };

extern "C" {
extern SCENE D_00475480;
extern CLOCK D_0036BB98;
extern ACTOR *D_0036B250;
extern U D_00317560;
extern U D_00317550, D_00317540;
extern float D_003233B8[];
extern float D_003233D0[2];
void func_0024F3B8(ACTOR *, void *, int);
void func_0013CD10(SCENE *, void *);
void func_001A1A28(SOURCE *, int);
void func_0028F068(ACTOR *, BODY *, int);
int func_0013B500(ACTOR *, int);
void func_00208B20(void *, int);
void func_00209470(void *, SOURCE *);
void func_00239CE8(EFFECT *, int);
void func_001F47C8(ACTOR *, void *);
void func_001309D8(void *);
void func_0023FC90(ACTOR *, int);
qword func_001BB4E8(CTX *, int);
void func_0024F1E8(ACTOR *, float);
void func_0024E878(ACTOR *, float);
CLIP *func_001733C8(void *);
CLIP *func_001733B8(void *);
void func_00148938(CLIP *);
qword func_001C03A0(ACTOR *, QUERY *, float);
float func_001B83F0(qword, qword, float, float, float, float);
qword func_0028E910(SPACE *, SPACE *, qword);
qword func_0028E990(SPACE *, SPACE *, qword);
void *func_00130348(ACTOR *, BODY *, int, float, qword, qword);
void func_0024E8E8(ACTOR *, qword);
void func_0011FEA8(qword, qword, qword, TWO_ROWS *);
void func_0023AC58(void *);
void func_00137588(CLIP *, ACTOR *, float, float, int, ANIMATION **);
void func_0013ABC8(void *, int);
void *func_002459F8(int);
void func_00244F08(void *, void *);
void func_002BBCD8(HANDLE *, void *);
void func_00245100(void *, float, float);
void func_00244E08(void *, float);
void func_00244ED0(void *, float);
void func_00244CA8(void *, float);
}

/* A splat vector handed to a helper BY VALUE (see the header comment). */
struct VF2 { qword q; };
static inline VF2 VuFloat(float g) { VF2 v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
static inline void Notify(void *p, int slot) { VTE &v = ((ACTOR *)p)->vt[slot]; ((void (*)(void *))v.fn)((char *)p + v.d); }
static inline void ClearXYZ(U *v) { v->i[2] = 0; v->i[1] = 0; v->i[0] = 0; }
static inline bool Less(int x, int limit) { return x < limit; }
static inline qword Position(ACTOR *p) { VTE &v = p->vt[36]; struct M4 { U r[4]; }; return ((M4 *(*)(void *))v.fn)((char *)p + v.d)->r[3].q; }
static inline qword ScaleX(qword a, VF2 s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
static inline qword Rot(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz ACC,%2,%1x
	vmadday.xyz ACC,%3,%1y
	vmaddz.xyz %0,%4,%1z" : "=j"(r) : "j"(v), "j"(m.row[0].q), "j"(m.row[1].q), "j"(m.row[2].q));
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }

static inline qword ScaleRecip(qword v, VF2 l) { qword r; __asm__("vdiv Q,$vf0w,%1x
	vwaitq
	vmulq.xyzw %0,%2,Q" : "=j"(r) : "j"(l.q), "j"(v)); return r; }
static inline qword AddScaled(qword base, qword v, VF2 s) { qword r; __asm__("vadda.xyzw ACC,$vf0,%1
	vmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(v), "j"(s.q)); return r; }

extern "C" void func_001B77F8(CTX *p, int newMode, SOURCE *source)
{
    if (newMode == p->mode)
        return;
    switch (p->mode) {
    case 18:
        func_0024F3B8(p->actor, p->link->target, 0);
        p->link = 0;
        break;
    case 9: {
        SOURCE *old = p->source;
        p->source = 0;
        func_0013CD10(&D_00475480, old);
        break;
    }
    case 8: {
        SOURCE *old = p->source;
        p->source = 0;
        if (p->actor->category != 1) {
            func_0013CD10(&D_00475480, old);
            if (old->state == 1)
                func_001A1A28(old, 0);
        }
        func_0028F068(p->actor, p->actor->body, 2);
        p->actor->velocity.q = D_00317560.q;
        break;
    }
    case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 19:
        func_0028F068(p->actor, p->actor->body, 2);
        p->actor->velocity.q = D_00317560.q;
        if (Less(p->mode, 17) && !Less(p->mode, 15)) {
            if (func_0013B500(p->actor, 0x34))
                func_00208B20((char *)p->actor + 0x18F0, -1);
            else
                func_00208B20(p->actor->secondary, -1);
        }
        break;
    case 20: case 21:
        if (Less(newMode, 22) && !Less(newMode, 20))
            break;
        if (*(EFFECT **)((char *)p->actor + 0x1D48))
            func_00239CE8(*(EFFECT **)((char *)p->actor + 0x1D48), 0x6C9);
        func_001F47C8(p->actor, 0);
        break;
    case 22:
        func_001309D8((char *)p + 0x1D0);
        func_0028F068(p->actor, p->actor->body, 2);
        func_0023FC90(p->actor, 0);
        break;
    case 4:
        if (p->object194) Notify(p->object194, 9);
        if (p->object198) Notify(p->object198, 9);
        if (p->object19C) Notify(p->object19C, 9);
        break;
    }
    ANIMATION *active = p->actor->animation;
    CLIP *clip = 0;
    p->mode = newMode;
    p->source = source;
    float blend = 0.0f;
    p->time = D_0036BB98.time;
    int flags = 1;
    float weight = 1.0f;
    switch (newMode) {
    case 18: {
        WORK w;
        flags = 9;
        Notify(p->actor, 102);
        func_0024F3B8(p->actor, p->link->target, 1);
        qword point = func_0028E910(p->link->space, 0, p->relative.q);
        qword direction = ScaleX(p->direction.q, VuFloat(-1.0f));
        w.temp.q = point;
        w.basis.row[0].q = direction;
        func_0011FEA8(direction, D_00317550.q, D_00317540.q, (TWO_ROWS *)&w.basis.row[1]);
        ACTOR *actor = p->actor;
        qword delta = Sub(w.temp.q, Rot(w.basis, p->offset.q));
        w.temp.q = delta;
        actor->offset.q = Sub(delta, Position(actor));
        ClearXYZ(&p->actor->velocity);
        p->flags28 = p->copy190;
        clip = p->special0FC;
        if (p->focused) {
            p->focused = 0;
            func_0024F1E8(p->actor, p->oldScale);
            func_001F47C8(p->actor, 0);
        }
        break;
    }
    case 0: case 1: case 6: case 7: case 9:
        switch (p->state) {
        case 13: clip = p->special100; break;
        case 15: clip = p->actor->clip1654; break;
        case 14: clip = p->actor->clip1658; break;
        case 16: clip = (CLIP *)func_001733C8(p->actor->x1108); break;
        case 17: clip = (CLIP *)func_001733B8(p->actor->x1108); break;
        case 18: clip = p->special108; break;
        }
        if (!clip) clip = p->special110;
        if (p->mode == 0) p->flags2C = clip != 0;
        if (!clip) clip = p->base[p->variant];
        if (!clip) clip = p->base[0];
        break;
    case 2: case 3: case 4: case 5:
        if (p->state == 13) clip = p->special104;
        if (!clip) clip = p->special114;
        if (!clip) clip = p->alt2[p->flags28 - 1];
        if (p->mode == 2) p->flags2C = clip != 0;
        if (!clip) clip = p->alternate[p->variant];
        if (!clip) clip = p->alternate[0];
        if (!clip) clip = p->base[0];
        if (p->mode == 4) {
            if (p->object194 && (p->flags28 == 1 || p->flags28 == 3)) Notify(p->object194, 8);
            if (p->object198 && (p->flags28 == 1 || p->flags28 == 3)) Notify(p->object198, 8);
            if (p->object19C && p->flags28 >= 2) Notify(p->object19C, 8);
        }
        break;
    case 8:
        func_0028F068(p->actor, p->actor->body, 0x12);
        func_0013CD10(&D_00475480, source);
        func_001A1A28(source, 1);
        ClearXYZ(&p->actor->velocity);
        clip = p->actor->animation->clip;
        break;
    case 12: case 13: case 14: case 15: case 16:
        func_0028F068(p->actor, p->actor->body, 0x12);
        ClearXYZ(&p->actor->velocity);
        p->variant = 0;
        p->flags28 = p->copy190;
        clip = p->base[0];
        if (Less(p->mode, 17) && !Less(p->mode, 15)) {
            if (func_0013B500(p->actor, 0x34)) {
                func_00209470((char *)p->actor + 0x18F0, p->source);
            } else {
                weight = 0.0f;
                func_00209470(p->actor->secondary, p->source);
                clip = p->actor->secondaryClip;
                blend = clip->duration * 0.5f;
            }
        }
        break;
    case 10: case 11: case 17: case 19: {
        func_0028F068(p->actor, p->actor->body, 0x12);
        ClearXYZ(&p->actor->velocity);
        p->flags28 = p->copy190;
        ACTOR *actor = p->actor;
        VTE &v = actor->vt[40];
        void *receiver = (char *)actor + v.d;
        qword velocity = func_001BB4E8(p, 4);
        ((void (*)(void *, qword))v.fn)(receiver, velocity);
        p->variant = 0;
        if (p->mode == 17) {
            clip = p->special10C;
            active = 0;
            if (clip) break;
        }
        clip = p->special0F4;
        active = 0;
        break;
    }
    case -1:
        if (p->focused) {
            p->focused = 0;
            func_0024F1E8(p->actor, p->oldScale);
            func_001F47C8(p->actor, 0);
        }
        p->field6C = 0;
        p->state = -1;
        break;
    case 20:
        func_0024E878(p->actor, p->actor->heading - D_003233B8[p->variant]);
        p->flags28 = p->copy190;
        clip = p->special140;
        func_001F47C8(p->actor, p->scriptFocus);
        p->scriptFocus->data->amount = D_003233D0[0] * 0.5f + D_003233D0[1] * 0.5f;
        if (*(EFFECT **)((char *)p->actor + 0x1D48))
            func_00239CE8(*(EFFECT **)((char *)p->actor + 0x1D48), 0x6C8);
        break;
    case 21:
        p->control150 = 0;
        p->control15C = 0;
        p->control168 = 0;
        p->control174 = 0;
        p->scriptedGain = 1.0f;
        func_00148938(p->multi);
        clip = p->multi;
        flags = 9;
        break;
    case 22: {
        float minimum = -1000.0f;
        qword bodyPosition = p->actor->body->position.q;
        float maximum = -1.0f;
        ACTOR *queryObject = p->query.object;
        if (queryObject && (func_0013B500(queryObject, 0x26) || func_0013B500(p->query.object, 0xA))) {
            minimum = 0.0f;
            maximum = 500.0f;
        }
        float scale = 0.7f;
        qword goal = func_001C03A0(p->actor, &p->query, scale);
        qword delta = Sub(goal, bodyPosition);
        qword accel = p->actor->motion->acceleration.q;
        float solved = func_001B83F0(delta, accel, 1000.0f, minimum, 1.0f, maximum);
        ACTOR *actor = p->actor;
        VTE &v = actor->vt[40];
        void *receiver = (char *)actor + v.d;
        scale = scale < solved ? solved : scale;
        float negativeHalf = -0.5f * scale;
        qword quotient = ScaleRecip(delta, VuFloat(scale));
        qword velocity = AddScaled(quotient, accel, VuFloat(negativeHalf));
        ((void (*)(void *, qword))v.fn)(receiver, velocity);
        float deadline = D_0036BB98.time + scale;
        qword endVelocity = AddScaled(velocity, accel, VuFloat(scale));
        qword localGoal = func_0028E910(0, p->actor->body->frame, goal);
        qword localEnd = func_0028E990(0, p->actor->body->frame, endVelocity);
        p->event = func_00130348(p->actor, p->actor->body, 5, deadline, localGoal, localEnd);
        func_0023FC90(p->actor, 1);
        ClearXYZ(&p->actor->velocity);
        func_0024E8E8(p->actor, delta);
        clip = p->base[0];
        break;
    }
    }
    if (p->mode == 19)
        func_0013CD10(&D_00475480, p->actor);
    switch (p->mode) {
    case 2: case 3: case 4: case 5:
        if (p->actor != D_0036B250)
            func_0013ABC8((char *)p->actor + 0x10D0, -1);
        break;
    case -1: case 0: case 1: case 6: case 7: case 9:
        break;
    default:
        func_0013ABC8((char *)p->actor + 0x10D0, -1);
        break;
    }
    if (p->actor == D_0036B250) {
        if (Less(p->mode, 5) && !Less(p->mode, 2)) {
            HANDLE *h = &p->fx;
            if (!p->fx.obj) {
                void *fx = func_002459F8(0x53);
                func_00244F08(fx, 0);
                func_002BBCD8(h, fx);
                func_00244F08(p->fx.obj, p->actor);
                func_00245100(p->fx.obj, 2000.0f, 3000.0f);
                func_00244E08(p->fx.obj, 1.0f);
                func_00244ED0(p->fx.obj, -0.2f);
            }
        } else if (p->fx.obj) {
            if (&p->fx) {
                func_00244CA8(p->fx.obj, 0.1f);
                func_002BBCD8(&p->fx, 0);
            }
        }
    }
    if (p->mode != -1) {
        if (!active || active->clip != clip) {
            func_0023AC58((char *)p->actor + 0x1140);
            func_00137588(clip, p->actor, blend, weight, flags, &p->actor->animation);
        }
        Notify(p->actor, 101);
    }
}
