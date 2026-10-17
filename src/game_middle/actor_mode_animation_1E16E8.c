// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, word2; void *function; };
struct ActorTable {
    unsigned char prefix[0x140];
    struct Method rebase;
};
struct Triple { int x, y, z; };
struct ModeActor {
    unsigned char prefix0[0xC];
    struct ActorTable *methods;
    unsigned char gap10[0x1A0 - 0x10];
    struct Triple origin;
    unsigned char gap1AC[0x113C - 0x1AC];
    void *runtime;
    unsigned char retained[4];
    unsigned char gap1144[0x18C0 - 0x1144];
    int mode;
    float changed;
    void *animationA;
    void *animationB;
    void *animationC;
    void *animationD;
    int cleared;
};
struct ModeClock { float now; };
extern struct ModeClock D_0036BB98;
extern qword D_00324850;
void func_0023AC58(void *record);
qword func_001C94E8(void *source, void *destination, qword direction);
void func_00137588(void *animation, void *receiver, int flags, void *output, float time, float rate);
void func_001E16E8(struct ModeActor *actor, int mode)
{
    void *animation;
    int flags;
    if (mode == actor->mode)
        return;
    actor->mode = mode;
    actor->changed = D_0036BB98.now;
    animation = 0;
    flags = 1;
    switch (mode) {
    case 0: {
        struct Triple *origin;
        animation = actor->animationA;
        origin = &actor->origin;
        origin->z = 0;
        origin->y = 0;
        actor->origin.x = 0;
        break;
    }
    case 1:
        animation = actor->animationB;
        flags = 9;
        break;
    case 2: {
        struct Method *method;
        qword direction;
        struct Triple *origin = &actor->origin;
        actor->cleared = 0;
        animation = actor->animationC;
        origin->z = 0;
        origin->y = 0;
        actor->origin.x = 0;
        direction = func_001C94E8(actor, 0, D_00324850);
        method = &actor->methods->rebase;
        ((void (*)(void *, qword))method->function)((char *)actor + method->adjustment, direction);
        break;
    }
    case 3:
        animation = actor->animationD;
        break;
    case -1:
        actor->cleared = 0;
        return;
    }
    func_0023AC58((char *)actor + 0x1140);
    func_00137588(animation, actor, flags, &actor->runtime, 0.0f, 1.0f);
}
