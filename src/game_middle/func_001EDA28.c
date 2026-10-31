// Resolve the registry's object ids to objects, then collect every object of one kind into a new list.
// SLY3_CFLAGS: -Os -G0
struct AllocationRequest { int bytes, alignment; };
struct Entity { unsigned char pad[0x114]; int index; unsigned char pad118[0x140 - 0x118]; int order; };
struct Registry {
    unsigned char pad[0x10];
    int idCount;
    int *ids;
    struct Entity **entities;
    unsigned char pad1C[4];
    int foundCount;
    struct Entity **found;
    unsigned char pad28[4];
    int ready;
};
extern char D_00475480[];
struct Entity *func_0017E1B8(void *game, int kind, int id, int flags);
int func_0017E208(void *game, int kind, int id, int flags, int max, struct Entity **out);
void *func_001D24D0(struct AllocationRequest *request, void *source);
static inline void *AllocCopy(struct AllocationRequest *request, int bytes, int alignment, void *source)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return func_001D24D0(request, source);
}

void func_001EDA28(struct Registry *self)
{
    struct Entity *list[0x400];
    struct AllocationRequest request;
    struct Entity *entity;
    int i, j, count, n;
    for (i = 0; i < self->idCount; i++) {
        entity = func_0017E1B8(D_00475480, 5, self->ids[i], 0);
        entity->index = i;
        self->entities[i] = entity;
    }
    n = func_0017E208(D_00475480, 0x205, 0x91, 0, 0x400, list);
    count = 0x400;
    if (n < 0x400)
        count = n;
    self->foundCount = count;
    self->found = AllocCopy(&request, count * 4, 0x10, list);
    for (j = 0; j < self->foundCount; j++)
        self->found[j]->order = j;
    self->ready = 1;
}
