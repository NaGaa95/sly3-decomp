// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "vector_intrinsics.h"

struct ContactEntry {
    short delta, reserved;
    union {
        void *(*matrix)(void *);
        int (*predicate)(void *);
    };
};
struct ContactActor;
struct ContactSide {
    char prefix[8];
    void *owner;
    ContactActor *object;
    char reserved10[0x30];
};
union ContactNormal {
    qword packed;
    struct { float x, y, z, w; } scalar;
};
struct Contact {
    ContactSide sides[2];
    ContactNormal normal;
    char reserved90[0xC];
    int kind;
    char reservedA0[0xC];
    Contact *next;
};
struct ContactList { Contact *head; ContactList *next; };
struct ContactWorld { char prefix[0x64]; ContactList *contacts; };
struct ContactActor {
    char prefix[0xC];
    ContactEntry *table;
    char reserved10[0xCC];
    ContactWorld *world;
};
struct ContactState {
    char prefix[0x10];
    ContactActor *owner;
    char reserved14[0x24];
    int testOpposite;
};
extern "C" {
qword func_00120D98(qword first, qword second);
float func_00171C98(void *timer);
extern char D_0036BD20[];
extern float D_00325500[3], D_00325510[2];
}

extern "C" int func_001F6300(void *object)
{
    ContactState *state = (ContactState *)object;
    for (ContactList *list = state->owner->world->contacts; list; list = list->next) {
        for (Contact *contact = list->head; contact; contact = contact->next) {
            if (contact->kind == 10 || contact->kind == 14 ||
                __builtin_fabsf(contact->normal.scalar.z) > 0.7f)
                continue;
            if (!state->testOpposite)
                return 1;
            ContactActor *owner = state->owner;
            ContactEntry *entry = &owner->table[36];
            const qword *matrix = (const qword *)entry->matrix(
                (char *)owner + entry->delta);
            float score = PackedVectorX(func_00120D98(matrix[0], contact->normal.packed));
            float time = func_00171C98(D_0036BD20);
            float threshold = D_00325500[0] + time *
                (D_00325500[1] + time * D_00325500[2]);
            float lower = D_00325510[0];
            float upper = D_00325510[1];
            if (threshold < lower)
                threshold = lower;
            else if (upper < threshold)
                threshold = upper;
            if (threshold < score)
                continue;
            int different = contact->sides[1].owner != state->owner;
            int sideOffset = different << 6;
            ContactSide *side = (ContactSide *)((char *)contact + sideOffset);
            ContactActor *other = side->object;
            entry = &other->table[66];
            if (entry->predicate((char *)other + entry->delta))
                return 1;
        }
    }
    return 0;
}
