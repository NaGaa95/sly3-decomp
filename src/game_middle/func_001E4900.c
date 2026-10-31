// SLY3_CFLAGS: -Os -G0 -fno-cse-skip-blocks
struct Animation;
struct Clock { float time; };
struct Holder { unsigned char prefix[0x1F0]; int active; };
struct ModeActor {
    unsigned char prefix[0x113C];
    void *runtime;
    void *retained;
    unsigned char gap1144[0x1C64 - 0x1144];
    int mode;
    float changed;
    struct Animation *animations[9];
    struct Holder *holder;
};
extern struct Clock D_0036BB98;
void func_0023AC58(void *);
void func_00137588(struct Animation *, void *, int, void *, float, float);

void func_001E4900(struct ModeActor *self, int mode)
{
    struct Animation *animation;
    if (mode == self->mode)
        return;
    self->mode = mode;
    animation = 0;
    self->changed = D_0036BB98.time;
    if ((unsigned int)mode < 9)
        animation = self->animations[mode];
    func_0023AC58(&self->retained);
    func_00137588(animation, self, mode == 0 ? 9 : 1, &self->runtime, 0.0f, 1.0f);
    if (!self->mode)
        self->holder->active = 1;
    else
        self->holder->active = 0;
}
