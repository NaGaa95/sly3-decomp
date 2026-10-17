// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
typedef int qword __attribute__((mode(TI)));
struct RayObject { char prefix[0xDC]; void *collision; };
extern "C" qword func_001C9428(SCENE_OBJECT *source,SCENE_OBJECT *destination,qword point);
extern "C" int func_00119BE8(void *collision,int limit,qword origin,qword direction,int mode,void *output);
extern "C" int func_0027F310(SCENE_OBJECT *object,qword origin,qword direction)
{
    qword hit[6];
    qword localOrigin=func_001C9428(0,object,origin);
    qword localDirection=func_001C9428(0,object,direction);
    return func_00119BE8(((RayObject *)object)->collision,0x7FFFFFFF,localOrigin,localDirection,1,hit)>0;
}
