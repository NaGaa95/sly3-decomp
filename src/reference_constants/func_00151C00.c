// Reference algorithm: src/hand/func_0013FA30.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; };
struct S { int f0; int f4; int f8; };
#include "owner_parent_link.h"
void func_00151B60(struct O *, int);
void func_00151C00(struct S *p, int c, struct O **apo) {
    int i;
    for (i = 0; i < c; i++) {
        struct O *po = apo[i];
        func_001C7A00(po, 0, 0);
        func_00151B60(po, p->f4);
        if (p->f8 != -1) ((void (*)(void *, int, int))po->vt[27].pfn)((char *)po + po->vt[27].d, p->f8, 1);
    }
}
