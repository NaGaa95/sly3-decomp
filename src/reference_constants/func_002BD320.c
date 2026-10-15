// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_geometry_property_access.h"

void *func_002BD320(RuntimeOwner *owner, int operation)
{
    RuntimeGeometryValueRecord *record;
    if (operation == 1) {
        func_002BD1F0(owner, 1);
        record = &owner->geometry->record.value;
    } else {
        record = func_002BCCF0(owner, operation);
    }
    if (record->kind != 1)
        return D_0036BEF0;
    return (unsigned char *)record + 0x30;
}
