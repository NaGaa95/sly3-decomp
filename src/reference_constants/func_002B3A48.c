// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_managed_pool_extensions.h"

void func_002B3A48(struct S *storage, void *table)
{
    RuntimeManagedWideLinkedCell *cell = (RuntimeManagedWideLinkedCell *)storage;
    RuntimeManagedWideListHead *head = table;
    RuntimeManagedWideLinkedCell *previous;
    RuntimeManagedDecoderWord group, index, nextGroup, nextIndex;
    func_002B3930(storage, &group.whole, &index.whole);
    previous = head->first;
    if (previous) {
        previous->previousGroup = group.low16;
        previous->previousIndex = index.low16;
    }
    func_002B3930((struct S *)head->first, &nextGroup.whole, &nextIndex.whole);
    cell->nextGroup = nextGroup.low16;
    cell->nextIndex = nextIndex.low16;
    head->first = cell;
}
