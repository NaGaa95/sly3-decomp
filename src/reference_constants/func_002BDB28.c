// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Shared observed Sly 3 layouts and coherent cohort helper declarations.
#include "runtime_geometry_access.h"

void *func_002BDB28(RuntimeOwner *owner, int operation)
{
    RuntimeGeometryPropertyRecord *record;
    if (operation == 1) {
        func_002BDA38(owner, 1);
        record = &owner->geometry->record.property;
    } else {
        record = func_002BD7E8(owner, operation);
    }
    if (record->kind != 1)
        return D_0036BEC0;
    return (unsigned char *)record + 0;
}
