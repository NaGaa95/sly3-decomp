#include "heap_frame_api.h"
// Destroy the embedded record with its original flag and conditionally invoke the caller-derived object release stub.
// Reference algorithm: src/hand/func_001E1560.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_002BC4D8(void *p,int flags) {
    func_001D2798((char *)p+0x4,2);
    if(flags&1)func_001D2818(p);
}
