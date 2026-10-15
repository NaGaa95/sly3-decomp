// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_geometry_property_access.h"
extern RuntimeGeometryVector4 D_00321300;
extern float D_00321310;

void func_002BD1F0(RuntimeOwner *owner, int kind)
{
    RuntimeGeometryValueRecord *record = func_002BCCF0(owner, 1);
    if (record->kind == kind)
        return;
    if (owner->geometry->record.value.kind != 0)
        return;
    record->kind = kind;
    switch (kind) {
    case 2: record->value.vector = D_00321300; break;
    case 1: record->value.scalar = D_00321310; break;
    }
}
