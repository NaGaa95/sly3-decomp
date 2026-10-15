// Extract the first two coefficients from each of the three matrix rows.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "matrix_xy_resource_api.h"
void func_00262708(void *receiver, const struct MatrixXYSource *matrix) {
    struct MatrixXYValue compact;
    struct MatrixXYSource copy = *matrix;
    compact.value[0] = copy.row[0].value[0];
    compact.value[1] = copy.row[0].value[1];
    compact.value[2] = copy.row[1].value[0];
    compact.value[3] = copy.row[1].value[1];
    compact.value[4] = copy.row[2].value[0];
    compact.value[5] = copy.row[2].value[1];
    func_00262848(receiver, &compact);
}
