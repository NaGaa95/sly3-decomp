// SLY3_CFLAGS: -Os -G0
struct ContactNode;
struct ContactVirtualEntry { short delta; short unused; void *method; };
struct ContactObject { char prefix[12]; struct ContactVirtualEntry *vtable; };
struct ContactNode { char prefix[0x58]; struct ContactNode *next; struct ContactNode *previous; struct ContactObject *object; char unused64[4]; void *resource; int word6C; unsigned long flags; };
struct ContactList { struct ContactNode *first; struct ContactNode *last; int link_offset; };
struct ContactGame { char prefix[0x44D0]; struct ContactList pending; };
void func_001CBAA0(struct ContactGame *, void *);
void func_0011B028(void *, void *);
#define CONTACT_CALL_PAIR(object, other) ((void (*)(void *, struct ContactObject *))(object)->vtable[58].method)((char *)(object) + (object)->vtable[58].delta, (other))
#define CONTACT_CALL_VOID(object, slot) ((void (*)(void *))(object)->vtable[slot].method)((char *)(object) + (object)->vtable[slot].delta)
void func_0013CBD8(struct ContactGame *game)
{
    struct ContactNode *node;
    for (node = game->pending.first; node; node = game->pending.first) {
        node->flags &= ~0x10UL;
        CONTACT_CALL_PAIR(node->object, 0);
        func_001CBAA0(game, node->resource);
        node->resource = 0;
        CONTACT_CALL_VOID(node->object, 62);
        node->flags &= ~2UL;
        func_0011B028(&game->pending, node);
    }
}
void func_0013CC90(struct ContactGame *unused_game, int count, struct ContactNode **output)
{
    int index;
    for (index = 0; index < count; ++index) {
        struct ContactNode *node = output[index];
        node->flags &= ~8UL;
        CONTACT_CALL_VOID(node->object, 61);
    }
}
