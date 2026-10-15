// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_removal_access.h"
extern unsigned char D_004D2A18[];
extern int D_0036AE00, D_0036AE0C, D_0036AE10;

static inline RuntimeManagedRemovalCell16 *ManagedCellFromLink(unsigned int group, unsigned int index)
{
    if (group == 0 && index == 0)
        return 0;
    return ((RuntimeManagedRemovalCell16 **)D_004D2A18)[group] + index;
}

void func_002B3B90(struct S *storage)
{
    RuntimeManagedRemovalCell16 *cell = (RuntimeManagedRemovalCell16 *)storage;
    RuntimeManagedRemovalCell16 *previous = ManagedCellFromLink(cell->links.halves.low16 & 15, (cell->links.whole >> 4) & 0x7ff);
    RuntimeManagedRemovalCell16 *next = ManagedCellFromLink((cell->links.whole >> 16) & 15, (cell->links.whole >> 20) & 0x7ff);
    if (cell == (RuntimeManagedRemovalCell16 *)D_0036AE0C)
        D_0036AE0C = (int)next;
    if (previous) {
        previous->links.fields.nextGroup = cell->links.halves.high16 & 15;
        previous->links.fields.nextIndex = cell->links.fields.nextIndex;
    } else if (cell == (RuntimeManagedRemovalCell16 *)D_0036AE10) {
        D_0036AE10 = (int)next;
    } else if (cell == (RuntimeManagedRemovalCell16 *)D_0036AE00) {
        D_0036AE00 = (int)next;
    }
    if (next) {
        next->links.fields.previousGroup = cell->links.halves.low16 & 15;
        next->links.fields.previousIndex = cell->links.fields.previousIndex;
    }
}
