// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Shared observed Sly 3 layouts and coherent cohort helper declarations.
#include "runtime_geometry_access.h"

void *func_002BCCF0(RuntimeOwner *owner, int operation)
{
    RuntimeGeometry *geometry = func_002BCAD8(owner, operation);
    if (operation == 1 && geometry->matrix_kind == -1) {
        geometry->matrix_kind = 0;
        geometry->record.whole_matrix = D_00321320;
    }
    if (geometry->matrix_kind != 0)
        return D_0036BEC0;
    return &geometry->record.whole_matrix;
}
