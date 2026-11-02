// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct BlendClock { float now, step; };
struct BlendOwner {
    unsigned char prefix[0x130];
    M4 current;
    qword start;
    qword end;
    float deadline;
    M4 *source;
    unsigned char gap198[4];
    void *target;
};
extern struct BlendClock D_0036BB98;
extern qword D_00479350;
void func_0023CC40(void *owner);
void func_001F2408(M4 *out, M4 *source, qword start, qword end, M4 *state, qword *anchor, float time, float step);
void func_001C8248(void *target, qword value, M4 *matrix, float first, float second);
static inline float TimeLeft(float deadline, struct BlendClock *clock)
{
    return deadline - clock->now + clock->step;
}
void func_001F2870(struct BlendOwner *owner)
{
    M4 matrix;
    func_0023CC40(owner);
    if (owner->target) {
        if (owner->deadline <= D_0036BB98.now) {
            matrix = owner->source[1];
        } else {
            func_001F2408(&owner->current, &owner->source[1], owner->start, owner->end,
                          &owner->current, &owner->start, TimeLeft(owner->deadline, &D_0036BB98), D_0036BB98.step);
            matrix = owner->current;
        }
        func_001C8248(owner->target, D_00479350, &matrix, 1.0f, 1.0f);
    }
}
