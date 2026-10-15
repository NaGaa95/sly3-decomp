// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Find a handle-chain prefix and allocate the missing context records.
struct Context;
struct ContextList { struct Context *first, *last; int member_offset; };
struct Context {
    int handle;
    struct Context *parent;
    int query_key;
    struct Context *hash_next;
    void *object;
    struct Context *sibling_next;
    struct ContextList children;
    int reserved24;
};
struct AllocationRequest { int bytes, alignment; };
typedef char CheckContext[(sizeof(struct Context) == 40) ? 1 : -1];
typedef char CheckList[(sizeof(struct ContextList) == 12) ? 1 : -1];
typedef char CheckRequest[(sizeof(struct AllocationRequest) == 8) ? 1 : -1];
extern void *func_001D2538(struct AllocationRequest *);
extern void func_0011AD60(struct ContextList *, int);
extern void func_0011AD80(struct ContextList *, struct Context *);
extern int func_001FA5D0(int);
extern struct ContextList *func_0017DBE8(void *, int);
extern char D_00475480[];

struct Context *func_001FA640(struct Context *context, int remaining,
                             const int *handles)
{
    struct Context *node;
    struct Context *parent;
    struct Context *allocated;
    struct AllocationRequest request;
    int i;

find_prefix:
    for (node = context->children.first; node; node = node->sibling_next) {
        if (node->handle == *handles) {
            if (remaining == 1)
                return node;
            context = node;
            --remaining;
            ++handles;
            goto find_prefix;
        }
    }
    request.bytes = remaining * sizeof(struct Context);
    request.alignment = 16;
    allocated = (struct Context *)func_001D2538(&request);
    parent = context;
    for (i = 0; i < remaining; ++i) {
        node = &allocated[i];
        func_0011AD60(&node->children, 0x14);
        node->handle = *handles++;
        node->query_key = func_001FA5D0(node->handle);
        func_0011AD80(func_0017DBE8(D_00475480, node->query_key), node);
        node->parent = parent;
        func_0011AD80(&parent->children, node);
        parent = node;
    }
    return node;
}
