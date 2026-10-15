// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_geometry_property_access.h"

void *func_002BD120(RuntimeOwner *owner, int operation)
{
    RuntimeGeometryPropertyRecord *record;
    if (operation == 1) {
        func_002BCFC8(owner, 2);
        record = &owner->geometry->record.property;
    } else {
        record = func_002BCD78(owner, operation);
    }
    if (record->kind != 2)
        return D_0036BEC0;
    return (unsigned char *)record + 0;
}
