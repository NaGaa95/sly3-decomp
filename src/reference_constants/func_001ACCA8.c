// Reference algorithm: src/hand/func_0018B2C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x134]; void *p150; char p1[0xE28]; int xf00; int xf04; char p2[0x10]; int xf20; char p3[0xDD4]; int x1d40; };
int func_00156998(struct S *p);
#include "input_query_api.h"
void func_001BDB50(void *p);
void func_001BE220(void *p);
void func_001ACCA8(struct S *p)
{
    if (func_00156998(p)) {
        if (p->xf04 == 1 && !p->xf20 &&
            func_001A7A80(p->p150, p->x1d40 == 7 ? 0x410 : 0x4F0, 0.25f))
            func_001BDB50(&p->xf00);
        func_001BE220(&p->xf00);
    }
}
