// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Shared observed Sly 3 layouts and coherent cohort helper declarations.
#include "runtime_geometry_access.h"

void *func_002BD7E8(RuntimeOwner *owner, int operation)
{
    RuntimeGeometry *geometry = func_002BD548(owner, operation);
    if (operation == 1 && geometry->matrix_kind == -1) {
        geometry->matrix_kind = operation;
        geometry->record.whole_matrix = D_00321380;
    }
    if (geometry->matrix_kind != 1)
        return D_0036BEC0;
    return &geometry->record.whole_matrix;
}
