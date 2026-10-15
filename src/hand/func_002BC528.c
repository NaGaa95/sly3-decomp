#include "heap_frame_api.h"
// Construct the inherited object, install its derived vtable, initialize the embedded record, and return the receiver.
// Reference algorithm: src/hand/func_001DFFE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00350E40[];
struct S {
    void * vtable;
};
struct S *func_002B89B8(struct S *object);
struct S *func_002BC528(struct S *object) {
    func_002B89B8(object);
    object->vtable=D_00350E40;
    func_001D2770((char *)object+0x4);
    return object;
}
