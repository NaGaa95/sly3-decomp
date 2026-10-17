// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct Selector;
struct Animation { char unknown00[0x48]; int state; };
struct EventOwner {
    char unknown00[0x1BC]; float angle;
    char unknown1C0[0x11BC - 0x1C0]; int storedPhase; int unknown11C0; int livePhase;
};
struct EventContext {
    EventOwner *owner; char unknown04[0x18 - 4]; int mode;
    char unknown1C[0x34 - 0x1C]; float gain;
};
struct EventController { EventContext *context; int state; Animation *primary; int unknown0C; Animation *secondary; Selector *selector; };
extern "C" {
extern int D_003457E0;
void func_0024CCB0(Selector *selector);
void func_001BE5A8(void *controller, int state);
int func_00260758(void *animation, int event);
void func_00262450(void *animation, int event);
void func_00262280(void *animation, int event);
void func_00261580(void *animation, int event, float gain);
}
static inline void Below(int &value, Animation *animation)
{
    value = 0;
    if (!animation || animation->state < 2)
        value = 1;
}
static inline void Equal(int &value, Animation *animation)
{
    value = 0;
    if (!animation || animation->state == 2)
        value = 1;
}
extern "C" void func_001BEA30(void *receiver)
{
    EventController *controller = (EventController *)receiver;
    if (controller->selector)
        func_0024CCB0(controller->selector);
    switch (controller->state) {
    case -1:
        return;
    case 5: {
        int first, second;
        Below(first, controller->primary);
        second = 1;
        if (controller->context->mode == 1)
            Below(second, controller->secondary);
        if (first && second)
            func_001BE5A8(controller, -1);
        return;
    }
    case 0: {
        int first, second;
        Equal(first, controller->primary);
        D_003457E0 = -1;
        second = 1;
        if (controller->context->mode == 1)
            Equal(second, controller->secondary);
        if (first && second)
            func_001BE5A8(controller, 1);
        break;
    }
    case 2:
        if (!func_00260758(controller->secondary, 0x3D0))
            func_001BE5A8(controller, 3);
        break;
    case 3:
        func_001BE5A8(controller, 4);
        break;
    case 4:
        if (!func_00260758(controller->secondary, 0x3D1))
            func_001BE5A8(controller, 1);
        break;
    }
    if (!controller->primary)
        return;
    if (controller->state) {
        int previous = controller->context->owner->livePhase;
        if (previous == 4) {
            if (D_003457E0 != previous)
                func_00262450(controller->primary, 0x3CE);
            if (controller->context->owner->livePhase == previous)
                goto store;
        }
        if (D_003457E0 == 4)
            func_00262280(controller->primary, 0x3CE);
store:
        D_003457E0 = controller->context->owner->storedPhase;
    }
    func_00261580(controller->primary, 0x3CD,
        (controller->context->owner->angle + 3.14159265f) * 0.15915494f);
    func_00261580(controller->primary, 0x3CC, controller->context->gain);
}
