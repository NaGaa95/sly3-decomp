// Reference algorithm: src/hand/func_001B5038.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x134]; void *p150; char pad2[0xF60 - 0x138]; int f00; int f04; char pad3[0xF78 - 0xF68]; int f20; };
int func_00156998(struct S *p);
#include "input_query_api.h"
void func_001BDB50(void *p);
void func_001BE220(void *p);
void func_001F0268(struct S *p)
{
    if (func_00156998(p)) {
        if (p->f04 == 1 && !p->f20 && func_001A7A80(p->p150, 0x4F0, 0.25f)) func_001BDB50(&p->f00);
        func_001BE220(&p->f00);
    }
}
