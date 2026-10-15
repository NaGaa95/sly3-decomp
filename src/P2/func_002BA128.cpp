// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "heap.h"
struct RuntimePointerArrayMethodEntry {
    short adjustment;
    short control;
    void *function;
};
struct RuntimePointerArrayMethodOwner {
    unsigned char opaque00[12];
    RuntimePointerArrayMethodEntry *methods;
    CDynArray array;
};
typedef char RuntimePointerArrayMethodEntrySize8[sizeof(RuntimePointerArrayMethodEntry) == 8 ? 1 : -1];
typedef char RuntimePointerArrayMethodArray16[(unsigned int)&((RuntimePointerArrayMethodOwner *)0)->array == 16 ? 1 : -1];

extern "C" int *func_002BA128(RuntimePointerArrayMethodOwner *owner, void *source)
{
    CDynArray *array = &owner->array;
    array->Append(source, 1);
    ((void (*)(void *, int *))owner->methods[6].function)(
        (char *)owner + owner->methods[6].adjustment,
        (int *)array->m_pv + (array->m_c - 1));
    return (int *)array->m_pv + (array->m_c - 1);
}
