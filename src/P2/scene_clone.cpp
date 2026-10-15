// Clone reference ownership, packed state and scene context bindings.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
#include "heap.h"
struct SCENE_SCRIPT_REFCOUNTED {
    int references;
    ~SCENE_SCRIPT_REFCOUNTED();
};
struct SCENE_ACTOR_REFCOUNTED {
    int references;
    ~SCENE_ACTOR_REFCOUNTED();
};
struct SCENE_SCRIPT_REFERENCE {
    SCENE_SCRIPT_REFCOUNTED *pointer;
    SCENE_SCRIPT_REFERENCE(const SCENE_SCRIPT_REFERENCE &);
    void operator=(SCENE_SCRIPT_REFCOUNTED *) asm("func_002BBF40");
    ~SCENE_SCRIPT_REFERENCE() {
        SCENE_SCRIPT_REFCOUNTED *value=pointer;
        if(value&&--value->references==0)delete value;
    }
};
struct SCENE_ACTOR_REFERENCE {
    SCENE_ACTOR_REFCOUNTED *pointer;
    SCENE_ACTOR_REFERENCE(const SCENE_ACTOR_REFERENCE &);
    void operator=(SCENE_ACTOR_REFCOUNTED *) asm("func_002BAA50");
    ~SCENE_ACTOR_REFERENCE() {
        SCENE_ACTOR_REFCOUNTED *value=pointer;
        if(value&&--value->references==0)delete value;
    }
};
struct SCENE_REFERENCE_PREFIX { SCENE_ACTOR_REFERENCE actor;SCENE_SCRIPT_REFERENCE script;int reserved8; };
struct SCENE_CONTEXT_LINK {
    int flags;SCENE_CONTEXT_LINK *next;int identifier;
    SCENE_CONTEXT_LINK *nextC;SCENE_OBJECT *owner;SCENE_CONTEXT_LINK *next14;
    SCENE_LIST list;int reserved24;
};
struct SCENE_COPY_GLOBAL { char prefix[0x4638];int mode; };
extern "C" SCENE_COPY_GLOBAL D_00475480;
extern "C" unsigned char D_0036B138[];
extern "C" void func_00129E20(void *);
extern "C" SCENE_SCRIPT_REFERENCE func_0012C820(SCENE_SCRIPT_REFCOUNTED *,void *);
extern "C" SCENE_ACTOR_REFERENCE func_00129BE0(SCENE_ACTOR_REFCOUNTED *,void *);
extern "C" void func_002BBFA8(SCENE_SCRIPT_REFCOUNTED *);
extern "C" void func_002BE530(SCENE_ACTOR_REFCOUNTED *);
extern "C" SCENE_CONTEXT_LINK *func_001D24D0(ALLOCREQ *,SCENE_CONTEXT_LINK *);
extern "C" void func_0011AD68(SCENE_CONTEXT_LINK **);
extern "C" void func_0011AD70(SCENE_LIST *);
extern "C" void func_0011AD80(SCENE_LIST *,SCENE_CONTEXT_LINK *);
extern "C" SCENE_LIST *func_0017DBE8(SCENE_COPY_GLOBAL *,int);
inline ALLOCREQ *SetCopyRequest(ALLOCREQ *request,int bytes,int alignment) {
    request->cb=bytes;request->cbAlign=alignment;return request;
}
inline void SetScriptReference(SCENE_OBJECT *object,SCENE_SCRIPT_REFCOUNTED *value) {
    SCENE_SCRIPT_REFERENCE *reference=(SCENE_SCRIPT_REFERENCE *)((char *)object+4);
    *reference=value;
}
inline void SetActorReference(SCENE_OBJECT *object,SCENE_ACTOR_REFCOUNTED *value) {
    SCENE_ACTOR_REFERENCE *reference=(SCENE_ACTOR_REFERENCE *)object;
    *reference=value;
}
extern "C" void func_001C8BF0(SCENE_OBJECT *destination,SCENE_OBJECT *source) {
    func_00129E20(D_0036B138);
    SCENE_REFERENCE_PREFIX *target=(SCENE_REFERENCE_PREFIX *)destination;
    SCENE_REFERENCE_PREFIX *original=(SCENE_REFERENCE_PREFIX *)source;
    if(original->script.pointer) {
        SetScriptReference(destination,func_0012C820(original->script.pointer,destination).pointer);
        func_002BBFA8(target->script.pointer);
    }
    if(original->actor.pointer) {
        SetActorReference(destination,func_00129BE0(original->actor.pointer,destination).pointer);
        func_002BE530(target->actor.pointer);
    }
    destination->time34=source->time34;
    int state48=source->flags.fields.state48;
    destination->flags.fields.state48=state48;
    int flag53=source->flags.fields.flag53;
    destination->flags.fields.flag53=flag53;
    int state44=source->flags.fields.state44;
    destination->flags.fields.state44=state44;
    int flag54=source->flags.fields.unknown54;
    destination->flags.fields.unknown54=flag54;
    int flags=source->field3C;
    if(!(flags&1))flags=*(int *)flags;
    flags&=~1;
    int storage=destination->field3C;
    if(!(storage&1))*(int *)storage=flags|(*(int *)storage&1);
    else destination->field3C=flags|(storage&1);
    destination->callbacks=source->callbacks;
    if(D_00475480.mode!=-2)destination->context=source->context;
    else {
        SCENE_CONTEXT_LINK *link=(SCENE_CONTEXT_LINK *)source->context;
        while(link&&link->owner==source) {
            ALLOCREQ request;
            SCENE_CONTEXT_LINK *copy=func_001D24D0(SetCopyRequest(&request,40,16),link);
            copy->owner=destination;
            func_0011AD68(&copy->nextC);
            func_0011AD68(&copy->next14);
            func_0011AD70(&copy->list);
            func_0011AD80(&copy->next->list,copy);
            func_0011AD80(func_0017DBE8(&D_00475480,copy->identifier),copy);
            link=link->next;
        }
    }
    SCENE_VIRTUAL_ENTRY *entry=&destination->vtable[6];
    char *sourceBody=(char *)source+0x40;
    char *destinationBody=(char *)destination+0x40;
    char *type=(char *)entry->Query((char *)destination+entry->delta);
    CopyAb(destinationBody,sourceBody,*(int *)(type+0xC)-0x40);
}
