// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_removal_access.h"
extern unsigned char D_004D2D78[];
extern int D_0036AE50, D_0036AE5C, D_0036AE60;

static inline RuntimeManagedRemovalCell12 *ManagedCellFromLink(unsigned int group, unsigned int index)
{
    if (group == 0 && index == 0)
        return 0;
    return ((RuntimeManagedRemovalCell12 **)D_004D2D78)[group] + index;
}

void func_002B4A88(struct S *storage)
{
    RuntimeManagedRemovalCell12 *cell = (RuntimeManagedRemovalCell12 *)storage;
    RuntimeManagedRemovalCell12 *previous = ManagedCellFromLink(cell->links.halves.low16 & 15, (cell->links.whole >> 4) & 0x7ff);
    RuntimeManagedRemovalCell12 *next = ManagedCellFromLink((cell->links.whole >> 16) & 15, (cell->links.whole >> 20) & 0x7ff);
    if (cell == (RuntimeManagedRemovalCell12 *)D_0036AE5C)
        D_0036AE5C = (int)next;
    if (previous) {
        previous->links.fields.nextGroup = cell->links.halves.high16 & 15;
        previous->links.fields.nextIndex = cell->links.fields.nextIndex;
    } else if (cell == (RuntimeManagedRemovalCell12 *)D_0036AE60) {
        D_0036AE60 = (int)next;
    } else if (cell == (RuntimeManagedRemovalCell12 *)D_0036AE50) {
        D_0036AE50 = (int)next;
    }
    if (next) {
        next->links.fields.previousGroup = cell->links.halves.low16 & 15;
        next->links.fields.previousIndex = cell->links.fields.previousIndex;
    }
}
