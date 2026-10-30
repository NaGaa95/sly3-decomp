// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct VirtualEntry { short adjustment; short reserved; int (*call)(); } VirtualEntry;
struct Object { VirtualEntry *vtable; };
struct Entry { struct Object *object; int pad; int primary; int secondary; };
struct World { unsigned char pad0[0x2F0]; int alternate; unsigned char pad2F4[0x17C4 - 0x2F4]; int table; };
struct Self { unsigned char pad0[0x10]; struct World *world; unsigned char pad14[0x44 - 0x14]; int value; };
/* 0x0047A430 has no symbol of its own; reach it through the preceding D_0047A424 object. */
extern struct { unsigned char pad[0xC]; struct Entry *entries; } D_0047A424;
int func_0018B658(int index);
void func_0018C0F8(struct Self *self, int value, struct World *world);
void func_0018C018(struct Self *self, int id)
{
    struct Entry *entry;
    struct Object *object;
    int table;
    int index;
    int value;
    int *slot;
    if (id == -1) return;
    entry = &D_0047A424.entries[id];
    object = entry->object;
    if (!object) return;
    table = self->world->table;
    if (table) {
        slot = (int *)(id * 4 + table);
        index = 0;
    } else {
        VirtualEntry *ve = &object->vtable[1];
        int values;
        index = ((int (*)(void *))ve->call)((char *)object + ve->adjustment);
        values = !self->world->alternate ? entry->secondary : entry->primary;
        slot = (int *)(index * 4 + values);
    }
    value = *slot;
    if (value == -1) return;
    if (id == 1) {
        self->value = func_0018B658(index);
    }
    func_0018C0F8(self, value, self->world);
}
