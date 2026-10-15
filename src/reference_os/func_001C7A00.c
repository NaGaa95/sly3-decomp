// Sly 2 reference: src/hand/func_001A58D0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
#include "owner_parent_link.h"
struct VTE { short d; short pad; OwnerParentCallback pfn; };
struct O { char pad[0xC]; struct VTE *vt; };
void func_001C7A00(void *receiver, void *parent, int flags)
{
    struct O *p = receiver;
    struct VTE *e = &p->vt[10];
    e->pfn((char *)p + e->d, parent, 0, flags);
}
