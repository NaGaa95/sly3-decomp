// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_removal_access.h"
extern unsigned char D_004D2CA0[];
extern int D_0036AE3C, D_0036AE48, D_0036AE4C;

static inline RuntimeManagedRemovalCell28 *ManagedCellFromLink(unsigned int group, unsigned int index)
{
    if (group == 0 && index == 0)
        return 0;
    return ((RuntimeManagedRemovalCell28 **)D_004D2CA0)[group] + index;
}

void func_002B46C8(struct S *storage)
{
    RuntimeManagedRemovalCell28 *cell = (RuntimeManagedRemovalCell28 *)storage;
    RuntimeManagedRemovalCell28 *previous = ManagedCellFromLink(cell->links.halves.low16 & 15, (cell->links.whole >> 4) & 0x7ff);
    RuntimeManagedRemovalCell28 *next = ManagedCellFromLink((cell->links.whole >> 16) & 15, (cell->links.whole >> 20) & 0x7ff);
    if (cell == (RuntimeManagedRemovalCell28 *)D_0036AE48)
        D_0036AE48 = (int)next;
    if (previous) {
        previous->links.fields.nextGroup = cell->links.halves.high16 & 15;
        previous->links.fields.nextIndex = cell->links.fields.nextIndex;
    } else if (cell == (RuntimeManagedRemovalCell28 *)D_0036AE4C) {
        D_0036AE4C = (int)next;
    } else if (cell == (RuntimeManagedRemovalCell28 *)D_0036AE3C) {
        D_0036AE3C = (int)next;
    }
    if (next) {
        next->links.fields.previousGroup = cell->links.halves.low16 & 15;
        next->links.fields.previousIndex = cell->links.fields.previousIndex;
    }
}
