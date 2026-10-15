// SLY3_CFLAGS: -Os -G0
struct PathRecord { int index, word4, key; };
struct PathActor {
    unsigned char opaque00[0x3C];
    unsigned int dirty;
    unsigned char opaque40[0x130 - 0x40];
    float minimum, maximum, rate, first_delay, second_delay, duration, scale;
    unsigned char opaque14C[0x15C - 0x14C];
    struct PathRecord records[6];
    unsigned char opaque1A4[0x1AC - 0x1A4];
    float first_speed, second_speed;
    unsigned char opaque1B4[0x200 - 0x1B4];
    int state;
    unsigned char opaque204[0x210 - 0x204];
    int selection;
};
extern int D_003242E8[6];
void func_0023AE08(void *actor);
void func_001D5978(struct PathActor *actor)
{
    int i;
    func_0023AE08(actor);
    actor->minimum = 400.0f;
    actor->maximum = 800.0f;
    actor->rate = 2.0f;
    actor->first_delay = 6.0f;
    actor->second_delay = 6.0f;
    actor->duration = 10.0f;
    actor->scale = 1.0f;
    for (i = 0; i < 6; i++) {
        struct PathRecord *record = &actor->records[i];
        record->key = D_003242E8[i];
        record->index = -1;
    }
    actor->first_speed = 300.0f;
    actor->second_speed = 1000.0f;
    actor->state = -1;
    actor->selection = -1;
    if ((actor->dirty ^ 1) & 1)
        *(unsigned int *)actor->dirty |= 2;
    else
        actor->dirty |= 2;
}
