// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x40]; void * owner; };
#include "animation_ensure_api.h"
void func_002591B0(struct S *object,void *first,int flags,void **output)
{
    if(object->owner)func_00136908((struct ASEG *)object->owner,(struct ALO *)first,0.0f,1.0f,flags,(struct ASEGA **)output);
}
