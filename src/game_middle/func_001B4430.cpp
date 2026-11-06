// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001B4430: set the step of a hero action context (Sly 2 func_00192BD8 relative).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;

struct VTE { short delta, pad; void *fn; };
struct M3 { qword row[3]; };
struct M4 { qword row[4]; };
struct CLIP { char pad0[0x64]; float duration; };
struct JOY { char pad0[8]; float amount; };
struct ANIMATION;
struct COMPONENT { void *object; };
struct PROGRAM_ITEM { void *owner; CLIP *clip; };
struct LO { char pad0[0xC]; VTE *vt; char pad10[0x3C - 0x10]; uint flags; };
struct EFFECT;
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x3C - 0x10]; uint flags; char pad40[0x134 - 0x40]; JOY *pjoy;
    char pad138[0x148 - 0x138]; void *focus; char pad14C[0x1A0 - 0x14C]; qword velocity; char pad1B0[0x1C0 - 0x1B0];
    char local[0x21C - 0x1C0]; float tStamp; char pad220[0x240 - 0x220]; qword position; char pad250[0x260 - 0x250];
    qword posOffset; char pad270[0x940 - 0x270]; char x940[0x9FC - 0x940]; int x9FC; char pada00[0x1120 - 0xA00]; int vec[3]; char pad112C[0x113C - 0x112C];
    ANIMATION *animation; COMPONENT component; int x1144; char pad1148[0x1198 - 0x1148]; void *x1198;
    char pad119C[0x13F4 - 0x119C]; int x13F4; char pad13F8[0x1404 - 0x13F8]; int x1404; char pad1408[0x1458 - 0x1408];
    int x1458; char pad145C[0x18F0 - 0x145C]; char x18F0[0x1AA0 - 0x18F0]; LO *first; LO *second; char pad1AA8[0x1AD0 - 0x1AA8];
    CLIP *specialClip; char pad1AD4[0x1C90 - 0x1AD4]; PROGRAM_ITEM program; char pad1C98[0x1EF8 - 0x1C98]; EFFECT *effect;
};
struct SOURCE {
    char pad0[0xC]; VTE *vt; char pad10[0xD0 - 0x10]; ACTOR *owner; char padD4[0x16C - 0xD4]; ACTOR *other;
    ACTOR *x170; char pad174[0x180 - 0x174]; ACTOR *actor; char pad184[0x18C - 0x184]; ACTOR *x18C; char pad190[0x1CC - 0x190];
    int enabled; char pad1D0[0x1E0 - 0x1D0]; ACTOR *x1E0;
};
struct DATA { char pad0[0x10]; float x; char pad14[0xC]; float y; char pad24[0xC]; float z; };
struct AUX { char pad0[0x108]; SOURCE *target; char pad10C[4]; DATA *data; };
struct SETTING { void *focus; };
struct CONTEXT {
    ACTOR *pactor; float tStamp; int action; int step; float tStep; SOURCE *focus; SETTING *setting; float param;
    float value; int reversed; int index; float speed; int previous; char pad34[4]; int changed; char pad3C[0x68 - 0x3C]; AUX *aux;
    char pad6C[0x170 - 0x6C]; CLIP *clip170, *clip174, *clip178, *clip17C; PROGRAM_ITEM program180;
    char pad188[0x230 - 0x188]; void *script230; CLIP *clip234, *clip238; char pad23C[4]; PROGRAM_ITEM program240;
    char pad248[0x314 - 0x248]; CLIP *overrideClip; float gain318, gain31C; CLIP *clip320, *clip324, *clip328;
    void *script32C; char pad330[0x430 - 0x330]; CLIP *clip430; char pad434[0x440 - 0x434]; char attach[0x470 - 0x440];
    CLIP *attachClip; char pad474[0x4F0 - 0x474]; CLIP *clip4F0, *clip4F4, *clip4F8; int tag; int fInhibit; char pad504[0x50C - 0x504];
    CLIP *clip50C, *clip510, *clip514; void *camera;
};
struct CLOCK { float t, dt; };
union U { qword q; float f[4]; int i[4]; };

extern "C" {
extern CLOCK g_clock;
extern ACTOR *D_00370AC0;         // the player
extern ACTOR *D_0038AE90;
extern qword D_00317530;
extern qword D_00317560;
extern qword D_00322CF0;
int func_0013B500(void *, int);
void func_0022EA88(SOURCE *, qword, void *, void *, void *, float *, float *);
void func_001A1A28(SOURCE *, int);
void func_002495E0(SOURCE *, ACTOR *);
void func_0013BD00(SOURCE *, ACTOR *);
void func_0013BD88(SOURCE *, ACTOR *);
void func_0024F3B8(ACTOR *, SOURCE *, int);
void func_0022E148(SOURCE *, float, qword *, qword *);
EFFECT *func_002459F8(int);
void func_00244F08(EFFECT *, SOURCE *);
void func_002BBCD8(EFFECT **, EFFECT *);
void func_0024E920(ACTOR *, SOURCE *);
void func_0024F0B0(ACTOR *);
void func_0024E8E8(ACTOR *, qword);
void *func_0016B180(void *, void *, int, ACTOR *, void *);
void *func_00169BF8(int);
void *func_001F4A80(ACTOR *);
void func_00169CE0(void *);
void func_00169C40(void **);
void func_00208B20(void *, int);
void func_002093E8(void *);
void func_00244CA8(EFFECT *, float);
void func_001F47C8(ACTOR *, void *);
void func_001B5890(CONTEXT *);
void func_00209470(void *, SOURCE *);
void func_00258F28(PROGRAM_ITEM *);
void func_00137628(ANIMATION **);
void func_0023AC58(COMPONENT *);
void func_00137588(CLIP *, ACTOR *, float, float, int, ANIMATION **);
void func_0023AAE8(void *, ACTOR *, int, int, COMPONENT *);
void func_001ADCA0(ACTOR *, int);
}

static inline void Zero3(int *p) { p[2] = 0; p[1] = 0; p[0] = 0; }
static inline M4 *MatrixOf(void *p, VTE *vt) { VTE &v = vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.delta); }
static inline M4 *MatrixOf(ACTOR *p) { return MatrixOf(p, p->vt); }
static inline M4 *MatrixOf(SOURCE *p) { return MatrixOf(p, p->vt); }
static inline void SourceState(SOURCE *p, int state)
{
    VTE &v = p->vt[3];
    ((void (*)(void *, int, void *, void *, void *, void *))v.fn)((char *)p + v.delta, state, 0, 0, 0, 0);
}
static inline void Notify(LO *p, int slot) { VTE &v = p->vt[slot]; ((void (*)(void *))v.fn)((char *)p + v.delta); }
static inline void Notify(ACTOR *p, int slot) { VTE &v = p->vt[slot]; ((void (*)(void *))v.fn)((char *)p + v.delta); }
static inline void SetVector(ACTOR *p, int slot, qword q) { VTE &v = p->vt[slot]; ((void (*)(void *, qword))v.fn)((char *)p + v.delta, q); }
static inline void SetPointer(ACTOR *p, int slot, void *pv) { VTE &v = p->vt[slot]; ((void (*)(void *, void *))v.fn)((char *)p + v.delta, pv); }
// bit 0 set: the word holds the flags itself; otherwise it points to them
static inline void AddFlags(uint *pflags, uint bits)
{
    uint w = *pflags;
    if ((w ^ 1) & 1)
        *(uint *)w |= bits;
    else
        *pflags = w | bits;
}

static inline bool Less(int n, int limit) { return n < limit; }   // keeps the two range tests apart
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline void SetX(float *pg, qword q) { __asm__("sw %1,%0" : "=m"(*pg) : "r"(q)); }
static inline float GetY(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline float GetZ(qword q) { float f; __asm__("pextuw %0,$zero,%1" : "=r"(f) : "r"(q)); return f; }

static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
static inline qword Unit(qword v, qword len)
{
    qword r;
    __asm__ __volatile__("vdiv $Q,$vf0w,%0x\n\tvwaitq" : : "j"(len));
    __asm__("vmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v));
    return r;
}
static inline qword Normalize(qword v, qword fallback)
{
    qword len = Length(v);
    if (X(len) < 0.0001f)
        return fallback;
    return Unit(v, len);
}
static inline void Normalize(qword *pv) { *pv = Normalize(*pv, D_00317530); }
static inline qword Transform(const M4 &m, qword q)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r) : "j"(m.row[0]), "j"(m.row[1]), "j"(m.row[2]), "j"(q));
    return r;
}

extern "C" void func_001B4430(CONTEXT *p, int step)
{
    if (step == p->step)
        return;

    // leave the old step
    switch (p->step) {
    case 1:
        p->pactor->x1144 = -1;
        break;
    case -1:
        if (p->focus && func_0013B500(p->focus, 9)) {
            SOURCE *source = p->focus;
            func_0022EA88(source, MatrixOf(p->pactor)->row[3], 0, 0, 0, &p->param, &p->value);
        }
        switch (p->action) {
        case 0:
            SourceState(p->focus, 5);
            break;
        case 1: {
            SOURCE *source = p->focus;
            source->x18C = p->pactor;
            func_001A1A28(source, 2);
            if (p->pactor == D_00370AC0)
                Notify(p->pactor->first, 9);
            break;
        }
        case 4: {
            SOURCE *source = p->focus;
            func_002495E0(source, p->pactor);
            func_0024F3B8(p->pactor, source, 1);
            Zero3(p->pactor->vec);
            ACTOR *actor = p->pactor;
            actor->position = MatrixOf(source)->row[3];
            break;
        }
        case 3: {
            SOURCE *source = p->focus;
            U dir, tangent;
            source->x1E0 = p->pactor;
            SourceState(source, 5);
            source->x1E0 = 0;
            func_0013BD00(source, p->pactor);
            func_0024F3B8(p->pactor, source, 1);
            p->speed = 0.0f;
            Zero3(p->pactor->vec);
            p->index = -1;
            func_0022E148(source, p->param, &p->pactor->position, &tangent.q);
            dir.i[2] = 0;
            Normalize(&dir.q);
            qword normal = dir.q;   // read before the call: a VU pseudo spilled to 0x50
            p->reversed = X(Dot(normal, MatrixOf(p->pactor)->row[0])) < -0.2f;
            break;
        }
        case 2: {
            EFFECT *effect = func_002459F8(0x5C);
            func_00244F08(effect, 0);
            func_002BBCD8(&D_00370AC0->effect, effect);
            break;
        }
        case 11:
            if (p->focus)
                func_0013BD00(p->focus, p->pactor);
            break;
        case 12:
            if (p->focus)
                func_0024E920(p->pactor, p->focus);
            func_0024F0B0(p->pactor);
            break;
        }
        p->previous = -1;
        p->pactor->tStamp = g_clock.t;
        break;
    case 7:
        if (Less(step, 11) && !Less(step, 9)) {
            SOURCE *source = p->focus;
            if (source->other) {
                qword pos = MatrixOf(source->other)->row[3];
                SetVector(p->pactor, 34, Sub(pos, p->pactor->posOffset));
                func_0024E8E8(p->pactor, MatrixOf(source->other)->row[0]);
                SetPointer(p->pactor, 35, p->pactor->local);
                SetVector(p->pactor, 40, D_00317560);
                SetVector(p->pactor, 41, D_00317560);
            }
            void *owner = func_001F4A80(p->pactor);
            p->camera = func_0016B180(func_00169BF8(0x50), owner, 13, p->pactor, p->pactor->x1198);
            func_00169CE0(p->camera);
        }
        break;
    case 9:
    case 10:
        if (!(Less(step, 11) && !Less(step, 9)))
            func_00169C40(&p->camera);
        break;
    }

    // enter the new one
    CLIP *clip = 0;
    void *script = 0;
    int flags = 1;
    int special = 0;
    float blend = 0.0f;
    float speed = 1.0f;
    switch (step) {
    case -1:
        p->fInhibit = 0;
        switch (p->action) {
        case 0:
            SourceState(p->focus, 6);
            break;
        case 1:
            func_001A1A28(p->focus, 0);
            if (p->pactor == D_00370AC0)
                Notify(p->pactor->first, 8);
            break;
        case 4: {
            SOURCE *source = p->focus;
            func_002495E0(source, 0);
            func_0024F3B8(p->pactor, source, 0);
            break;
        }
        case 3: {
            SOURCE *source = p->focus;
            SourceState(source, 6);
            func_0013BD88(source, p->pactor);
            func_0024F3B8(p->pactor, source, 0);
            break;
        }
        case 6:
            func_00208B20(p->pactor->x18F0, -1);
            break;
        case 11:
            if (p->focus)
                func_0013BD88(p->focus, p->pactor);
            p->pactor->x13F4 = 0;
            p->pactor->x9FC = -1;
            break;
        case 5:
        case 9:
            func_00208B20(p->attach, -1);
            break;
        case 12:
            p->pactor->x1404 = -1;
            func_002093E8(p->pactor->x940);
            p->pactor->x1458 = 0;
            break;
        case 2:
            if (D_00370AC0->effect) {
                func_00244CA8(D_00370AC0->effect, 0.0f);
                func_002BBCD8(&D_00370AC0->effect, 0);
            }
            break;
        }
        if (p->pactor->focus) {
            if (p->pactor->focus == p->aux)
                func_001F47C8(p->pactor, 0);
            else if (p->pactor->focus == p->setting->focus)
                func_001F47C8(p->pactor, 0);
        }
        p->pactor->x1144 = -1;
        p->action = -1;
        p->step = -1;
        p->focus = 0;
        p->setting = 0;
        p->param = p->value = 0.0f;
        p->changed = 0;
        p->tag = -1;
        break;
    case 0:
    case 5:
        switch (p->action) {
        case 0:
            clip = p->clip174;
            flags = 9;
            break;
        case 13:
            clip = step == 0 ? p->clip510 : p->clip174;
            flags = 9;
            break;
        case 2:
            clip = p->clip514;
            flags = 9;
            break;
        case 1:
            script = p->script230;
            flags = 1;
            break;
        case 4:
            clip = p->clip234;
            flags = 9;
            special = 7;
            break;
        case 3:
            if (p->focus->enabled) {
                CLIP *override = p->overrideClip;
                if (override) {
                    clip = override;
                    p->gain318 = p->gain31C = 0.0f;
                } else
                    clip = p->clip238;
            } else
                clip = p->clip238;
            flags = 9;
            special = 31;
            break;
        case 6:
        case 7:
        case 14:
            clip = p->clip320;
            flags = 9;
            break;
        case 5:
        case 9:
            speed = 0.0f;
            func_00209470(p->attach, p->focus);
            clip = p->attachClip;
            blend = clip->duration * 0.5f;
            break;
        case 10:
            clip = p->pactor->pjoy->amount >= 0.5f ? p->clip4F0 : p->clip4F4;
            break;
        case 11:
            if (p->tag == 20) {
                clip = D_0038AE90->specialClip;
                if (clip)
                    break;
            }
            clip = p->clip4F8;
            break;
        case 12:
            clip = p->clip50C;
            break;
        }
        p->pactor->velocity = D_00317560;
        break;
    case 1:
        switch (p->action) {
        case 0:
            clip = p->clip170;
            if (!p->pactor->focus) {
                if (func_0013B500(p->focus, 11)) {
                    SOURCE *source = p->focus;
                    if (source->actor)
                        func_001F47C8(p->pactor, source->actor);
                    else {
                        func_001B5890(p);
                        p->aux->target = source;
                        func_001F47C8(p->pactor, p->aux);
                    }
                } else if (func_0013B500(p->focus, 32)) {
                    SOURCE *source = p->focus;
                    if (source->owner)
                        func_001F47C8(p->pactor, source->owner);
                } else if (func_0013B500(p->focus, 36)) {
                    SOURCE *source = p->focus;
                    if (source->owner)
                        func_001F47C8(p->pactor, source->owner);
                    else {
                        func_001B5890(p);
                        qword v = Transform(*MatrixOf(source), D_00322CF0);
                        SetX(&p->aux->data->x, v);
                        p->aux->data->y = GetY(v);
                        p->aux->data->z = GetZ(v);
                        func_001F47C8(p->pactor, p->aux);
                    }
                }
            }
            break;
        case 13:
            clip = p->clip170;
            break;
        }
        flags = 9;
        break;
    case 4:
        switch (p->action) {
        case 3:
            clip = p->program240.clip;
            func_00258F28(&p->program240);
            break;
        case 1:
            clip = p->program180.clip;
            func_00258F28(&p->program180);
            break;
        case 2:
            clip = p->pactor->program.clip;
            func_00258F28(&p->pactor->program);
            break;
        }

        flags = 9;
        break;
    case 3:
        clip = p->clip17C;
        p->pactor->velocity = D_00317560;
        break;
    case 2:
        clip = p->clip178;
        p->pactor->velocity = D_00317560;
        break;
    case 7: {
        SOURCE *source = p->focus;
        clip = p->clip324;
        if (source->other) {
            M3 basis = *(M3 *)MatrixOf(source->other);
            func_0024E8E8(p->pactor, basis.row[0]);
        }
        p->pactor->velocity = D_00317560;
        source->x170 = p->pactor;
        SourceState(source, 5);
        source->x170 = 0;
        break;
    }
    case 8:
        clip = p->clip328;
        p->pactor->velocity = D_00317560;
        SourceState(p->focus, 6);
        break;
    case 9:
        script = p->script32C;
        if (p->step == 7) {
            AddFlags(&p->pactor->flags, 0x10);
            if (p->pactor == D_00370AC0) {
                AddFlags(&p->pactor->first->flags, 0x10);
                AddFlags(&D_00370AC0->second->flags, 0x10);
            }
        }
        p->pactor->velocity = D_00317560;
        break;
    case 10:
        clip = p->clip430;
        p->pactor->x1144 = -1;
        flags = 9;
        p->pactor->velocity = D_00317560;
        break;
    }
    p->step = step;
    p->tStep = g_clock.t;
    if (step != -1) {
        func_00137628(&p->pactor->animation);
        func_0023AC58(&p->pactor->component);
        func_00137588(clip, p->pactor, blend, speed, flags, &p->pactor->animation);
        func_0023AAE8(script, p->pactor, -1, flags, &p->pactor->component);
        Notify(p->pactor, 101);
        if (func_0013B500(p->pactor, 52))
            func_001ADCA0(p->pactor, special);
    }
}
