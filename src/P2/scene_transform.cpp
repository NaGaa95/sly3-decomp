// Recovered scene-relative matrix invocation and basis-vector construction.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
#include "mat.h"
extern "C" void func_0011D768(MATRIX4 *,MATRIX4 *);
extern "C" void func_0011D558(MATRIX4 *,MATRIX4 *,MATRIX4 *);
typedef void (*SCENE_TRANSFORM_METHOD)(void *,qword,MATRIX4 *,int,float,float);
extern "C" void func_001C8248(SCENE_OBJECT *object,qword value,MATRIX4 *matrix,float first,float second) {
    MATRIX4 argument,result,inverse;
    MATRIX4 &resultRef=result;
    MATRIX4 &inverseRef=inverse;
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[36];
    MATRIX4 *current=(MATRIX4 *)entry->Query((char *)object+entry->delta);
    func_0011D768(&inverseRef,current);
    func_0011D558(&resultRef,matrix,&inverseRef);
    argument=result;
    entry=&object->vtable[22];
    ((SCENE_TRANSFORM_METHOD)entry->Simple)((char *)object+entry->delta,value,&argument,0,first,second);
}
extern "C" qword func_001C8548(int index) {
    union { VECTOR4 vector;qword value;int words[4]; } result;
    float *component=(float *)&result.vector+index;
    result.words[0]=result.words[1]=result.words[2]=result.words[3]=0;
    *component=1.0f;
    return result.value;
}
