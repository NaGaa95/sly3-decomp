// Recompute two cached flag bits on every item of the list from its object's two predicates.
// SLY3_CFLAGS: -Os -G0
struct Item {
    void *object;
    unsigned char opaque04[0x18];
    unsigned flag0 : 1;
    unsigned flag1 : 1;
    unsigned flag2 : 1;
    unsigned flag3 : 29;
};
struct ItemList {
    unsigned char opaque00[0x5C];
    int count;
    struct Item *items;
};
int func_0021F350(void *object);
int func_0021F410(void *object);

void func_0021F5F8(struct ItemList *list)
{
    int i;
    for (i = 0; i < list->count; i++) {
        struct Item *item = &list->items[i];
        item->flag1 = func_0021F350(item->object);
        item->flag2 = func_0021F410(item->object);
    }
}
