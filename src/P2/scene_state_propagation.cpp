// Mark scene state locally, through owners, or through dependent children.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" unsigned char D_00475480[];
extern "C" void func_0015ADA0(void *,SCENE_HANDLE *);
extern "C" void func_0015B6B0(void *,void *);
inline unsigned char &SceneStateByte(SCENE_OBJECT *object) {
    return ((unsigned char *)&object->flags)[4];
}
extern "C" void func_001C9198(SCENE_OBJECT *object,int state) {
    int handleInherited=object->handle->object->flags.fields.inherited;
    if(handleInherited)func_0015ADA0(D_00475480,object->handle);
    int inherited=object->flags.fields.inherited;
    if(inherited) {
        void *value=SceneQuery(object);
        if(value)func_0015B6B0(D_00475480,value);
    }
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[50];
    ((void (*)(void *,int))entry->Simple)((char *)object+entry->delta,state);
    for(SCENE_OBJECT *owner=object->owner;owner;owner=owner->owner)
        SceneStateByte(owner)|=state;
}
extern "C" void func_001C9288(SCENE_OBJECT *object,int state) {
    SceneStateByte(object)=state;
}
extern "C" void func_001C9290(SCENE_OBJECT *object,int state) {
    SceneStateByte(object)=state;
    for(SCENE_OBJECT *child=object->children.first;child;child=child->previous)
        if(!child->flags.fields.unknown54)func_001C9198(child,state);
}
extern "C" void func_001C92F8(SCENE_OBJECT *object,int independent) {
    object->flags.fields.unknown54=independent&1;
}
extern "C" unsigned int func_001C9330(SCENE_OBJECT *object) {
    return object->flags.fields.unknown54;
}
