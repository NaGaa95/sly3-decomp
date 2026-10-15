// Reference algorithm: src/hand/func_001F4BA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct T { char pad[0x70]; ulong fl; };
struct S { char pad[0xDC]; struct T *pt; };
struct DL;
extern struct DL D_00479944;
void func_0011B028(struct DL *, void *);
void func_0023DCF0(struct S *p)
{
    struct T *pt = p->pt;
    if (!pt) return;
    if (!(pt->fl & 1)) return;
    pt->fl &= ~1;
    func_0011B028(&D_00479944, p->pt);
}
