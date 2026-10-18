// SLY3_CFLAGS: -Os -G0
struct Holder;
struct ReadyOwner {
    char unknown00[0x3D8];
    void *timer;
    int unknown3DC;
    int blocked;
    char unknown3E4[0x10D0 - 0x3E4];
    struct Holder *holder;
};
struct ReadyTask {
    char unknown00[0x10];
    struct ReadyOwner *owner;
    char unknown14[0x30 - 0x14];
    void *target;
    char unknown34[0x40 - 0x34];
    int blocked;
};
int func_00170500(struct Holder *holder, void *key);
int func_002564C8(void *timer);
int func_001A4390(struct ReadyTask *task)
{
    if (task->blocked)
        return 0;
    if (task->owner->blocked)
        return 0;
    if (func_00170500(task->owner->holder, task->target)) {
        if (task->owner->timer)
            return func_002564C8(task->owner->timer);
    }
    return 1;
}
