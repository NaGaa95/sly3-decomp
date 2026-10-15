// Clear the active object only when its byte type and signed selection state permit it.
// Reference algorithm: src/hand/func_001E1D48.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct O {
    unsigned char n0;
    char pad[7];
    int n10;
};
struct S {
    char pad[0x48];
    struct O *po;
};
int func_00229438(struct S *p, struct O *po);
#include "script_actor_binding_api.h"
void func_00226700(struct S *p) {
    if (p->po && func_00229438(p, p->po)) {
        int f = 1;
        if (p->po->n0 == 0x29) f = (p->po->n10 == -1);
        if (f) func_0022B028(p, 0, 0);
    }
}
