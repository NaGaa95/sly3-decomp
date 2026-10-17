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
struct Triple { int first; float second; int third; };
struct Owner {
    unsigned char prefix0[0x28];
    unsigned long flags;
    unsigned char gap30[0xD0 - 0x30];
    struct Controller controller;
    unsigned char gapEC[0x130 - 0xEC];
    struct Triple vector;
    unsigned char gap13C[0x150 - 0x13C];
    int modeA;
    int modeB;
    unsigned char gap158[0x160 - 0x158];
    float scale;
    float offset;
};
extern float D_003221D0;
void func_0028FD70(void *self);
void func_001A0708(void *member);
void func_001C9118(void *owner, int mode);
#define SETTINGS_OF(controller) \
    (((struct Settings *(*)(void *))(controller)->methods->settings.function)( \
        (char *)(controller) + (controller)->methods->settings.adjustment))
void func_001A3308(struct Owner *owner)
{
    struct Controller *controller;
    struct Settings *settings;
    struct Settings *tagSettings;
    struct Triple *vector;
    func_0028FD70(owner);
    controller = &owner->controller;
    func_001A0708((char *)owner + 0xEC);
    owner->modeA = 8;
    owner->modeB = 9;
    vector = &owner->vector;
    vector->first = 0;
    vector->second = 1.0f;
    vector->third = 0;
    func_001C9118(owner, 2);
    settings = SETTINGS_OF(controller);
    settings->flags |= 0x1000000000000000UL;
    owner->controller.value = 1250.0f;
    controller->id = -1;
    tagSettings = SETTINGS_OF(controller);
    if ((tagSettings->tagged ^ 1) & 1)
        *(int *)tagSettings->tagged &= ~0x40;
    else
        tagSettings->tagged &= ~0x40;
    owner->controller.value = 1525.0f;
    owner->flags |= 0x1000000000000000UL;
    owner->scale = 0.5f;
    owner->offset = D_003221D0;
}
