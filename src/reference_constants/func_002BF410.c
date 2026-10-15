// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "state_emitter_shared.h"

struct RuntimeRetainedResourceView {
    unsigned char prefix[12];
    struct VirtualEntry *table;
};
struct RuntimeResourceArrayOwnerView {
    unsigned char opaque00[0x210];
    struct RuntimeRetainedResourceView *head;
    unsigned char opaque214[4];
    struct RuntimeRetainedResourceView *resources[8];
    struct RuntimeRetainedResourceView *tail;
};
typedef char RuntimeResourceArrayBegin218[(unsigned int)&((struct RuntimeResourceArrayOwnerView *)0)->resources == 0x218 ? 1 : -1];
typedef char RuntimeResourceArrayTail238[(unsigned int)&((struct RuntimeResourceArrayOwnerView *)0)->tail == 0x238 ? 1 : -1];
void func_002BC7F0(void *storage, int flags);

static inline void ReleaseResource(struct RuntimeRetainedResourceView *resource)
{
    if (resource) {
        struct VirtualEntry *table = resource->table;
        table[2].call((unsigned char *)resource + table[2].delta);
    }
}

static inline void ReleaseResourceRange(struct RuntimeRetainedResourceView **first,
                                        struct RuntimeRetainedResourceView **end)
{
    if (first)
        while (first != end)
            ReleaseResource(*--end);
}

void func_002BF410(void *storage, int flags)
{
    struct RuntimeResourceArrayOwnerView *owner = storage;
    struct RuntimeRetainedResourceView **end = &owner->tail;
    ReleaseResource(*end);
    ReleaseResourceRange(owner->resources, end);
    ReleaseResource(owner->head);
    func_002BC7F0(owner, flags);
}
