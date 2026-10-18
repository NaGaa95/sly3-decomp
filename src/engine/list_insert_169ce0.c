// SLY3_CFLAGS: -Os -G0
struct ItemEntry { short delta, padding; void (*fn)(void *); };
struct ItemTable { struct ItemEntry entries[4]; };
struct ItemList;
struct Item { struct ItemList *list; int key; unsigned char gap8[4]; struct Item *next; unsigned char gap10[0x1C - 0x10]; struct ItemTable *table; };
struct ItemList { unsigned char prefix[0x300]; struct Item *head; };
void func_0011AFC0(struct Item **head, struct Item *before, struct Item *item);
void func_00169CE0(struct Item *self)
{
    struct ItemList *list = self->list;
    struct Item *oldHead = list->head;
    struct Item *cursor;
    for(cursor = oldHead; cursor && cursor->key >= self->key; cursor = cursor->next);
    func_0011AFC0(&list->head, cursor, self);
    if(self->list->head != oldHead) {
        if(oldHead) oldHead->table->entries[2].fn((char *)oldHead + oldHead->table->entries[2].delta);
        self->table->entries[1].fn((char *)self + self->table->entries[1].delta);
    }
}
