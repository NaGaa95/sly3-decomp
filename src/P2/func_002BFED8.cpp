// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "shuffle_array.h"
#include "runtime_shuffle_pair_access.h"

extern "C" void func_002BFED8(RuntimeShufflePairBag *array, int count,
                             const RuntimeShufflePair *items, void *heap)
{
    if (array->heap)
        ((HEAP *)array->heap)->Free(array->items);
    array->heap = heap;
    array->count = count;
    array->items = (RuntimeShufflePair *)PvAllocCopy((HEAP *)heap, count * sizeof(RuntimeShufflePair), (void *)items, 4);
    array->cursor = 0;
    ShuffleArray(array->count, array->items);
}
