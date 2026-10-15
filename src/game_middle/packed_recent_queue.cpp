// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "../P2/state_position_ops.h"

typedef unsigned int RecentObjectFlags __attribute__((mode(DI)));

struct RecentObject {
    int word0;
    int id;
    char gap08[0x10];
    RecentObjectFlags flags;
};

struct PackedRecentEntry {
    int id;
    int word4;
    RecentObject *object;
    float time;
    qword position;
};

struct PackedRecentQueue {
    int word0;
    int count;
    int gap08[2];
    PackedRecentEntry entries[32];
};

struct PackedRecentClock { float now, step; };
extern "C" PackedRecentClock D_0036BB98;
extern "C" void *func_00291F38(void *destination, void *source, int bytes);
extern "C" void *func_00292034(void *destination, int value, int bytes);

static inline qword RecentSquaredLengthXYZ(qword difference)
{
    qword one;
    asm("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\t"
        "vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "+j"(difference), "=&j"(one));
    return difference;
}

static inline float RecentDistance(qword left, qword right)
{
    return PackedSquareRootX(RecentSquaredLengthXYZ(PackedDifference(left, right)));
}

extern "C" void func_001C0F18(PackedRecentQueue *p, RecentObject *object, qword position)
{
    int i;
    PackedRecentEntry *entry;
    for (i = 1; i < p->count; ++i) {
        entry = &p->entries[i];
        if (object == entry->object && RecentDistance(position, entry->position) < 50.0f) {
            if (i != 1) {
                PackedRecentEntry saved = *entry;
                func_00291F38(&p->entries[2], &p->entries[1], (i - 1) * sizeof(PackedRecentEntry));
                p->entries[1] = saved;
            }
            break;
        }
    }
    if (i >= p->count) {
        if ((unsigned int)p->count < 32)
            ++p->count;
        func_00291F38(&p->entries[1], &p->entries[0], p->count * sizeof(PackedRecentEntry) - sizeof(PackedRecentEntry));
    }
    entry = &p->entries[0];
    func_00292034(entry, 0, sizeof(PackedRecentEntry));
    if (object) {
        p->entries[0].id = object->id;
        entry->object = object;
        object->flags |= (RecentObjectFlags)1 << 20;
    }
    p->entries[0].position = position;
    entry->time = D_0036BB98.now;
}
