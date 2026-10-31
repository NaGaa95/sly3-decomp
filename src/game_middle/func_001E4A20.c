// SLY3_CFLAGS: -Os -G0
struct Animation;
struct Clock { float time; };
struct FlagTarget { unsigned char prefix[0x112C]; int mark; };
struct ModeActor {
    unsigned char prefix[0x1C9C];
    int mode;
    float changed;
    struct Animation *animation;
    void *runtime;
};
extern char D_00475480[];
extern struct Clock D_0036BB98;
int func_0017E208(void *game, int a, int b, int c, int max, struct FlagTarget **out);
void func_002514D8(struct FlagTarget *target, int mark);
void func_00137588(struct Animation *, void *, int, void *, float, float);

void func_001E4A20(struct ModeActor *self, int mode)
{
    struct FlagTarget *targets[32];
    int count, i;
    if (mode == self->mode)
        return;
    self->mode = mode;
    self->changed = D_0036BB98.time;
    count = func_0017E208(D_00475480, 0x105, 0x3A, 0, 32, targets);
    for (i = 0; i < count; i++) {
        struct FlagTarget *target = targets[i];
        if (mode)
            func_002514D8(target, 0x16);
        else if (target->mark == 0x16)
            func_002514D8(target, -1);
    }
    func_00137588(mode ? self->animation : 0, self, 0, &self->runtime, 0.0f, 1.0f);
}
