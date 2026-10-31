// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
// Move the (two or three) anchor entries to the world positions of the owner's origin and its two offset points.
typedef int qword __attribute__((mode(TI)));
struct Entry { float x, y, z; int id; };
struct Owner { unsigned char pad0[0x60]; void *world; };
struct Anchors {
    unsigned char pad0[0x10];
    struct Owner *owner;
    unsigned char pad14[0x70 - 0x14];
    qword origin;
    unsigned char pad80[0xF8 - 0x80];
    int count;
    struct Entry *entries[3];
};
extern qword D_00325AD0[2];
qword func_001C9428(void *world, int zero, qword v);
float func_002BC420(qword *v);
float func_002BC430(qword *v);
float func_002BC448(qword *v);
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline void Store(struct Entry *entry, qword *v)
{
    float x = func_002BC420(v);
    float y = func_002BC430(v);
    float z = func_002BC448(v);
    entry->x = x;
    entry->y = y;
    entry->z = z;
}
void func_0020E5F0(struct Anchors *self)
{
    void *world = self->owner->world;
    struct Entry *first;
    qword v;
    self->entries[0]->id = -1;
    first = self->entries[0];
    v = func_001C9428(world, 0, self->origin);
    Store(first, &v);
    if (self->count >= 2) {
        struct Entry *second, *third;
        qword v1, v2;
        self->entries[1]->id = -1;
        second = self->entries[1];
        v1 = func_001C9428(world, 0, Add(self->origin, D_00325AD0[0]));
        Store(second, &v1);
        self->entries[2]->id = -1;
        third = self->entries[2];
        v2 = func_001C9428(world, 0, Add(self->origin, D_00325AD0[1]));
        Store(third, &v2);
    }
}
