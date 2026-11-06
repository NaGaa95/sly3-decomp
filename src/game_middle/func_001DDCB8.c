// SLY3_CFLAGS: -Os -G0
// func_001DDCB8: switches the actor to mode (-1.. 2): releases the bones, remembers the animation progress and restarts
// the animation/resource for the new mode.
// Allocation note: `actor->mode = mode` is written once after the if/else (a store at the top of the join block), which
// orders the following zero-initialisations before the clock load in the first scheduling pass.
typedef int ModeVector __attribute__((mode(TI)));
struct ModeAnimation { unsigned char prefix[0x64]; float duration; };
struct ModeRuntime { unsigned char prefix0[0x14]; struct ModeAnimation *animation; unsigned char gap18[4]; float time; };
struct ModeActor {
    unsigned char prefix0[0x48];
    void *bone48, *bone4C;
    unsigned char gap50[0x1A0 - 0x50];
    ModeVector direction;
    float rate;
    unsigned char gap1B4[0x113C - 0x1B4];
    struct ModeRuntime *runtime;
    void *retained;
    unsigned char gap1144[0x1470 - 0x1144];
    unsigned char pair[0x1594 - 0x1470];
    int mode;
    float changed;
    unsigned char gap159C[0x15A4 - 0x159C];
    struct ModeAnimation *animation15A4;
    unsigned char gap15A8[0x1650 - 0x15A8];
    void *resource1650;
    unsigned char gap1654[0x165C - 0x1654];
    struct ModeAnimation *animation165C;
};
struct ModeClock { float time, step; };
extern struct ModeClock D_0036BB98;
extern ModeVector D_00317560;
void func_0028F068(void *actor, void *bone, int mode);
void func_00258F28(void *pair);
void func_00137628(void *runtime);
void func_0023AC58(void *record);
void func_00137588(struct ModeAnimation *animation, void *actor, int flags, void *runtime, float time, float rate);
void func_0023AAE8(void *resource, void *actor, int mode, int flags, void *output);
void func_001DDCB8(struct ModeActor *actor, int mode)
{
    struct ModeAnimation *animation;
    void *resource;
    int flags;
    float time;
    if (mode == actor->mode)
        return;
    if (actor->mode == 0) {
        func_0028F068(actor, actor->bone48, 2);
        func_0028F068(actor, actor->bone4C, 2);
    } else {
        if (actor->mode >= 0) {
            if (actor->mode < 3)
                actor->rate = actor->runtime->time / actor->runtime->animation->duration;
        }
    }
    actor->mode = mode;
    animation = 0;
    resource = 0;
    actor->changed = D_0036BB98.time;
    flags = 1;
    time = 0.0f;
    switch (mode) {
    case 0:
        func_0028F068(actor, actor->bone48, 1);
        func_0028F068(actor, actor->bone4C, 1);
        resource = actor->resource1650;
        actor->direction = D_00317560;
        break;
    case 1:
        animation = actor->animation15A4;
        time = actor->rate * animation->duration;
        func_00258F28(actor->pair);
        flags = 9;
        break;
    case 2:
        animation = actor->animation165C;
        flags = 9;
        time = actor->rate * animation->duration;
        break;
    }
    func_00137628(&actor->runtime);
    func_0023AC58(&actor->retained);
    func_00137588(animation, actor, flags, &actor->runtime, time, 1.0f);
    func_0023AAE8(resource, actor, -1, flags, &actor->retained);
}
