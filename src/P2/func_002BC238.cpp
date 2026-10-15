// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "shuffle_array.h"
extern "C" {
#include "runtime_shuffle_access.h"

int func_002BC238(struct SHUFFLED_IDENTIFIERS *array)
{
    if (array->cursor == array->count) {
        ShuffleArray(array->count, array->items);
        array->cursor = 0;
    }
    return array->items[array->cursor++];
}
}
