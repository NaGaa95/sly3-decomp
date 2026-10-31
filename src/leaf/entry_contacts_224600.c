// For each entry measure its anchor distance and, when contacts exist, trigger the earliest contact and record its time.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Contact {
    int first;
    unsigned char opaque04[0xC];
    qword position;
    unsigned char opaque20[0x4C - 0x20];
    void *target;
    unsigned char opaque50[0xA4 - 0x50];
    float time;
    unsigned char opaqueA8[4];
    struct Contact *next;
};
struct Entry {
    unsigned char opaque000[0x160];
    float earliest;
    float latest;
    struct Contact *contacts;
    unsigned char opaque16C[4];
};
struct Owner {
    unsigned char opaque000[0x178];
    int count;
    struct Entry *entries;
};
extern qword D_00317560;
void func_00224338(struct Owner *owner, struct Entry *entry, qword *points, float *distance);
void func_00240CB0(void *self, int a, void *target, int b, int c, int d, qword e, qword f, int g);

void func_00224600(struct Owner *owner)
{
    int i;
    for (i = 0; i < owner->count; i++) {
        struct Entry *entry = &owner->entries[i];
        qword points[2];
        float distance;
        func_00224338(owner, entry, points, &distance);
        if (entry->contacts == 0) {
            entry->earliest = entry->latest = distance;
        } else {
            struct Contact *best = 0;
            struct Contact *contact;
            float earliest = distance;
            for (contact = entry->contacts; contact; contact = contact->next) {
                if (contact->time < earliest) {
                    earliest = contact->time;
                    best = contact;
                }
            }
            func_00240CB0(owner, best->first, best->target, 0x1000, 10, 0, best->position, D_00317560, 0);
            entry->latest = earliest;
        }
    }
}
