// Recovered detached-object attachment and scene activation notifications.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" unsigned char D_00475480[];
extern "C" int func_001C8610(SCENE_OBJECT *);
extern "C" void func_001C7500(SCENE_OBJECT *,SCENE_LIST **,SCENE_OBJECT ***);
extern "C" void func_0011B028(SCENE_LIST *,void *);
extern "C" void func_0011AFC0(SCENE_LIST *,SCENE_OBJECT *,SCENE_OBJECT *);
extern "C" void func_0015ADA0(void *,SCENE_HANDLE *);
extern "C" void func_0015B420(void *,SCENE_OBJECT *);
extern "C" void func_0015B6B0(void *,void *);
extern "C" void func_001C7530(SCENE_OBJECT *object) {
    if(object->flags.fields.detached) {
        object->flags.fields.detached=0;
        SCENE_LIST *list;SCENE_OBJECT **anchor;
        func_001C7500(object->owner,&list,&anchor);
        if(object==*anchor)*anchor=object->previous;
        else {
            func_0011B028(list,object);
            func_0011AFC0(list,*anchor,object);
        }
        if(object->owner) {
            int inherited=object->owner->flags.fields.inherited;
            if(!inherited)goto registerOwner;
        }
        CallScene(object,11);
registerOwner:
        if(!object->owner) {
            int state=object->flags.fields.state48;
            if(state!=2)func_0015ADA0(D_00475480,object->handle);
        }
        SCENE_OBJECT **children;
        int count=SceneChildren(object,&children);
        for(int i=0;i<count;i++)CallScene(children[i],8);
        if(func_001C8610(object))CallScene(object,25);
        else if(!object->owner)func_0015B420(D_00475480,object);
    }
}
extern "C" void func_001C78A0(SCENE_OBJECT *object) {
    object->flags.fields.inherited=1;
    void *value=SceneQuery(object);
    if(value)func_0015B6B0(D_00475480,value);
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[4];
    entry->Message((char *)object+entry->delta,0,object);
}
