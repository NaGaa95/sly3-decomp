// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "particle_lifecycle_api.h"
struct PropertyOps {
    unsigned char entry0[8];
    short refresh_adjustment, refresh_reserved;
    void (*refresh)(void *, int);
    unsigned char entry2[8];
    short poll_adjustment, poll_reserved;
    int (*poll)(void *);
    unsigned char entry4[8];
    short dispose_adjustment, dispose_reserved;
    void (*dispose)(void *);
};
struct Sampling {
    int resource_key;
    unsigned char to_kind[0x48 - 4];
    int kind;
    unsigned char to_changed[0x52 - 0x4C];
    unsigned short changed;
};
struct Timing {
    unsigned char prefix[0x82];
    unsigned short changed;
};
struct Definition {
    unsigned char prefix[0x10];
    struct Sampling *sampling;
    struct Timing *timing;
};
struct Owner {
    unsigned char prefix[0x10];
    void *lookup_owner;
};
struct PropertyView {
    struct Owner *owner;
    struct Definition *definition;
    void *resource;
    unsigned char to_ops[0x40 - 12];
    struct PropertyOps *ops;
};
extern unsigned char D_00475480[];
void *func_0017E1B8(void *, int, int, void *);
int func_001FF100(struct Property *);

void func_001FEF60(struct Property *property, int flags)
{
    struct PropertyView *p = (struct PropertyView *)property;
    int advanced = 0;
    int pending;
    p->ops->refresh((char *)property + p->ops->refresh_adjustment, 1);
    if (flags & 1)
        advanced = func_001FF100(property);
    pending = p->ops->poll((char *)property + p->ops->poll_adjustment);
    if (!advanced && !pending && (flags & 2))
        p->ops->dispose((char *)property + p->ops->dispose_adjustment);
}

void func_001FF010(struct Property *property, int changed_only)
{
    struct PropertyView *p = (struct PropertyView *)property;
    if (!changed_only || p->definition->sampling->changed) {
        struct Sampling *sampling = p->definition->sampling;
        void *owner = p->owner->lookup_owner;
        if (sampling->kind == 2)
            p->resource = func_0017E1B8(D_00475480, 4,
                                      sampling->resource_key, owner);
        p->definition->sampling->changed = 0;
    }
    p->definition->timing->changed = 0;
}
