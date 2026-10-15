// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "runtime_geometry_property_access.h"
extern RuntimeGeometryVector2 D_00321360;
extern int D_00321368;
extern RuntimeGeometryVector3 D_00321370;

void func_002BCFC8(RuntimeOwner *owner, int kind)
{
    RuntimeGeometryPropertyRecord *record = func_002BCD78(owner, 1);
    if (record->kind == kind)
        return;
    if (record->kind != -1)
        return;
    record->kind = kind;
    switch (kind) {
    case 1: record->value.pair = D_00321360; break;
    case 2: record->value.scalar = D_00321368; break;
    case 7: record->value.triple = D_00321370; break;
    }
}
