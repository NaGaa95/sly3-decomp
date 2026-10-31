// SLY3_CFLAGS: -Os -G0 -ffast-math
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct ResetOwner { char pad00[0xC0]; int control; };
struct ResetContext {
    struct ResetOwner *owner;
    char pad04[0x14];
    int state;
    float started;
    float updated;
};
void func_001C20A8(struct ResetContext *context)
{
    struct ResetOwner *owner = context->owner;
    context->state = -1;
    context->updated = context->started = g_clock.t;
    owner->control = 0;
}
