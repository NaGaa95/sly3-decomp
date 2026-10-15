// Update registered object phases and three mutation-aware intrusive resource lists.
// SLY3_CFLAGS: -Os -G0
struct GameUpdateList {
    void *head;
    void *tail;
    int link_offset;
};
struct GameUpdateIterator {
    struct GameUpdateList *list;
    void **next;
    int link_offset;
    struct GameUpdateIterator *previous;
};
struct GameUpdateVirtualEntry {
    short delta;
    short reserved;
    void (*call)();
};
struct GameUpdateObject {
    unsigned char prefix[0xC];
    struct GameUpdateVirtualEntry *table;
};
struct GameUpdateLinkedObject {
    unsigned char prefix[0xC];
    struct GameUpdateVirtualEntry *table;
    unsigned char unused10[0x22C-0x10];
    struct GameUpdateLinkedObject *next;
};
struct GameUpdateEntry {
    unsigned int flags;
    struct GameUpdateObject *object;
};
struct GameUpdateView {
    unsigned char prefix4514[0x4514];
    struct GameUpdateList list4514;
    unsigned char unused4520[0x4648-0x4520];
    int count;
    int word464C;
    int *current_index;
    struct GameUpdateEntry *entries;
    unsigned char unused4658[0x473C-0x4658];
    struct GameUpdateLinkedObject *linked_objects;
    unsigned char unused4740[0x4784-0x4740];
    struct GameUpdateList list4784;
    unsigned char unused4790[0x480C-0x4790];
    struct GameUpdateList list480C;
};
typedef char GameUpdatePointerIs4[(sizeof(void *) == 4) ? 1 : -1];
typedef char GameUpdateListIs12[(sizeof(struct GameUpdateList) == 12) ? 1 : -1];
typedef char GameUpdateIteratorIs16[(sizeof(struct GameUpdateIterator) == 16) ? 1 : -1];
typedef char GameUpdateEntryIs8[(sizeof(struct GameUpdateEntry) == 8) ? 1 : -1];

extern struct GameUpdateIterator *D_0036AE94;
extern float D_0036BB9C;
extern unsigned char D_00375290[];
extern unsigned char D_004BC230[];
extern unsigned char D_00474FF0[];
extern unsigned char D_0036B138[];
void func_0015DE78(struct GameUpdateView *);
void func_0015B0E8(struct GameUpdateView *);
void func_0015B918(struct GameUpdateView *);
void func_0027DA70(struct GameUpdateView *);
void func_00137900(void *);
void func_00202D80(void *);
void func_00173950(void *);
void func_00242A58(struct GameUpdateView *);
void func_001E8288(void);
void func_00235FF8(void);
void func_001CF0D0(void *);
void func_002848D0(void *);
void func_00247728(void *);
void func_0027DE38(struct GameUpdateView *);
void func_0025CB38(struct GameUpdateView *);
void func_00129E20(void *);

static inline void BeginIterator(struct GameUpdateIterator *iterator,
                                 struct GameUpdateList *list)
{
    iterator->list = list;
    iterator->next = (void **)list;
    iterator->link_offset = list->link_offset;
    iterator->previous = D_0036AE94;
    D_0036AE94 = iterator;
}
static inline void *NextIterator(struct GameUpdateIterator *iterator)
{
    void *object = *iterator->next;
    // Flat32-bit addresses reproduce the original ADDU even at the terminating
    // null head; no C pointer arithmetic is applied to a null pointer.
    iterator->next = (void **)((unsigned int)object + iterator->link_offset);
    return object;
}

void func_0027D7E8(struct GameUpdateView *game)
{
    func_0015DE78(game);
    func_0015B0E8(game);
    func_0015B918(game);
    if (D_0036BB9C <= 0.0f) {
        func_0027DA70(game);
    } else {
        int index;
        struct GameUpdateLinkedObject *linked;
        struct GameUpdateIterator first, second, third;
        void *object;
        game->current_index = &index;
        for (index = 0; index < game->count; ++index) {
            struct GameUpdateEntry *entry = &game->entries[index];
            if (entry->flags & 2) {
                struct GameUpdateObject *receiver = entry->object;
                struct GameUpdateVirtualEntry *method = receiver->table + 18;
                ((void (*)(void *))method->call)((char *)receiver + method->delta);
            }
        }
        game->current_index = 0;
        for (linked = game->linked_objects; linked; linked = linked->next) {
            struct GameUpdateVirtualEntry *method = linked->table + 55;
            ((void (*)(void *))method->call)((char *)linked + method->delta);
        }
        BeginIterator(&first, &game->list4514);
        while ((object = NextIterator(&first)) != 0)
            func_00137900(object);
        BeginIterator(&second, &game->list480C);
        while ((object = NextIterator(&second)) != 0)
            func_00202D80(object);
        BeginIterator(&third, &game->list4784);
        while ((object = NextIterator(&third)) != 0)
            func_00173950(object);
        func_0015DE78(game);
        func_00242A58(game);
        func_001E8288();
        func_00235FF8();
        func_0015DE78(game);
        D_0036AE94 = first.previous;
    }
    func_001CF0D0(D_00375290);
    func_002848D0(D_004BC230);
    func_00247728(D_00474FF0);
    func_0027DE38(game);
    func_0025CB38(game);
    func_00129E20(D_0036B138);
}
