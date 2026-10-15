// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "state_emitter_shared.h"

struct RuntimeRetainedResourceView {
    unsigned char prefix[12];
    struct VirtualEntry *table;
};

struct RuntimeResourceOwnerView {
    unsigned char prefix[12];
    struct RuntimeRetainedResourceView *resource;
};

void func_001D2818(void *storage);

void func_002BEB58(void *storage, int flags)
{
    struct RuntimeResourceOwnerView *owner = (struct RuntimeResourceOwnerView *)storage;
    struct RuntimeRetainedResourceView *resource = owner->resource;
    if (resource) {
        struct VirtualEntry *table = resource->table;
        table[2].call((unsigned char *)resource + table[2].delta);
    }
    if (flags & 1)
        func_001D2818(owner);
}
