// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// The ordinary switch order follows the Sly 2 vector/scalar source order.
#include "runtime_geometry_access.h"
extern RuntimeGeometryVector4 D_00321300;
extern float D_00321310;

void func_002BDC60(RuntimeOwner *owner, int kind)
{
    RuntimeGeometryValueRecord *record = func_002BD760(owner, 1);
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
