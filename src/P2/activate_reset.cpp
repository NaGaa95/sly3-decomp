// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct ActiveView { unsigned char prefix[0x190]; int active; };
extern "C" int func_001C8610(SCENE_OBJECT *object);
extern "C" void func_001C7A00(SCENE_OBJECT *object,int a,int b);
extern "C" void func_00286B00(SCENE_OBJECT *object,int mode);
extern "C" void func_002857D0(SCENE_OBJECT *object)
{
    if(((ActiveView *)object)->active==-1)
        return;
    int inherited=object->flags.fields.inherited;
    if(inherited && func_001C8610(object))
        return;
    func_001C7A00(object,0,0x1F);
    func_00286B00(object,3);
}
