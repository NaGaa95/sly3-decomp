// Heap-frame constructor: preserve actual pointer identity around mark push.
#include "heap_frame_api.h"
void func_001D26D0(void);
void *func_001D2770(void *receiver) {
    func_001D26D0();
    return receiver;
}
