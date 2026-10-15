// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Shared observed Sly 3 layouts and coherent cohort helper declarations.
#include "runtime_geometry_access.h"

void *func_002BDD90(RuntimeOwner *owner, int operation)
{
    RuntimeGeometryValueRecord *record;
    if (operation == 1) {
        func_002BDC60(owner, 1);
        record = &owner->geometry->record.value;
    } else {
        record = func_002BD760(owner, operation);
    }
    if (record->kind != 1)
        return D_0036BEF0;
    return (unsigned char *)record + 0x30;
}
