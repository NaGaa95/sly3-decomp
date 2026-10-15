// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_shuffle_access.h"
extern char D_00352B58[];

struct SHUFFLED_IDENTIFIERS *func_002BC1C8(void *storage, int count, const int *identifiers, void *heap)
{
    struct SHUFFLED_IDENTIFIERS *object = storage;
    func_002BC090((struct S *)object);
    object->vtable = D_00352B58;
    object->heap = 0;
    func_002BC0A8(object, count, identifiers, heap);
    return object;
}
