// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "state_position_ops.h"
struct BSP_NODE;
struct VolumeView { char prefix[0xDC]; BSP_NODE *volume; char gapE0[0x20]; qword center; float radius; int active; };
extern "C" BSP_NODE *func_00119C90(BSP_NODE *node, unsigned int limit, qword point);
static inline float SquaredLength(qword difference)
{
    qword one;
    float result;
    asm("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "+j"(difference), "=&j"(one));
    asm("mtc1 %1,%0" : "=f"(result) : "r"(difference));
    return result;
}
extern "C" int func_0027F298(VolumeView *view, qword point)
{
    int outside = view->radius < SquaredLength(PackedDifference(point, view->center));
    if (outside)
        return view->active;
    return func_00119C90(view->volume, 0x7FFFFFFF, point) != 0;
}
