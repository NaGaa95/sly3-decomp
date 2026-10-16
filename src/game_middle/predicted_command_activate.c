// SLY3_CFLAGS: -Os -G0
typedef unsigned int PredictedCommandPosition __attribute__((mode(TI)));
struct PredictedCommandOwner {
    unsigned char opaque00[0x1144];
    int flags;
};
struct PredictedCommandReceiver {
    unsigned char opaque00[0x10];
    struct PredictedCommandOwner *owner;
    unsigned char opaque14[0x1C];
    unsigned char parameters[0x20];
};
PredictedCommandPosition func_001C03A0(void *owner, void *parameters, float duration);
void func_001D9EF0(void *receiver, int state, PredictedCommandPosition position);

void func_001D9E70(void *receiver)
{
    struct PredictedCommandReceiver *source = receiver;
    PredictedCommandPosition position;
    float duration = 0.0f;
    if (source->owner->flags & 1) duration = 0.7f;
    position = func_001C03A0(source->owner, source->parameters, duration);
    if (source->owner->flags & 1) func_001D9EF0(source, 0, position);
    else func_001D9EF0(source, 1, position);
}
