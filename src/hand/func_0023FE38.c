// Clear flag 0x1000 on matching entries and bit 50 on each attached resource.
// Reference algorithm: src/hand/func_001F6978.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct Q { char pad[0x10]; ulong fl; };
struct E { int k; int pad[2]; int fl; int pad2[5]; struct Q *pq; };
struct P { char pad[0xA8]; int c; int pad2; struct E *ae; };
void func_0023FE38(struct P *p, int k)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (pe->k == k) {
            pe->fl &= ~0x1000;
            if (pe->pq) pe->pq->fl &= ~(1L << 50);
        }
    }
}
