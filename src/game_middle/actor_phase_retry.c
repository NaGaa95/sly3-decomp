// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct ActorScale { unsigned char opaque[8]; float value; };
struct ActorPhase {
    unsigned char opaque00[0x134];
    struct ActorScale *scale;
    unsigned char opaque138[0x1A0 - 0x138];
    qword direction;
    unsigned char opaque1B0[0x110C - 0x1B0];
    float heading;
    unsigned char opaque1110[0x113C - 0x1110];
    void *subject;
    unsigned char opaque1140[0x1408 - 0x1140];
    float timer;
    unsigned char opaque140C[0x1528 - 0x140C];
    int phase;
    float start_time;
    int word1530;
    void *attachment;
};
extern float D_003457A0;
int func_00138AC8(void *subject);
void func_001DE690(void *actor, int state);
void func_001DF600(void *actor, int phase);
int func_001BADF8(void *actor, float *timer, float start_time);
void func_001C0538(void *actor, int state);
qword func_0011FD70(float heading, float magnitude, float vertical);

void func_001DF418(struct ActorPhase *actor)
{
    int previous;
    for (;;) {
        previous = actor->phase;
        if (!actor->subject || func_00138AC8(actor->subject))
            func_001DE690(actor, 0);
        else if (actor->phase == 1) {
            if (actor->attachment)
                func_001DF600(actor, 2);
            else if (func_001BADF8(actor, &actor->timer, actor->start_time))
                func_001C0538(actor, 0);
        }
        if (actor->phase == previous || actor->phase == -1)
            break;
    }
    switch (actor->phase) {
    case 0: case 1:
        actor->direction = func_0011FD70(actor->heading + 3.1415927f,
            D_003457A0 * (actor->scale->value * 0.75f), 0.0f);
        break;
    }
}
