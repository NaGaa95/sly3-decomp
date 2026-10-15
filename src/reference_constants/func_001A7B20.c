// Original axis configuration record and actual pointer return.
// Complete consumer 1A7B38 proves the four fields in input_axis_config.h.
// SLY3_CFLAGS: -Os -G0
#include "input_axis_config.h"

struct INPUT_AXIS_CONFIG *func_001A7B20(int index)
{
    return D_00345098 + index;
}
