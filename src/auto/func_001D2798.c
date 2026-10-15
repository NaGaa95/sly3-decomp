// Heap-frame destructor: pop global mark, then honor the real delete bit.
#include "heap_frame_api.h"
void func_001D2720(void);
void func_001D2798(void *receiver, int flags) {
    func_001D2720();
    if (flags & 1) {
        func_001D2818(receiver);
    }
}
