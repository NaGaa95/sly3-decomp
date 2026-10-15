// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int UpdateVector __attribute__((mode(TI)));
struct O;
struct SCENE_OBJECT;
struct SceneRateState;
struct SideTrigger;
struct PendingTransitionState;

struct UpdateVirtualEntry {
    short delta, unused;
    union {
        UpdateVector (*vector)(void *);
        void (*state)(void *, int);
        void (*change)(void *, SCENE_OBJECT *, void *, int);
    } call;
};
struct UpdateParent {
    char prefix[0x10];
    UpdateParent *parent;
    char reserved14[0x128-0x14];
    unsigned long flags;
};
struct UpdateContact {
    void *frame;
    UpdateParent *object;
};
struct UpdateFields {
    char prefix[0xC];
    UpdateVirtualEntry *table;
    char reserved10[0x130-0x10];
    int state;
    float time;
    char reserved138[0x188-0x138];
    UpdateContact *pending;
};

extern "C" {
extern float D_0036BB98;
void func_0023C660(SceneRateState *);
void func_001F7770(SideTrigger *);
void func_001F6A60(O *);
void func_001F7240(PendingTransitionState *);
}

static inline UpdateVector UpdateGetVector(UpdateFields *source)
{
    UpdateVirtualEntry *entry = &source->table[38];
    return entry->call.vector((char *)source + entry->delta);
}
static inline void UpdateSetState(UpdateFields *source, int state)
{
    UpdateVirtualEntry *entry = &source->table[80];
    entry->call.state((char *)source + entry->delta, state);
}
static inline float UpdateLengthSquared(UpdateVector vector)
{
    UpdateVector product, one;
    float result;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\t"
            "vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(product), "=&j"(one) : "j"(vector));
    __asm__("qmfc2.ni %0,%1" : "=r"(result) : "j"(product));
    return result;
}
static inline float UpdateZ(UpdateVector vector)
{
    float result;
    __asm__("pextuw %0,$0,%1" : "=r"(result) : "r"(vector));
    return result;
}

extern "C" void func_001F7388(O *receiver)
{
    UpdateFields *source = (UpdateFields *)receiver;
    func_0023C660((SceneRateState *)receiver);
    func_001F7770((SideTrigger *)receiver);
    switch (source->state) {
    case 0:
        if (10000.0f < UpdateLengthSquared(UpdateGetVector(source)))
            func_001F6A60(receiver);
    case 4:
        func_001F7240((PendingTransitionState *)receiver);
        break;
    case 2:
        if (UpdateZ(UpdateGetVector(source)) < 0.0f)
            UpdateSetState(source, 3);
        break;
    case 3: {
        UpdateVector vector = UpdateGetVector(source);
        if (source->pending && UpdateZ(vector) < 25.0f) {
            UpdateParent *parent = source->pending->object;
            for (; parent && !(parent->flags & 0x80UL); parent = parent->parent) {}
            if (parent) {
                UpdateVirtualEntry *entry = &source->table[10];
                void *frame = source->pending->frame;
                entry->call.change((char *)source + entry->delta,
                    (SCENE_OBJECT *)source->pending->object, frame, 15);
            }
            source->pending = 0;
            UpdateSetState(source, 0);
        } else if (5.0f < D_0036BB98 - source->time) {
            UpdateSetState(source, -1);
        } else {
            func_001F6A60(receiver);
            func_001F7240((PendingTransitionState *)receiver);
        }
        break;
    }
    case 1:
    case 5:
        break;
    }
}

extern "C" const int D_00325548[6] = {153, 154, 155, 156, 157, 158};
