// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Activate one existing instance group and forward its original virtual calls.
struct VirtualEntry { short delta, pad; void (*function)(); };
struct Object { char prefix[0xC]; struct VirtualEntry *vtable; };
struct Output { struct VirtualEntry *vtable; };
struct Matrix { float elements[4][4]; };
struct InstanceTable {
    int object_count;
    struct Object **objects;
    int capacity;
    int used;
    char reserved10[8];
    int *requested_keys;
    char reserved1C[0x6C - 0x1C];
};
struct Game { char prefix[0x4630]; struct InstanceTable *instances; };

int func_001FA5A8(int index, int instance);

void func_001FAFB0(struct Game *game, int index, void *owner,
                   int resource_word, int requested_key,
                   const struct Matrix *matrix, struct Output *output)
{
    struct InstanceTable *table = &game->instances[index];
    if (table->used < table->capacity) {
        int handle = func_001FA5A8(index, table->used);
        int j;
        table->requested_keys[table->used] = requested_key;
        for (j = 0; j < table->object_count; j++) {
            struct Object *object = table->objects[table->used * table->object_count + j];
            ((void (*)(void *, int, int))object->vtable[27].function)
                ((char *)object + object->vtable[27].delta, handle, 1);
            ((void (*)(void *))object->vtable[8].function)
                ((char *)object + object->vtable[8].delta);
            ((void (*)(void *, void *, int, int))object->vtable[10].function)
                ((char *)object + object->vtable[10].delta, owner, resource_word, 0);
            ((void (*)(void *, const struct Matrix *))object->vtable[42].function)
                ((char *)object + object->vtable[42].delta, matrix);
        }
        if (output)
            ((void (*)(void *, int, struct Object **))output->vtable[1].function)
                ((char *)output + output->vtable[1].delta, table->object_count,
                 &table->objects[table->used * table->object_count]);
        table->used++;
    }
}

#define OFF(t, m) ((unsigned int)&((t *)0)->m)
typedef char instance_layout[(sizeof(void *) == 4 && sizeof(struct VirtualEntry) == 8 &&
    sizeof(struct InstanceTable) == 0x6C && sizeof(struct Matrix) == 64 &&
    OFF(struct VirtualEntry, function) == 4 && OFF(struct Object, vtable) == 0xC &&
    OFF(struct Game, instances) == 0x4630 && OFF(struct InstanceTable, requested_keys) == 0x18) ? 1 : -1];
