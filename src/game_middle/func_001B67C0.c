// SLY3_CFLAGS: -Os -G0
// Merges a time-sorted batch of incoming entries (key, source, target, angle) into the owner's queue of up to four active
// entries: entries matching an incoming key take its time and have their angle smoothed toward the new one (with wrap-around
// over the source's angle range) and are re-aimed, unmatched queue entries are released, and the remaining incoming
// entries are appended (creating a target through func_001B6F10 when the owner is active). The queue is kept sorted by time.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Range { float low, high; };
struct Source { unsigned char pad0[0x24]; struct Method *table; };
struct Target { unsigned char pad0[0xC]; struct Method *table; };
struct Entry {
    void *key;
    struct Source *source;
    float time;
    int kind;
    struct Target *target;
    int pad14;
    float angle;
    float velocity;
    unsigned char pad20[0x30 - 0x20];
} __attribute__((aligned(16)));
struct Queue {
    unsigned char pad0[0x4E78];
    int count;
    int pad4E7C;
    struct Entry entries[4];
};
struct Owner { unsigned char pad0[0xA04]; int active; };
#define ENTRIES_OFFSET ((unsigned)&((struct Queue *)0)->entries)
struct ApproachCurve;
struct ClockStep { float now, step; };
extern struct ClockStep D_0036BB98;
extern struct ApproachCurve D_00322EA0;
extern unsigned char D_0036C700[];
void func_00292540(void *base, int count, int size, int (*compare)(const void *, const void *));
void *func_00291F38(void *destination, const void *source, int size);
// entry-time comparator (a->time < b->time ? -1 : 1)
int func_001B6798(const void *first, const void *second);
void func_002412C8(struct Target *target, float value);
float func_0011E598(float input, float target, const struct ApproachCurve *curve, float *derivative, float step);
struct Target *func_001B6F10(struct Queue *queue, int active, struct Entry *entry);
void func_001854C8(void *context, int message, void *key);
void func_001B67C0(struct Queue *queue, struct Owner *owner, int count, struct Entry *entries)
{
    int j, i;
    struct Entry *entry, *incoming, *slot;
    int n;
    register struct Target *target __asm__("$3"); /* register pin: the new target lives in $v1 across the test and the store */
    func_00292540(entries, count, sizeof(struct Entry), func_001B6798);
    for (i = queue->count; --i >= 0;) {
        entry = &queue->entries[i];
        j = count;
        goto cond;
        do {
            incoming = &entries[j];
            if (entry->key != incoming->key)
                continue;
            entry->time = incoming->time;
            if (entry->target == 0) {
                entry->angle = incoming->angle;
                entry->velocity = 0;
            } else {
                struct Range range;
                struct Method *method = &incoming->source->table[1];
                int wrapped = ((int (*)(void *, struct Range *))method->function)((char *)incoming->source + method->adjustment, &range);
                float size;
                qword position;
                if (wrapped) {
                    float delta;
                    size = range.high - range.low;
                    delta = incoming->angle - entry->angle;
                    if (size * 0.5f < delta) {
                        delta -= size;
                        incoming->angle = entry->angle + delta;
                    } else if (delta < size * -0.5f) {
                        delta += size;
                        incoming->angle = entry->angle + delta;
                    } else
                        wrapped = 0;
                }
                entry->angle = func_0011E598(entry->angle, incoming->angle, &D_00322EA0, &entry->velocity, D_0036BB98.step);
                if (wrapped) {
                    if (range.high < entry->angle)
                        entry->angle = entry->angle - size;
                    else if (entry->angle < range.low)
                        entry->angle = entry->angle + size;
                }
                method = &entry->source->table[3];
                ((void (*)(void *, struct Owner *, float, qword *, int))method->function)((char *)entry->source + method->adjustment, owner, entry->angle, &position, 0);
                method = &entry->target->table[34];
                ((void (*)(void *, qword))method->function)((char *)entry->target + method->adjustment, position);
            }
            func_00291F38(incoming, incoming + 1, (count - j) * sizeof(struct Entry) - sizeof(struct Entry));
            count--;
            goto next;
          cond:;
        } while (--j >= 0);
        if (entry->target)
            func_002412C8(entry->target, 0.5f);
        func_00291F38(entry, entry + 1, (3 - i) * sizeof(struct Entry));
        queue->count--;
    next:;
    }
    for (j = 0; j < count; j++) {
        incoming = &entries[j];
        if (owner->active && incoming->kind == 1) {
            target = func_001B6F10(queue, owner->active, incoming);
            if (!target)
                break;
            incoming->target = target;
        }
        n = queue->count;
        slot = (struct Entry *)((char *)queue + n * sizeof(struct Entry) + ENTRIES_OFFSET);
        *slot = *incoming;
        queue->count = n + 1;
        func_001854C8(D_0036C700, 0x4E, incoming->key);
    }
    func_00292540(queue->entries, queue->count, sizeof(struct Entry), func_001B6798);
}
