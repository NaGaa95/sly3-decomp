// Recovered scene ownership, packed state reset and intrusive list attachment.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "bis.h"
#include "scene.h"
extern "C" void *D_00479AB4;
extern "C" SCENE_GLOBAL_LIST D_00475490;
extern "C" unsigned char D_0047904C[];
extern "C" SCENE_HANDLE *func_0011E118(void *);
extern "C" void func_0011AFC0(SCENE_LIST *,SCENE_OBJECT *,SCENE_OBJECT *);

extern "C" void func_001C7470(SCENE_OBJECT *object) {
    if(!object->handle) {
        object->handle=func_0011E118(D_0047904C);
        object->handle->object=object;
    }
}
extern "C" void func_001C7500(SCENE_OBJECT *owner,SCENE_LIST **list,SCENE_OBJECT ***anchor) {
    if(owner) {
        *list=&owner->children;
        *anchor=&owner->anchor;
    } else {
        *list=&D_00475490.list;
        *anchor=&D_00475490.anchor;
    }
}
extern "C" void func_001C7340(SCENE_OBJECT *object) {
    object->flags.fields.state44=15;
    object->flags.fields.state48=2;
    object->time34=1.0e10f;
    object->flags.fields.tag=255;
    if(object->owner) {
        object->handle=object->owner->handle;
        object->flags.fields.inherited=object->owner->flags.fields.inherited;
    } else {
        func_001C7470(object);
        object->flags.fields.inherited=1;
    }
    object->field3C=65;
    object->context=object->owner?object->owner->context:D_00479AB4;
    SCENE_LIST *list;SCENE_OBJECT **anchor;
    func_001C7500(object->owner,&list,&anchor);
    func_0011AFC0(list,*anchor,object);
}
extern "C" void func_001519C8(SCENE_OBJECT *,CBinaryInputStream *);
extern "C" void func_001C7D98(SCENE_OBJECT *object,CBinaryInputStream *stream) {
    func_001519C8(object,stream);
}
