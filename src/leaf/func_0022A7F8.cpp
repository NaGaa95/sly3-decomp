// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-expensive-optimizations
#include "../P2/vector_intrinsics.h"
#include "../P2/matrix_algorithms.h"
// The jump table of func_0022A7F8 is followed in the original by the FLT_MAX literals of func_0022BB78 and func_0022BF40 (the same translation unit), so the three functions live in this file.
// func_0022A7F8: movement output of a scripted action. Dispatches on the action node's type (38..103): curve following,
// walking to or following a target, stop actions, and the blocked flag; it sets the actor's heading and fills the actor's
// controller output (x/y direction, speed, flags). Based on the structure of Sly 2 func_001E46A0, decoded fresh.
// Default assembler (hazard nops); the 66-entry jump table is padded by it, see build/naga_work/w60/NOTES.md.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct Method { short delta; short pad; void *fn; };
struct PATH { char pad00[0xD4]; int cyclic; };
struct Out { float x, y, speed; char pad0C[0xC]; unsigned flags; };
union Slot { int i; float f; };
struct Node { unsigned type : 8; unsigned pad01 : 24; int pad04; Slot *a; };
struct Obj {
    char pad00[0xC]; Method *vt;
    char pad10[0x508 - 0x10]; int mode; int active; char pad510[4]; PATH *motion; char pad518[4]; float motionTime;
    char pad520[0x101C - 0x520]; PATH *curve; float curveTime;
    char pad1024[0x110C - 0x1024]; float heading;
    char pad1110[0x140C - 0x1110]; Out out;
    char pad1428[0x19D0 - 0x1428]; qword oldPosition;
    char pad19E0[0x1A00 - 0x19E0]; qword position;
};
struct Self {
    char pad00[0x48]; Node *node; Obj *actor; int blocked;
    char pad54[0x80 - 0x54]; float prevMotion, prevCurve;
};
extern "C" {
extern float D_00326B20[3];
extern float D_00341FF0[2];
extern qword D_00317530;
float func_0022E0B8(PATH *, float);
void func_0022E330(PATH *, qword *, qword *, float);
void *func_001F4A80(Obj *);
qword func_001681B0(void *, qword);
float func_001205C8(qword);
float func_0011E3B8(float);
float func_0022DFD8(PATH *);
float func_0022DFC0(PATH *);
void func_001A9960(Out *, float);
void func_001A9940(Out *, int);
void func_001A9918(Out *, int);
int func_0011E9F0(float, float, float);
void func_0024E878(Obj *, float);
qword func_001C94E8(void *, Obj *, qword);
Obj *func_00226770(Self *, int);
void func_0022AEC8(Self *, Obj *, qword *, float *);
void func_0022E148(PATH *, float, qword *, qword *);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword SubR(qword b, qword a) { qword r; __asm__("vsub.xyzw %0,%2,%1" : "=j"(r) : "j"(b), "j"(a)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline qword Root(qword a) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(a)); return r; }
static inline float X(qword a) { float r; __asm__("mtc1 %1,%0" : "=f"(r) : "r"(a), "j"(a)); return r; }
static inline int VectorBits(qword v) { int i; __asm__("" : "=r"(i) : "r"(v)); return i; }
static inline float ToFloat(int bits) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(bits)); return f; }
static inline int WordY(qword v) { int w; __asm__("prot3w %0,%1" : "=r"(w) : "r"(v)); return w; }
static inline int WordZ(qword v) { int w; __asm__("pextuw %0,$0,%1" : "=r"(w) : "r"(v)); return w; }
static inline qword Normalize(qword a)
{
    qword length = Root(Dot(a, a));
    __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "+j"(length) : "j"(a));
    return length;
}
static inline qword NormalizeOr(qword a, qword fallback)
{
    register qword alt __asm__("$4") = fallback;   // pin: the fallback vector is held in a0 (the original loads it into $a0)
    qword length = Root(Dot(a, a));
    if (X(length) < 0.0001f)
        length = alt;
    else
        __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "+j"(length) : "j"(a));
    return length;
}
static inline float LengthXY(qword a)
{
    qword r;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(a));
    return X(Root(r));
}
#define MATRIX(o) ((qword *(*)(void *))(o)->vt[36].fn)((char *)(o) + (o)->vt[36].delta)
struct Work { U from, to, normal; float heading; };
extern "C" void func_0022A7F8(Self *self)
{
    Work work;
    Node *node = self->node;
    Obj *actor = self->actor;
    Out *out = &actor->out;
    switch (node->type) {
    case 38: {
        int reverse = 0;
        float t = func_0022E0B8(actor->curve, actor->curveTime + 50.0f);
        func_0022E330(actor->curve, &work.from.q, 0, t);
        t = func_0022E0B8(actor->curve, actor->curveTime - 50.0f);
        func_0022E330(actor->curve, &work.to.q, 0, t);
        qword dir = func_001681B0(func_001F4A80(actor), Sub(work.from.q, work.to.q));
        actor->heading = func_001205C8(dir);
        *(int *)&out->x = VectorBits(dir);
        out->y = PackedVectorY(dir);
        if (actor->curve->cyclic) {
            float forward, backward;
            if (self->prevCurve < actor->curveTime) {
                forward = actor->curveTime - self->prevCurve;
                { float s = func_0022DFD8(actor->curve) + self->prevCurve; backward = s - actor->curveTime; }
            } else {
                backward = self->prevCurve - actor->curveTime;
                { float s = func_0022DFD8(actor->curve) + actor->curveTime; forward = s - self->prevCurve; }
            }
            if (forward < backward) reverse = 1;
        } else if (self->prevCurve < actor->curveTime)
            reverse = 1;
        if (reverse) {
            actor->heading = func_0011E3B8(actor->heading + 3.1415927f);
            out->x = -out->x;
            out->y = -out->y;
        }
        func_001A9960(out, 1.0f);
        break;
    }
    case 41: case 42: case 43: case 44: case 45: case 46:
    stopped:
        func_001A9960(out, 0.0f);
        if (actor->active != -1) out->flags |= 0x20;
        break;
    case 47: {
        Obj *target = func_00226770(self, node->a[2].i);
        if (!target) goto stopped;
        func_0022AEC8(self, target, 0, &work.heading);
        func_0024E878(actor, work.heading);
        actor->heading = work.heading;
        goto stopped;
    }
    case 48: {
        func_001A9960(out, __builtin_fabsf(node->a[1].f));
        if (node->a[4].i) out->flags |= 8;
        Obj *target = func_00226770(self, node->a[0].i);
        if (!target) goto activityFlags;
        if (actor->active != -1 && actor->mode == 3) {
            PATH *motion = actor->motion;
            func_0022E148(motion, actor->motionTime, &work.from.q, &work.to.q);
            work.to.f[2] = 0.0f;
            work.to.q = NormalizeOr(work.to.q, D_00317530);
            int reverse = 0;
            actor->heading = func_001205C8(work.to.q);
            if (motion->cyclic) {
                float forward, backward;
                if (self->prevMotion < actor->motionTime) {
                    forward = actor->motionTime - self->prevMotion;
                    { float s = func_0022DFC0(motion) + self->prevMotion; backward = s - actor->motionTime; }
                } else {
                    backward = self->prevMotion - actor->motionTime;
                    { float s = func_0022DFC0(motion) + actor->motionTime; forward = s - self->prevMotion; }
                }
                if (forward < backward) reverse = 1;
            } else if (self->prevMotion < actor->motionTime)
                reverse = 1;
            if (reverse) actor->heading = func_0011E3B8(actor->heading + 3.1415927f);
        } else {
            func_0022AEC8(self, target, &work.from.q, 0);
            qword captured = work.from.q;
            work.to.q = Sub(captured, MATRIX(actor)[3]);
            actor->heading = func_001205C8(work.to.q);
            float distance = LengthXY(work.to.q);
            float gain = D_00326B20[0] + distance * (D_00326B20[1] + distance * D_00326B20[2]);
            float low = D_00341FF0[0], high = D_00341FF0[1];
            if (gain < low) gain = low;
            else if (high < gain) gain = high;
            out->speed *= gain;
        }
    }
    activityFlags:
        if (actor->active != -1 && (actor->mode == 0 || actor->mode == 0xD)) out->flags |= 0x20;
        break;
    case 53: {
        func_001A9960(out, __builtin_fabsf(node->a[1].f));
        Obj *target = func_00226770(self, node->a[0].i);
        if (!target || actor->active == -1 || actor->mode != 8) break;
        func_0022AEC8(self, target, &work.from.q, 0);
        qword first = work.from.q;
        work.to.q = SubR(MATRIX(actor)[3], first);
        work.to.f[2] = 0.0f;
        work.normal.q = Normalize(func_001C94E8(0, actor, work.to.q));
        out->x = -work.normal.f[1] * out->speed;
        out->y = work.normal.f[0] * out->speed;
        break;
    }
    case 101:
        out->flags |= 0x20;
        func_001A9960(out, 0.0f);
        break;
    case 103: {
        qword position = actor->position;
        qword oldPosition = actor->oldPosition;
        int near = 0;
        if (func_0011E9F0(PackedVectorX(position), PackedVectorX(oldPosition), 0.1f)) {
            int y = WordY(position), oldY = WordY(oldPosition);
            if (func_0011E9F0(ToFloat(y), ToFloat(oldY), 0.1f)) {
                int z = WordZ(position), oldZ = WordZ(oldPosition);
                near = func_0011E9F0(ToFloat(z), ToFloat(oldZ), 0.1f) != 0;
            }
        }
        if (near) func_001A9940(out, 0x40);
        func_001A9960(out, 0.0f);
        break;
    }
    case 54:
        func_001A9960(out, 0.0f);
        break;
    case 93:
        self->blocked = 1;
        break;
    case 94:
        self->blocked = 0;
        break;
    }
    if (self->blocked) func_001A9918(out, 0x10);
}


// ---- func_0022BB78 ----

// Each frame supplies one complete eighty-byte sample. Translation defaults
// copy all four stored matrix words. Packed Euler W is Z sign-extension
// residue from the established platform operation, not a fourth angle.
struct TrajectorySample {
    qword position;
    qword rotation;
    float scale;
    float time_offset;
    int word28;
    int word2C;
    int use_explicit;
    unsigned char unused34[0x50 - 0x34];
};
typedef char TrajectorySampleIs80[(sizeof(TrajectorySample) == 0x50) ? 1 : -1];

// Only these eighty-four consumed bytes have a layout claim; no whole-prefix
// copy or claim about the external trailing record is made.
struct TrajectoryFrameDataPrefix {
    TrajectorySample sample;
    float additional_time;
};
struct TrajectoryFrameReferenceView {
    unsigned char unused[8];
    const TrajectoryFrameDataPrefix *data;
};
struct TrajectoryTask;
struct TrajectoryOwner;
struct TrajectoryNodeView {
    unsigned char prefix14[0x14];
    TrajectoryOwner *owner;
    unsigned char unused18[0x88 - 0x18];
    float time;
    TrajectoryTask *effect;
};
struct TrajectoryVirtualEntry {
    short delta;
    short reserved;
    void *call;
};
struct TrajectoryObjectView {
    unsigned char prefix[0xC];
    TrajectoryVirtualEntry *table;
    unsigned char unused10[0x118 - 0x10];
    float scalar118;
};

extern "C" {
    extern qword D_00317560;
    float func_00226458(TrajectoryOwner *);
    void *func_00226B20(void *);
    int func_0011E9F0(float, float, float);
    void *func_00169BF8(unsigned int);
    void *func_0016B5E8(void *, void *, int);
    void func_00169CE0(TrajectoryTask *);
    void func_0016BDE8(TrajectoryTask *, const TrajectorySample *,
                     const TrajectorySample *, const TrajectorySample *);
    void func_0022BB78(TrajectoryNodeView *, const TrajectoryFrameReferenceView *,
                      const TrajectoryFrameReferenceView *,
                      const TrajectoryFrameReferenceView *);
}

static inline bool PackedNear(qword reference, qword value)
{
    return func_0011E9F0(PackedVectorX(reference), PackedVectorX(value), 0.0001f)
        && func_0011E9F0(PackedVectorY(reference), PackedVectorY(value), 0.0001f)
        && func_0011E9F0(PackedVectorZ(reference), PackedVectorZ(value), 0.0001f);
}

static inline const MATRIX4 *Matrix(TrajectoryObjectView *provider)
{
    TrajectoryVirtualEntry *entry = provider->table + 36;
    return static_cast<MATRIX4 *>(((void *(*)(void *))entry->call)(
        (char *)provider + entry->delta));
}

void func_0022BB78(TrajectoryNodeView *p,
                  const TrajectoryFrameReferenceView *first,
                  const TrajectoryFrameReferenceView *second,
                  const TrajectoryFrameReferenceView *third)
{
    if (first->data->additional_time == 0.0f)
        p->time = 3.4028235e38f;
    else
        p->time = (func_00226458(p->owner) + first->data->sample.time_offset)
                + first->data->additional_time;

    TrajectorySample samples[3] = {
        first->data->sample, second->data->sample, third->data->sample
    };
    TrajectoryObjectView *provider =
        static_cast<TrajectoryObjectView *>(func_00226B20(p));

    for (unsigned int i = 0; i < 3; ++i) {
        TrajectorySample *sample = &samples[i];
        if (!sample->use_explicit) {
            if (PackedNear(D_00317560, sample->position)) {
                const MATRIX4 *matrix = Matrix(provider);
                __builtin_memcpy(&sample->position, matrix->mat[3], 16);
            }
            if (PackedNear(D_00317560, sample->rotation))
                sample->rotation = func_0011D3C0((const MATRIX3 *)Matrix(provider));
        }
        if (sample->scale == 0.0f)
            sample->scale = provider->scalar118;
    }

    if (!p->effect) {
        p->effect = static_cast<TrajectoryTask *>(
            func_0016B5E8(func_00169BF8(0x170), provider, 13));
        func_00169CE0(p->effect);
    }
    func_0016BDE8(p->effect, &samples[0], &samples[1], &samples[2]);
}


// ---- func_0022BF40 ----
extern "C" {
// Create a child node for an owner from a pool: zeroed 0x180-byte block, construct, link to owner/parent/resource, register
// in the owner's child list and run its first virtual hook.
struct ChildVirtualEntry { short delta; short pad; void (*call)(void *); };
struct ChildSpec { unsigned char pad00[4]; int resource; };
struct ChildOwner { unsigned char pad00[0x48]; unsigned char children[0x10]; };
struct ChildNode {
    unsigned char pad00[0xC]; struct ChildVirtualEntry *vtable;
    unsigned char pad10[4]; struct ChildOwner *owner; void *handle[1]; void *root; void *resource;
    unsigned char pad24[8]; struct ChildSpec *spec;
    unsigned char pad30[0x88 - 0x30]; float f88;
    unsigned char pad8C[0x15C - 0x8C]; unsigned char list15C[0x20];
};
extern char D_00479D44[];
extern char D_00475480[];
void *func_0011E118(void *pool);
void *func_00292034(void *destination, int value, unsigned int bytes);
void func_002BF0C0(void *node);
void func_002BF050(void **handle, void *target);
void *func_0017E1B8(void *game, int kind, int index, void *argument);
void func_0011AF38(void *list, int count);
void func_0011AF90(void *list, void *item);
struct ChildNode *func_0022BF40(struct ChildOwner *owner, struct ChildSpec *spec, struct ChildNode *parent)
{
    struct ChildNode *node = (struct ChildNode *)func_0011E118(D_00479D44);
    func_00292034(node, 0, 0x180);
    func_002BF0C0(node);
    node->owner = owner;
    func_002BF050(node->handle, parent);
    if (parent)
        node->root = parent->root;
    else
        node->root = owner;
    if (spec->resource != -1)
        node->resource = func_0017E1B8(D_00475480, 5, spec->resource, 0);
    node->spec = spec;
    node->f88 = 3.4028235e38f;
    func_0011AF38(node->list15C, 8);
    func_0011AF90(owner->children, node);
    node->vtable[1].call((char *)node + node->vtable[1].delta);
    return node;
}

}
