// SLY3_CFLAGS: -Os -G0
struct ContactObject;
struct ContactNode;
struct ContactVirtualEntry { short delta; short unused; void *method; };
struct ContactObject { char prefix[12]; struct ContactVirtualEntry *vtable; };
struct ContactPair { void *resource; struct ContactPair *next; struct ContactPair *other; struct ContactObject *object; };
struct ContactNode { char prefix[0x58]; struct ContactNode *next; int word5C; struct ContactObject *object; struct ContactPair *pairs; void *resource; int word6C; unsigned long flags; };
struct ContactBinding { char prefix[0xDC]; struct ContactNode *node; };
struct ContactGame { char prefix[0x44D0]; struct ContactNode *first; };
void func_001CBAA0(struct ContactGame *, void *);
void *func_001CDF20(struct ContactGame *, struct ContactNode *, struct ContactNode *);
void func_0023E228(struct ContactObject *);
void func_002BBFE8(void *, int);
#define CONTACT_CALL_PAIR(object, other) ((void (*)(void *, struct ContactObject *))(object)->vtable[58].method)((char *)(object) + (object)->vtable[58].delta, (other))
#define CONTACT_CALL_PREDICATE(object) ((int (*)(void *))(object)->vtable[66].method)((char *)(object) + (object)->vtable[66].delta)
void func_0013C9D0(struct ContactGame *game, int *count, struct ContactNode **output)
{
    char completion;
    int used = 0;
    struct ContactNode *node;
    for (node = game->first; node; node = node->next) {
        unsigned long flags = node->flags;
        struct ContactPair *pair;
        if (flags & 4)
            continue;
        flags |= 0x10;
        node->flags = flags;
        if (!(flags & 8)) {
            node->flags = flags | 8;
            output[used++] = node;
        }
        for (pair = node->pairs; pair; pair = pair->next) {
            struct ContactNode *other = ((struct ContactBinding *)pair->object)->node;
            unsigned long other_flags = other->flags;
            void *old_resource;
            if (other_flags & 0x10)
                continue;
            if (other_flags & 4)
                continue;
            if (!(other_flags & 8)) {
                other->flags = other_flags | 8;
                output[used++] = other;
            }
            CONTACT_CALL_PAIR(node->object, other->object);
            CONTACT_CALL_PAIR(other->object, node->object);
            old_resource = pair->resource;
            func_001CBAA0(game, old_resource);
            {
                void *new_resource = func_001CDF20(game, node, other);
                pair->resource = new_resource;
                pair->other->resource = new_resource;
            }
            if (old_resource || pair->resource) {
                if (!CONTACT_CALL_PREDICATE(node->object))
                    func_0023E228(node->object);
                if (!CONTACT_CALL_PREDICATE(other->object))
                    func_0023E228(other->object);
            }
        }
    }
    *count = used;
    func_002BBFE8(&completion, 2);
}
