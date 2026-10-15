// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_removal_access.h"
extern unsigned char D_004D2BC8[];
extern int D_0036AE28, D_0036AE34, D_0036AE38;

static inline RuntimeManagedRemovalCell24 *ManagedCellFromLink(unsigned int group, unsigned int index)
{
    if (group == 0 && index == 0)
        return 0;
    return ((RuntimeManagedRemovalCell24 **)D_004D2BC8)[group] + index;
}

void func_002B4308(struct S *storage)
{
    RuntimeManagedRemovalCell24 *cell = (RuntimeManagedRemovalCell24 *)storage;
    RuntimeManagedRemovalCell24 *previous = ManagedCellFromLink(cell->links.halves.low16 & 15, (cell->links.whole >> 4) & 0x7ff);
    RuntimeManagedRemovalCell24 *next = ManagedCellFromLink((cell->links.whole >> 16) & 15, (cell->links.whole >> 20) & 0x7ff);
    if (cell == (RuntimeManagedRemovalCell24 *)D_0036AE34)
        D_0036AE34 = (int)next;
    if (previous) {
        previous->links.fields.nextGroup = cell->links.halves.high16 & 15;
        previous->links.fields.nextIndex = cell->links.fields.nextIndex;
    } else if (cell == (RuntimeManagedRemovalCell24 *)D_0036AE38) {
        D_0036AE38 = (int)next;
    } else if (cell == (RuntimeManagedRemovalCell24 *)D_0036AE28) {
        D_0036AE28 = (int)next;
    }
    if (next) {
        next->links.fields.previousGroup = cell->links.halves.low16 & 15;
        next->links.fields.previousIndex = cell->links.fields.previousIndex;
    }
}
