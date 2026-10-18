// SLY3_CFLAGS: -Os -G0
struct Object {
    char pad[0x120];
    unsigned long flags;
};

struct Item {
    int unused;
    struct Object *object;
};

struct Allocation {
    int bytes;
    int alignment;
};

void *func_001D25B0(struct Allocation *);

void func_0025D240(int count, struct Item **items, int *result_count,
                   struct Object ***result)
{
    struct Allocation allocation;
    struct Object **objects;
    int used = 0;
    int i;
    int j;
    allocation.bytes = count * 4;
    allocation.alignment = 16;
    objects = (struct Object **)func_001D25B0(&allocation);
    for (i = 0; i < count; i++) {
        struct Object *object = items[i]->object;
        if (!(object->flags & 0x4000000000000000UL)) {
            object->flags |= 0x4000000000000000UL;
            objects[used++] = object;
        }
    }
    for (j = 0; j < used; j++)
        objects[j]->flags &= ~0x4000000000000000UL;
    *result_count = used;
    *result = objects;
}
