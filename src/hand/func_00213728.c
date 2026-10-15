// Cycle through the path list in the requested direction until an allowed entry is found; clear the selection after a complete unsuccessful cycle.
// Reference algorithm: src/hand/func_001D77D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
#include "activation_selector_api.h"
typedef struct { char pad[0x40]; int c; } LIST;
typedef struct {
    char pad[0x194];
    LIST *plist;
    void *x188;
    char pad18c[0x220 - 0x18C];
    int c;
    int a[8];
} OBJ;
void func_00213728(OBJ *p, int d)
{
    int i0;
    int i;
    if (p->x188 == 0)
        return;
    i = func_00239AB8(p->plist, func_00239E70(p->x188));
    i0 = i;
    for (;;) {
        int identifier;
        int j;
        i += d;
        if (i < 0)
            i = p->plist->c - 1;
        else if (i >= p->plist->c)
            i = 0;
        identifier = func_00239B80(p->plist, i);
        for (j = 0; j < p->c; j++) {
            if (p->a[j] == identifier) {
                func_00239CE8(p->x188, identifier);
                return;
            }
        }
        if (d == 0)
            d = 1;
        else if (i == i0)
            break;
    }
    func_0023AAE8(0, p, -1, 0, &p->x188);
}
