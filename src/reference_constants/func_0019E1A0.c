#include "state_transition_api.h"
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *, int, int, int, int, int); };
struct S { char pad[0xC]; struct VTE *vt; char p2[0x1E8]; void *x1c8; };

void func_0019E1A0(struct S *p)
{
    struct VTE *e;
    func_0019C570((struct StateTransitionOwner *)p->x1c8, 1);
    p->x1c8 = 0;
    e = &p->vt[3];
    e->pfn((char *)p + e->d, 6, 0, 0, 0, 0);
}
