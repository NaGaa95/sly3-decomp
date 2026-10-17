// SLY3_CFLAGS: -Os -G0
struct KeyHolder { unsigned char prefix[4]; int key; };
struct ChainNode {
    unsigned char prefix[4];
    struct KeyHolder *holder;
    unsigned char gap8[0x24 - 8];
    struct ChainNode *next;
};
struct Method { short adjustment, word2; void *function; };
struct MethodTable { unsigned char prefix[0x18]; struct Method notify; };
struct Item {
    unsigned char prefix[4];
    int key;
    unsigned char gap8[0x18 - 8];
    struct MethodTable *methods;
};
struct Container {
    unsigned char prefix[0xD0];
    int count;
    struct Item **items;
};
struct LookupOwner {
    unsigned char prefix[0x10];
    struct Container *container;
    unsigned char gap14[0x6C - 0x14];
    struct ChainNode *chain;
};
void *func_00202C90(struct LookupOwner *owner, int key)
{
    struct ChainNode *node;
    int i;
    for (node = owner->chain; node; node = node->next) {
        if (node->holder->key == key)
            return node;
    }
    for (i = 0; i < owner->container->count; i++) {
        struct Item *item = owner->container->items[i];
        if (item->key == key) {
            struct Method *method = &item->methods->notify;
            return ((void *(*)(void *, void *))method->function)((char *)item + method->adjustment, owner);
        }
    }
    return 0;
}
