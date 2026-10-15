// Read the serialized factory identifier, create the selected object, bind its owner, and read the 36-byte initialization record for its virtual initializer.
// Reference algorithm: src/hand/func_001ED7A8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *, char *); };
struct O { int pad[3]; struct VTE *vt; char pad2[0x34 - 0x10]; void *p30; };
#include "factory_descriptor.h"
int func_00119048(void *pbis);
void func_00118DA0(void *pbis, int cb, char *buf);
struct O *func_00236EB0(void *pv, void *pbis)
{
    char buf[0x24];
    int i = func_00119048(pbis);
    struct O *p;
    if (i == -1) return 0;
    p = (D_003409E0 + i)->create();
    p->p30 = pv;
    func_00118DA0(pbis, 0x24, buf);
    p->vt[7].pfn((char *)p + p->vt[7].d, buf);
    return p;
}
