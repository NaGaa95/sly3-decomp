// Per-frame update of a target-follow state. The followed position is sampled
// (mode 0: path position nearest the actor, mode 1: followed object position,
// mode 2: followed object frame relative to the state matrix), expressed in the
// actor's space, projected on the blended pair of curves with a bounded
// minimisation, published as the blend fraction/weight and animation time, and
// finally the actor is moved by the difference to the sampled position.
// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
#include "../P2/mat.h"
#include "../P2/matrix_algorithms.h"
#include "../P2/state_position_ops.h"

// One packed XYZW position; the horizontal length replaces X and Y is cleared.
union FollowVector {
    qword packed;
    struct { int x, y; float z, w; } lane;
};

struct FollowSource { void *runtime; };
struct FollowEffect { char opaque00[0x64]; float duration; };
struct FollowChannel { char opaque00[0xA0]; MATRIX4 *transform; };
struct FollowState {
    SCENE_OBJECT *actor;                // 0x00
    FollowSource *source;               // 0x04
    float weight;                       // 0x08
    char opaque0C[0x1C - 0x0C];
    float fraction;                     // 0x1C
    char opaque20[0x30 - 0x20];
    FollowEffect *effect;               // 0x30
    char opaque34[4];
    FollowChannel *channel;             // 0x38
    char opaque3C[4];
    MATRIX4 matrix;                     // 0x40
    void *task;                         // 0x80
    void *path;                         // 0x84
    float time;                         // 0x88
    SCENE_OBJECT *target;               // 0x8C
    int mode;                           // 0x90
    char opaque94[0xA4 - 0x94];
    int state;                          // 0xA4
};
// Callback context of the minimised objective functions (second word is 16-aligned).
struct FollowContext {
    FollowState *state;
    qword position;
};
typedef char CheckFollowMatrix40[((int)&((FollowState *)0)->matrix == 0x40) ? 1 : -1];
typedef char CheckFollowTime88[((int)&((FollowState *)0)->time == 0x88) ? 1 : -1];
typedef char CheckFollowState[((int)&((FollowState *)0)->state == 0xA4) ? 1 : -1];
typedef char CheckFollowContext[(sizeof(FollowContext) == 0x20) ? 1 : -1];

extern "C" {
// Path position nearest the anchor; the admitted body consumes seven transported
// words and ignores the eighth (float) input, but the call site still supplies it.
void func_0022EEA0(void *path, qword anchor, int kind, void *position, void *direction,
                   float *progress, float *length, float initial);
MATRIX4 func_0011D768(const MATRIX4 &matrix);
MATRIX4 func_0011D558(const MATRIX4 &left, const MATRIX4 &right);
qword func_001C9428(SCENE_OBJECT *source, SCENE_OBJECT *destination, qword point);
// Five float inputs F12..F16: initial, step, lower, upper, tolerance.
void func_0011EF00(float (*objective)(void *, float), void *context,
                   float initial, float step, float lower, float upper, float tolerance,
                   float *out_parameter, float *out_value);
float func_00208348(void *context, float parameter);
float func_00208318(void *context, float parameter);
void func_00208288(FollowState *state, qword point, float *fraction, float *distance, float time);
void func_002081F8(FollowState *state, qword point, float *fraction, float *distance, float time);
void func_0028EA00(MATRIX3 *output, SCENE_OBJECT *source, MATRIX4 *destination, const MATRIX3 *input);
void func_0012F4F8(void *receiver, qword value);
void func_00137D08(void *runtime, int seek, float time, float rate, int update_mode);
void func_00148938(void *effect);
void func_0024E8E8(void *owner, qword difference);
void func_0024F0B0(void *owner);
}

// The square root and the transfer of its X lane stay separate statements: the Y store of the packed vector sits between them.
static inline void SquareRootX(VUXScalarCarrier &scalar)
{
    asm("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(scalar));
}
static inline int BitsX(VUXScalarCarrier scalar)
{
    int bits;
    asm("qmfc2.ni %0,%1" : "=r"(bits) : "j"(scalar));
    return bits;
}

static inline MATRIX4 *ObjectMatrix(SCENE_OBJECT *object)
{
    SCENE_VIRTUAL_ENTRY *entry = &object->vtable[36];
    return (MATRIX4 *)entry->Query((char *)object + entry->delta);
}

static inline qword ObjectPosition(SCENE_OBJECT *object)
{
    return ((const qword *)ObjectMatrix(object))[3];
}

extern "C" void func_00208378(FollowState *state)
{
    FollowVector position;      // not written by other modes: original stack contents are used
    MATRIX3 basis;
    if (state->state == -1)
        return;
    switch (state->mode) {
    case 0: {
        void *path = state->path;
        func_0022EEA0(path, ObjectPosition(state->actor), 0, &position, 0, 0,
                      &state->time, state->time);
        break;
    }
    case 1:
        position.packed = ObjectPosition(state->target);
        break;
    case 2: {
        MATRIX4 product;
        product = func_0011D558(*ObjectMatrix(state->target), func_0011D768(state->matrix));
        const MATRIX3 *rotation = (const MATRIX3 *)&product;
        position.packed = ((const qword *)&product)[3];
        basis = *rotation;
        break;
    }
    }
    FollowContext context;
    FollowVector local;
    context.state = state;
    local.packed = func_001C9428(0, state->actor, position.packed);
    VUXScalarCarrier length = PackedHorizontalDot(local.packed, local.packed);
    SquareRootX(length);
    local.lane.y = 0;
    local.lane.x = BitsX(length);
    context.position = func_001C9428(state->actor, 0, local.packed);
    float t, result, projection;
    if (state->mode == 2) {
        MATRIX3 transformed, temporary;
        func_0011EF00(func_00208348, &context, 0.5f, 0.1f, 0.0f, 1.0f, 0.0f, &t, &result);
        func_00208288(state, context.position, &projection, 0, t);
        func_0028EA00(&temporary, 0, state->channel->transform, &basis);
        transformed = temporary;
        func_0012F4F8(state->task, func_0011D3C0(&transformed));
    } else {
        func_0011EF00(func_00208318, &context, 0.5f, 0.1f, 0.0f, 1.0f, 0.0f, &t, &result);
        func_002081F8(state, context.position, &projection, 0, t);
    }
    func_00137D08(state->source->runtime, 0, t * state->effect->duration, 0.0f, 0);
    state->fraction = projection;
    state->weight = 1.0f - projection;
    func_00148938(state->effect);
    qword target = position.packed;
    func_0024E8E8(state->actor, PackedDifference(target, ObjectPosition(state->actor)));
    func_0024F0B0(state->actor);
}
