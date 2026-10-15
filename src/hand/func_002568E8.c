// Cancel the previous handle and clear its owner, then register the new attachment with the revised event mode and store the scalar and quadword state.
// Reference algorithm: src/hand/func_0020AC28.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
typedef int qword __attribute__((mode(TI)));
extern qword D_00317560;
struct A { char pad[0x90]; void *channel; };
struct S { char pad[0x1084]; struct A *pa; void *task; void *node; qword v; };
void func_002568E8(void *owner, void *parameter, void *node, qword v)
{
    struct S *p = owner;
    struct A *pa = parameter;
    if (p->pa) {
        func_001309D8(&p->task);
        p->task = 0;
        p->pa = 0;
    }
    p->pa = pa;
    if (pa && pa->channel) {
        p->task = func_00130078(p, pa->channel, 5, 9, 3, D_00317560);
        p->node = node;
        p->v = v;
    }
}
