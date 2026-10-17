// SLY3_CFLAGS: -Os -G0
struct HeadingMethod { short adjustment, word2; void *function; };
struct HeadingTable { unsigned char prefix[0x120]; struct HeadingMethod matrix; };
struct HeadingRuntime { unsigned char prefix[0x1C]; float time; unsigned char gap20[0x40 - 0x20]; float rate; };
struct HeadingActor {
    unsigned char prefix0[0xC];
    struct HeadingTable *methods;
    unsigned char gap10[0x110C - 0x10];
    float reference;
    unsigned char gap1110[0x113C - 0x1110];
    struct HeadingRuntime *runtime;
    void *retained;
};
struct HeadingControl {
    struct HeadingActor *actor;
    unsigned char gap4[4];
    int state;
    unsigned char gapC[0x1C - 0xC];
    int mode;
    unsigned char gap20[0x28 - 0x20];
    int index;
    int flag;
    unsigned char gap30[0xC0 - 0x30];
    void *tableC[5];
    void *tableB[5];
    void *tableA[5];
};
float func_002A3EE8(float y, float x);
float func_0011E3B8(float angle);
void func_0023AC58(void *record);
void func_00137588(void *animation, void *actor, int flags, void *output, float time, float rate);
void func_001B8EB0(struct HeadingControl *control)
{
    float heading, delta, magnitude;
    void *animation;
    struct HeadingRuntime *runtime;
    control->flag = 1;
    {
        struct HeadingMethod *method = &control->actor->methods->matrix;
        float *matrix = ((float *(*)(void *))method->function)((char *)control->actor + method->adjustment);
        heading = func_002A3EE8(matrix[1], matrix[0]);
    }
    delta = func_0011E3B8(control->actor->reference - heading);
    magnitude = __builtin_fabsf(delta);
    if (magnitude < 1.0995574f)
        control->state = 3;
    else if (2.0420351f < magnitude)
        control->state = 4;
    else if (0.0f < delta)
        control->state = 2;
    else
        control->state = 1;
    runtime = control->actor->runtime;
    if (control->mode == 2) {
        animation = control->tableA[control->index];
        if (!animation) {
            animation = control->tableB[control->state];
            if (!animation)
                animation = control->tableB[0];
        }
    } else {
        animation = control->tableC[control->state];
    }
    if (!animation)
        animation = control->tableC[0];
    func_0023AC58((char *)control->actor + 0x1140);
    func_00137588(animation, control->actor, 1, (char *)control->actor + 0x113C, runtime->time, runtime->rate);
}
