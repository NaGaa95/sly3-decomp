// SLY3_CFLAGS: -Os -G0
typedef int TransitionVector __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Animation { char prefix[0x64]; float duration; };
struct AnimationPair { unsigned int word; struct Animation *animation; };
struct AnimationRuntime {
    char prefix[0x14]; struct Animation *animation;
    char gap18[4]; float time;
};
struct TransitionActor {
    char prefix[0xC]; struct Method *methods;
    char gap10[0x48 - 0x10]; void *position, *rotation;
    char gap50[0x1A0 - 0x50];
    union { TransitionVector packed; unsigned int words[4]; } vector;
    float phase;
    char gap1B4[0x320 - 0x1B4]; char request[0x500 - 0x320];
    char message[0xE40 - 0x500]; char contextE40[0xF60 - 0xE40];
    char contextF60[0x1134 - 0xF60]; void *resource;
    char gap1138[4]; struct AnimationRuntime *runtime; void *retained;
    char gap1144[0x1470 - 0x1144]; int state; float changed;
    char gap1478[8]; struct AnimationPair first;
    char gap1488[0x1530 - 0x1488]; struct AnimationPair second;
    char gap1538[0x15E0 - 0x1538]; struct AnimationPair third;
    char gap15E8[0x16A8 - 0x15E8]; int mode;
};
struct Clock { float time; };
extern struct Clock D_0036BB98;
extern TransitionVector D_00317560;
void func_0028F068(void *, void *, int);
void func_00155328(void *);
void func_001B77F8(void *, int, int);
void func_001B4430(void *, int);
void func_001C21F0(void *, int);
int func_00239A78(void *, int);
void func_00155310(void *, int);
void func_00258F28(void *);
void func_001BDBB0(void *, int);
int func_001EA940(void *);
void func_001EA4B0(void *, int);
void func_00137628(void *);
void func_0023AC58(void *);
void func_00137588(struct Animation *, void *, int, void *, float, float);
void func_0023AB98(void *, void *, int, int, int, void *);

void func_001E9BC8(struct TransitionActor *actor, int state)
{
    int old;
    struct Animation *animation;
    void *resource;
    int flags, identifier, mask;
    float time;
    if (state == actor->state)
        return;
    switch (actor->state) {
    case 0:
        func_0028F068(actor, actor->position, 2);
        func_0028F068(actor, actor->rotation, 2);
        if (actor->mode == -1)
            func_00155328(actor);
        break;
    case 4:
        func_001B77F8(actor->request, -1, 0);
        break;
    case 5:
        func_001B4430(actor->message, -1);
        break;
    case 6:
        func_001C21F0(actor->contextE40, -1);
        break;
    case 1: case 2: case 3:
        actor->phase = actor->runtime->time / actor->runtime->animation->duration;
        break;
    case 8:
        func_0028F068(actor, actor->position, 2);
        func_0028F068(actor, actor->rotation, 2);
        break;
    }
    old = actor->state;
    actor->state = state;
    animation = 0; resource = 0; flags = 1; identifier = -1; mask = 4; time = 0.0f;
    actor->changed = D_0036BB98.time;
    switch (state) {
    case 0:
        func_0028F068(actor, actor->position, 1);
        func_0028F068(actor, actor->rotation, 1);
        resource = actor->resource;
        switch (old) {
        case 2: identifier = 0x193; break;
        case 4: identifier = 0x195; break;
        case 7: identifier = 0x197; break;
        default: identifier = 0x192; break;
        }
        if (func_00239A78(resource, identifier) < 0)
            identifier = -1;
        actor->vector.packed = D_00317560;
        mask = ((int (*)(void *))actor->methods[111].function)(
            (char *)actor + actor->methods[111].adjustment);
        func_00155310(actor, 1);
        break;
    case 1:
        animation = actor->first.animation;
        time = actor->phase * animation->duration;
        func_00258F28(&actor->first);
        flags = 9;
        break;
    case 2:
        animation = actor->second.animation;
        time = actor->phase * animation->duration;
        func_00258F28(&actor->second);
        flags = 9;
        break;
    case 3:
        animation = actor->third.animation;
        time = actor->phase * animation->duration;
        func_00258F28(&actor->third);
        flags = 9;
        break;
    case 6:
        func_001BDBB0(actor->contextF60, -1);
        break;
    case 8:
        func_0028F068(actor, actor->position, 1);
        func_0028F068(actor, actor->rotation, 1);
    case 7: {
        unsigned int *position = actor->vector.words;
        position[0] = position[1] = position[2] = 0;
        break;
    }
    case -1:
        break;
    }
    switch (actor->state) {
    case 0: case 1: case 2: case 3: case 4:
        break;
    default:
        func_001EA4B0(actor, func_001EA940(actor) ? 2 : -1);
        break;
    }
    func_00137628(&actor->runtime);
    func_0023AC58(&actor->retained);
    func_00137588(animation, actor, flags, &actor->runtime, time, 1.0f);
    func_0023AB98(resource, actor, identifier, flags, mask, &actor->retained);
    ((void (*)(void *))actor->methods[101].function)(
        (char *)actor + actor->methods[101].adjustment);
}
