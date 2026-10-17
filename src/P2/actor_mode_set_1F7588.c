// SLY3_CFLAGS: -Os -G0
struct ModeMethod { short adjustment, word2; void *function; };
struct ModeTable { unsigned char prefix[0x40]; struct ModeMethod first; struct ModeMethod second; };
struct ModeObject { unsigned char prefix[0xC]; struct ModeTable *methods; };
struct ModeSelf {
    unsigned char prefix0[0xC];
    struct ModeTable *methods;
    unsigned char gap10[0x130 - 0x10];
    int mode;
    float changed;
    float remaining;
    void *resource;
    void *request;
    struct ModeObject *object;
    unsigned char gap148[0x16C - 0x148];
    int word16C;
};
struct ModeClock { float now; };
extern struct ModeClock D_0036BB98;
extern int D_00325548[];
void func_001C7A00(void *object, int a, int b);
void func_0023AAE8(void *resource, void *actor, int id, int flags, void **output);
void func_0023AC58(void **request);
void func_00239DB8(void *request, int value);
void func_0023A790(void *request, float remaining);
void func_001F7588(struct ModeSelf *self, int mode)
{
    float remaining;
    struct ModeObject *object;
    struct ModeMethod *method;
    if (self->mode == mode)
        return;
    remaining = 0.0f;
    if (mode != 0 && mode != 4)
        func_001C7A00(self, 0, 0);
    if (self->mode == -1) {
        func_0023AAE8(self->resource, self, -1, 0, &self->request);
        remaining = self->remaining;
        self->word16C = 0;
    }
    if (mode == -1) {
        func_0023AC58(&self->request);
        method = &self->methods->second;
        ((void (*)(void *))method->function)((char *)self + method->adjustment);
    }
    switch (mode) {
    case 0:
    case 3:
    case 4:
        object = self->object;
        if (object) {
            method = &object->methods->first;
            ((void (*)(void *))method->function)((char *)object + method->adjustment);
        }
        break;
    default:
        object = self->object;
        if (object) {
            method = &object->methods->second;
            ((void (*)(void *))method->function)((char *)object + method->adjustment);
        }
        break;
    }
    self->mode = mode;
    self->changed = D_0036BB98.now;
    if (mode != -1) {
        if (self->request) {
            func_00239DB8(self->request, D_00325548[mode]);
            if (remaining != 0.0f)
                func_0023A790(self->request, remaining);
        }
    }
}
