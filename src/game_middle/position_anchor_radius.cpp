// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"

extern "C" qword func_00250600(void *);
extern "C" qword func_001EE788(void *, qword);

extern "C" int func_001EE878(void *anchor, void *object, float radius)
{
    qword point = func_00250600(object);
    qword position = func_001EE788(anchor, point);
    return PackedHorizontalLength(PackedDifference(point, position)) <= radius;
}
