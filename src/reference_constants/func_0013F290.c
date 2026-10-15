// Reference algorithm: src/hand/func_00189488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1520]; int n; };
#include "actor_input_query.h"
int func_0013F290(struct S *p)
{
    int r = func_001530F8(p);
    if (r != -1) return r;
    switch (p->n) {
    case 1: case 5: case 6: case 7: case 15:
        return 1;
    }
    return -1;
}
