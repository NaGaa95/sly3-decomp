// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int CrossWord __attribute__((mode(TI)));
struct CrossMethod { short adjustment, word2; void *function; };
struct CrossTable { unsigned char prefix[0x120]; CrossMethod position; unsigned char gap128[0x138 - 0x128]; CrossMethod velocity; };
struct CrossRecord {
    unsigned char prefix[0xC];
    struct CrossReceiver *receiver;
    CrossWord local;
    unsigned char gap20[0x30 - 0x20];
    CrossWord world;
};
struct CrossReceiver {
    unsigned char prefix[0xC];
    CrossTable *methods;
    unsigned char gap10[0x218 - 0x10];
    void *holder;
};
struct CrossMatrix { unsigned char prefix[0x30]; CrossWord position; };
extern "C" void func_0024E660(void *receiver, void *holder, int index);

static inline CrossWord CrossDifference(CrossWord left, CrossWord right)
{
    CrossWord result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(left), "j"(right));
    return result;
}
static inline CrossWord Cross3(CrossWord first, CrossWord second)
{
    CrossWord result;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1"
            : "=j"(result) : "j"(first), "j"(second));
    return result;
}

extern "C" void func_001AA8D0(CrossReceiver *receiver, void *holder, int index)
{
    func_0024E660(receiver, holder, index);
    if (holder != receiver->holder) {
        CrossRecord *record = (CrossRecord *)((char *)holder + (index << 6));
        CrossReceiver *owner = record->receiver;
        if (owner == receiver) {
            CrossWord point = record->world;
            CrossMethod *velocityMethod = &owner->methods->velocity;
            CrossWord velocity = ((CrossWord (*)(void *))velocityMethod->function)((char *)owner + velocityMethod->adjustment);
            CrossWord local = record->local;
            CrossMethod *positionMethod = &owner->methods->position;
            CrossMatrix *matrix = ((CrossMatrix *(*)(void *))positionMethod->function)((char *)owner + positionMethod->adjustment);
            record->world = CrossDifference(point, Cross3(velocity, CrossDifference(local, matrix->position)));
        }
    }
}
