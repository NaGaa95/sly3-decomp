// Recovered intrusive scene hierarchy detachment, reparenting and notification.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" unsigned char D_00475480[];
extern "C" SCENE_LIST D_00479278;
extern "C" int func_001C8610(SCENE_OBJECT *);
extern "C" void func_001C7500(SCENE_OBJECT *,SCENE_LIST **,SCENE_OBJECT ***);
extern "C" void func_001C7470(SCENE_OBJECT *);
extern "C" void func_001C74B0(SCENE_OBJECT *);
extern "C" void func_0011B028(SCENE_LIST *,void *);
extern "C" void func_0011AF60(SCENE_LIST *,SCENE_OBJECT *);
extern "C" void func_0011AFC0(SCENE_LIST *,SCENE_OBJECT *,SCENE_OBJECT *);
extern "C" void func_0015AD18(void *,SCENE_HANDLE *);
extern "C" void func_0015ADA0(void *,SCENE_HANDLE *);
extern "C" void func_0015B420(void *,SCENE_OBJECT *);
extern "C" void func_001C1128(void *,SCENE_OBJECT *,int);
extern "C" void func_0015B640(void *,void *);
extern "C" void func_001C76F0(SCENE_OBJECT *object) {
    if(!object->flags.fields.detached) {
        if(func_001C8610(object))CallScene(object,24);
        if(!object->owner)func_0015AD18(D_00475480,object->handle);
        int inherited=object->flags.fields.inherited;
        SCENE_LIST *list;SCENE_OBJECT **anchor;
        func_001C7500(object->owner,&list,&anchor);
        func_0011B028(list,object);
        func_0011AF60(list,object);
        if(!*anchor)*anchor=object;
        object->flags.fields.detached=1;
        SCENE_OBJECT **children;
        int count=SceneChildren(object,&children);
        for(int i=0;i<count;i++)CallScene(children[i],9);
        if(inherited)CallScene(object,12);
    }
}
extern "C" void func_001C7938(SCENE_OBJECT *object) {
    object->flags.fields.inherited=0;
    if(object->flags.fields.registered)func_001C1128(D_00475480,object,0);
    void *value=SceneQuery(object);
    if(value)func_0015B640(D_00475480,value);
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[4];
    entry->Message((char *)object+entry->delta,1,object);
}
extern "C" void func_001C7A30(SCENE_OBJECT *object,SCENE_OBJECT *owner,void *parent,int flags) {
    int inherited=0;
    int oldInherited=object->flags.fields.inherited;
    if(owner) {
        int ownerInherited=owner->flags.fields.inherited;
        if(!ownerInherited)goto ownerLists;
    }
    inherited=1;
    if(object->flags.fields.detached)inherited=0;
ownerLists:
    SCENE_LIST *oldList,*newList;
    SCENE_OBJECT **oldAnchor,**newAnchor;
    func_001C7500(object->owner,&oldList,&oldAnchor);
    func_001C7500(owner,&newList,&newAnchor);
    if(object->flags.fields.detached) {
        if(object==*oldAnchor)*oldAnchor=object->previous;
        func_0011B028(oldList,object);
        func_0011AF60(newList,object);
        if(!*newAnchor)*newAnchor=object;
    } else {
        func_0011B028(oldList,object);
        func_0011AFC0(newList,*newAnchor,object);
    }
    if(func_001C8610(object)) {
        CallScene(object,24);
        if(object->handle->object==object)func_0011B028(&D_00479278,object->handle);
    }
    SCENE_OBJECT *oldOwner=object->owner;
    object->owner=owner;
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[13];
    entry->Parent((char *)object+entry->delta,object,oldOwner);
    SCENE_OBJECT **children;
    int count=SceneChildren(object,&children);
    for(int i=0;i<count;i++) {
        SCENE_OBJECT *child=children[i];
        SCENE_VIRTUAL_ENTRY *childEntry=&child->vtable[10];
        childEntry->Change((char *)child+childEntry->delta,owner,parent,flags);
    }
    if(inherited!=oldInherited) {
        if(inherited)CallScene(object,11);
        else CallScene(object,12);
    }
    if(func_001C8610(object))CallScene(object,25);
    else if(!object->owner&&inherited) {
        func_0015ADA0(D_00475480,object->handle);
        func_0015B420(D_00475480,object);
    }
}
extern "C" void func_001C7CC8(SCENE_OBJECT *object,SCENE_OBJECT *requestedOwner,int flags) {
    int current=object->field3C;
    if(!(current&1))*(int *)current|=4;
    else object->field3C=current|4;
    if(object->owner) {
        if(requestedOwner==object&&!flags)func_001C74B0(object);
        object->handle=object->owner->handle;
    } else if(flags) {
        object->handle=0;
        func_001C7470(object);
    }
}
