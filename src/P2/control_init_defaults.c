// SLY3_CFLAGS: -Os -G0
struct Method { short adjustment, word2; void *function; };
struct MethodTable {
    unsigned char prefix[8];
    struct Method settings;
};
struct Settings {
    unsigned char prefix[0x28];
    unsigned long flags;
    unsigned char gap30[0x3C - 0x30];
    int tagged;
};
struct Controller {
    float value;
    unsigned char gap4[0x14 - 4];
    struct MethodTable *methods;
    int id;
};
struct Owner {
    unsigned char prefix[0x1A8];
    struct Controller controller;
    unsigned char gap1C4[0x1D0 - 0x1C4];
    float scaleD0;
    float scaleD4;
    unsigned char gap1D8[0x1DC - 0x1D8];
    float scaleDC;
};
void func_0022D708(void *owner);
void func_001A0708(void *member);
void func_001C9118(void *owner, int mode);
#define SETTINGS_OF(controller) \
    (((struct Settings *(*)(void *))(controller)->methods->settings.function)( \
        (char *)(controller) + (controller)->methods->settings.adjustment))
void func_00203550(struct Owner *owner)
{
    struct Controller *controller;
    struct Settings *settings;
    struct Settings *tagSettings;
    func_0022D708(owner);
    controller = &owner->controller;
    func_001A0708((char *)owner + 0x180);
    func_001C9118(owner, 2);
    owner->scaleD4 = 1.0f;
    owner->scaleD0 = 1000.0f;
    owner->scaleDC = 1.0f;
    settings = SETTINGS_OF(controller);
    settings->flags |= 0x1000000000000000UL;
    owner->controller.value = 1250.0f;
    controller->id = -1;
    tagSettings = SETTINGS_OF(controller);
    if ((tagSettings->tagged ^ 1) & 1)
        *(int *)tagSettings->tagged &= ~0x40;
    else
        tagSettings->tagged &= ~0x40;
}
