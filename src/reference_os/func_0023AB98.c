// Sly 2 reference: src/hand/func_001F14F8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
#include "activation_retained_api.h"
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[3]; };
struct X { char pad[0xC]; struct VT *pvt; };
void func_00239C20(struct X *);

void func_0023AB98(void *pv, void *receiver, int b, int c, int d, void **output)
{
    struct X **ppx = (struct X **)output;
    if (*ppx) {
        func_00239C20(*ppx);
        (*ppx)->pvt->a[2].pfn((char *)*ppx + (*ppx)->pvt->a[2].d);
        *ppx = 0;
    }
    if (pv) {
        struct X *px = func_002399F0(pv, receiver, b, c, d);
        *ppx = px;
        px->pvt->a[1].pfn((char *)px + px->pvt->a[1].d);
    }
}
