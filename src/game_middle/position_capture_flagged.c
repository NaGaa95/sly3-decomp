// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, word2; void *function; };
struct Position { unsigned char prefix[0x30]; qword value; };
struct ObjectTable { unsigned char prefix[0x120]; struct Method position; };
struct Object {
    unsigned char prefix[0xC];
    struct ObjectTable *methods;
    unsigned char gap10[0x2C - 0x10];
    unsigned char pad2C[3];
    unsigned char flagByte;
};
struct Tracker {
    unsigned char prefix[0xC];
    struct ObjectTable *methods;
    unsigned char gap10[0x1994 - 0x10];
    int pending;
    unsigned char gap1998[0x19A4 - 0x1998];
    int mode;
    unsigned char gap19A8[0x19B0 - 0x19A8];
    qword ownerPosition;
    qword startPosition;
    qword targetPosition;
    unsigned char gap19E0[0x1AA4 - 0x19E0];
    struct Object *target;
};
void func_0023C970(void *tracker);
#define POSITION_OF(object)     (((struct Position *(*)(void *))(object)->methods->position.function)(         (char *)(object) + (object)->methods->position.adjustment))
void func_001AB958(struct Tracker *tracker)
{
    qword start = POSITION_OF(tracker->target)->value;
    tracker->mode = 0;
    tracker->startPosition = start;
    func_0023C970(tracker);
    if (!tracker->pending) {
        long byte = tracker->target->flagByte;
        if ((int)byte & 1) {
            tracker->ownerPosition = POSITION_OF((struct Object *)tracker)->value;
            tracker->targetPosition = POSITION_OF(tracker->target)->value;
            tracker->mode = 3;
            return;
        }
    }
    tracker->mode = 0;
}
