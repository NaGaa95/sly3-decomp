// SLY3_CFLAGS: -Os -G0
struct PendingScene { char unknown00[0x28]; unsigned long flags; };
struct PendingGame {
    char unknown00[0x3BE4];
    int count;
    struct PendingScene *objects[64];
    float releaseTimes[64];
};
extern struct PendingGame D_00475480;
extern float D_0036BB98;
int func_001C80C0(void *receiver)
{
    struct PendingScene *object = (struct PendingScene *)receiver;
    int i;
    if (object->flags & (1UL << 58))
        return 1;
    if (object->flags & (1UL << 57)) {
        for (i = 0; i < D_00475480.count; i++) {
            if (object == D_00475480.objects[i]) {
                if (D_0036BB98 >= D_00475480.releaseTimes[i]) {
                    object->flags |= 1UL << 58;
                    return 1;
                }
                break;
            }
        }
    }
    return 0;
}
