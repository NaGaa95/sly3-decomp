// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Info {
    unsigned char pad0[0x10]; int kind; unsigned char pad14[4]; int id; unsigned char pad1C[4]; int mask;
    struct Method *table;
};
struct Source { unsigned char pad0[0x18]; int id; };
struct Entry {
    void *key;
    struct Info *source;
    float time;
    int kind;
    void *target;
    float stamp;
    float angle;
    float velocity;
    qword position;
} __attribute__((aligned(16)));
struct Object { unsigned char pad0[0xC]; struct Method *table; unsigned char pad10[0x34 - 0x10]; float radius; };
struct Link { unsigned char pad0[0x18]; int id; };
struct Owner {
    unsigned char pad0[0x164]; int flags;
    unsigned char pad168[0x32C - 0x168]; struct Object *x32C;
    unsigned char pad330[0x38C - 0x330]; struct Object *x38C;
    unsigned char pad390[0x514 - 0x390]; struct Object *x514; struct Link *x518;
    unsigned char pad51C[0x101C - 0x51C]; struct Object *x101C;
    unsigned char pad1020[0x19F4 - 0x1020]; struct Object *x19F4;
};
struct ClockStep { float now, step; };
extern struct ClockStep D_0036BB98;
extern struct Owner *D_00370AC0;
extern float D_00345704;
void *func_001D2898(void *destination, const void *source, int size);
void *func_00292034(void *destination, int value, int size);
void *func_00291F38(void *destination, const void *source, int size);
static inline void MoveEntries(struct Entry *destination, struct Entry *source, unsigned size) { func_00291F38(destination, source, size); }
static inline void ZeroEntry(struct Entry *entry) { func_00292034(entry, 0, sizeof(struct Entry)); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float LengthSquared(qword v)
{
    qword d = v, one;
    float f;
    __asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=j"(one) : "j"(v));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
static inline float Length(qword v)
{
    qword d = v, one;
    float f;
    __asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
void func_001B5E18(void *game, struct Owner *owner, qword position, struct Object *target, struct Info *info, int count, struct Entry *entries)
{
    struct Entry entry;
    float radius;
    int i;
    {
        float *radiusPtr = ((float *(*)(void *))target->table[26].function)((char *)target + target->table[26].adjustment);
        radius = radiusPtr ? *radiusPtr : target->radius;
    }
    {
        qword here = ((qword *(*)(void *))target->table[36].function)((char *)target + target->table[36].adjustment)[3];
        qword d = Sub(here, position);
        int outside = radius * radius < LengthSquared(d);
        if (outside)
            return;
    }
    if (target == owner->x514)
        return;
    if (target == owner->x32C)
        return;
    if (info->id && owner->x518 && info->id == owner->x518->id)
        return;
    if (target == owner->x38C)
        return;
    if (target == owner->x101C)
        return;
    if (owner == D_00370AC0 && target == owner->x19F4)
        return;
    if (!(owner->flags & info->mask))
        return;
    ((void (*)(void *, struct Owner *, float *))info->table[2].function)((char *)info + info->table[2].adjustment, owner, &entry.angle);
    ((void (*)(void *, struct Owner *, qword *, int, float))info->table[3].function)((char *)info + info->table[3].adjustment, owner, &entry.position, 0, entry.angle);
    entry.kind = info->kind;
    entry.time = Length(Sub(position, entry.position));
    ((void (*)(void *, float *))info->table[4].function)((char *)info + info->table[4].adjustment, &entry.time);
    if (D_00345704 < entry.time)
        return;
    if (info->id) {
        for (i = 0; i < count; i++) {
            struct Entry *other = &entries[i];
            if (!other->source)
                break;
            if (((struct Source *)other->source)->id == info->id) {
                if (entry.time < entries[i].time) {
                    func_001D2898(&entries[i], &entries[i + 1], (count - 1 - i) * sizeof(struct Entry));
                    ZeroEntry(&entries[count] - 1);
                    entries[count - 1].time = D_00345704;
                } else
                    return;
                break;
            }
        }
    }
    i = count;
    do {
        struct Entry *previous = &entries[--i];
        if (previous->kind > entry.kind || (previous->kind == entry.kind && previous->time < entry.time)) {
            i++;
            break;
        }
    } while (i != 0);
    if (i == count)
        return;
    MoveEntries(&entries[i + 1], &entries[i], (count - i) * sizeof(struct Entry) - sizeof(struct Entry));
    entry.key = target;
    entry.source = info;
    entry.stamp = D_0036BB98.now;
    entry.target = 0;
    entry.velocity = 0;
    entries[i] = entry;
}
