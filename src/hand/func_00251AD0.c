// Forward the actual actor object and packed position when the original receiver gate and flags permit it.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int FLAGS64 __attribute__((mode(DI)));
typedef int QWORD __attribute__((mode(TI)));
struct FlagsOwner {
    char prefix[0x120];
    FLAGS64 flags;
};
struct Actor {
    char prefix[0x40];
    void *object;
    char gap44[8];
    struct FlagsOwner *owner;
    char gap50[0x10];
    QWORD position;
};
struct Receiver {
    char prefix[0x218];
    struct Actor *actor;
    char gap21C[0x2AC];
    unsigned int enabled;
    void *destination;
};
int func_001BADC0(void *receiver);
void func_001C0F18(void *receiver, void *object, QWORD position);
void func_00251AD0(struct Receiver *p) {
    if (p->enabled && func_001BADC0(p)) {
        struct Actor *actor = p->actor;
        if (!(actor->owner->flags & ((FLAGS64)1 << 61))) func_001C0F18(p->destination, actor->object, actor->position);
    }
}
