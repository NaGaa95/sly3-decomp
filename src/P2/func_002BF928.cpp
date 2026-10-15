// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Same observed scalar shuffle algorithm as the maintained2BDE20 specialization.
#include "shuffle_array.h"
extern "C" {
#include "runtime_shuffle_access.h"

void func_002BF928(struct SHUFFLED_IDENTIFIERS *array, int count, const int *identifiers, void *heap)
{
    if (array->heap)
        ((HEAP *)array->heap)->Free(array->items);
    array->heap = heap;
    array->count = count;
    array->items = (int *)PvAllocCopy((HEAP *)heap, count * sizeof(int), (void *)identifiers, 4);
    array->cursor = 0;
    ShuffleArray(array->count, array->items);
}
}
