// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "heap.h"
extern "C" {
#include "runtime_shuffle_access.h"
extern char D_0036A878[];
void func_001D2818(void *storage);

void func_002BFE68(void *storage, int flags)
{
    struct SHUFFLED_IDENTIFIERS *array = (struct SHUFFLED_IDENTIFIERS *)storage;
    array->vtable = D_0036A878;
    if (array->heap)
        ((HEAP *)array->heap)->Free(array->items);
    if (flags & 1)
        func_001D2818(array);
}
}
