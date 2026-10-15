// Recovered pointer collection growth and recursive scene state propagation.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "object_collection.h"
#include "heap.h"
inline int MaximumCapacity(int first,int second){return first>second?first:second;}
extern "C" void *func_001D25B0(ALLOCREQ *);
extern "C" int func_0013B500(SCENE_OBJECT *,int);
extern "C" int func_0025E150();
void OBJECT_COLLECTION::Append(int count,SCENE_OBJECT **values) {
    int needed=this->count+count;
    if(this->capacity<needed) {
        int capacity=this->capacity;
        do {
            capacity=MaximumCapacity(32,capacity*2);
        }while(capacity<needed);
        ALLOCREQ request;
        request.cb=capacity*sizeof(SCENE_OBJECT *);
        request.cbAlign=16;
        SCENE_OBJECT **allocated=(SCENE_OBJECT **)func_001D25B0(&request);
        CopyAb(allocated,this->values,this->count*sizeof(SCENE_OBJECT *));
        this->capacity=capacity;
        this->values=allocated;
    }
    CopyAb(this->values+this->count,values,count*sizeof(SCENE_OBJECT *));
    this->count+=count;
}
extern "C" void func_00151B60(SCENE_OBJECT *object,int state) {
    object->flags.fields.state44=state;
    if(func_0013B500(object,47)) {
        for(SCENE_OBJECT *child=object->children.first;child;child=child->previous)
            func_00151B60(child,state);
    }
}
