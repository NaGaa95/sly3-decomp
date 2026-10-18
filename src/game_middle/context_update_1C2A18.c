// SLY3_CFLAGS: -Os -G0
struct ContextMethod {
    short adjustment, reserved;
    void (*function)(void *);
};
struct ContextAnimationSource {
    char prefix[0x64];
    float duration;
};
struct ContextAnimation {
    char prefix[0x14];
    struct ContextAnimationSource *source;
    char gap18[4];
    float time;
    char gap20[0x40 - 0x20];
    float rate;
};
struct ContextActor {
    char prefix[0xC];
    struct ContextMethod *methods;
    char gap10[0x113C - 0x10];
    struct ContextAnimation *animation;
};
struct ContextUpdate {
    struct ContextActor *actor;
    int state;
    float stamp;
    char gapC[0x24 - 0xC];
    int notify, notified;
};
extern float D_0036BB98;
int func_00138AC8(struct ContextAnimation *);
void func_001C2E78(struct ContextUpdate *);

void func_001C2A18(struct ContextUpdate *context)
{
    int previous;
    do {
        previous = context->state;
        if (previous == 7) {
            if (D_0036BB98 - context->stamp > 5.0f) {
                func_001C2E78(context);
            }
        } else if (func_00138AC8(context->actor->animation)) {
            func_001C2E78(context);
        } else if (context->state >= 9 && context->notify && !context->notified) {
            struct ContextActor *actor = context->actor;
            struct ContextAnimation *animation = actor->animation;
            if (animation && animation->rate > 0.0f &&
                (animation->source->duration - animation->time) / animation->rate < 1.0f) {
                actor->methods[103].function((char *)actor + actor->methods[103].adjustment);
            }
        }
        if (context->state == -1) break;
    } while (context->state != previous);
}
