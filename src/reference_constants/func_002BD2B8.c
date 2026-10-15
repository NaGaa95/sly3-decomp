// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_geometry_property_access.h"

void *func_002BD2B8(RuntimeOwner *owner, int operation)
{
    RuntimeGeometryValueRecord *record;
    if (operation == 1) {
        func_002BD1F0(owner, 2);
        record = &owner->geometry->record.value;
    } else {
        record = func_002BCCF0(owner, operation);
    }
    if (record->kind != 2)
        return D_0036BEF0;
    return (unsigned char *)record + 0x30;
}
