// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Shared observed Sly 3 layouts and coherent cohort helper declarations.
#include "runtime_geometry_access.h"

RuntimeGeometry *func_002BD548(RuntimeOwner *owner, int operation)
{
    if (operation == 1) {
        owner->writable = operation;
        if (owner->geometry->references >= 2) {
            struct MSG request;
            owner->geometry->references--;
            request.cb = 0x100;
            request.nKind = 0x10;
            owner->geometry = func_001D24D0(&request, owner->geometry);
            owner->geometry->references = operation;
        }
    }
    return owner->geometry;
}
