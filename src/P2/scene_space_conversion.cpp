// Convert packed coordinates between optional source and target scene spaces.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
#include "vector_matrix_intrinsics.h"
extern "C" void func_0011D768(MATRIX4 *,MATRIX4 *);
extern "C" void func_0011C6F8(MATRIX3 *,MATRIX3 *);
inline MATRIX4 *SceneMatrix(SCENE_OBJECT *object) {
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[36];
    return (MATRIX4 *)entry->Query((char *)object+entry->delta);
}
extern "C" void func_001C93A8(SCENE_OBJECT *object) {
    if(object->flags.fields.unknown59) {
        SCENE_VIRTUAL_ENTRY *entry=&object->vtable[30];
        ((void (*)(void *,void *))entry->Simple)((char *)object+entry->delta,0);
        entry=&object->vtable[29];
        ((void (*)(void *,void *))entry->Simple)((char *)object+entry->delta,0);
    }
}
extern "C" qword func_001C9428(SCENE_OBJECT *source,SCENE_OBJECT *destination,qword point) {
    MATRIX4 inverse;
    struct {qword vector;} value;
    value.vector=point;
    if(source)value.vector=TransformPackedPoint(SceneMatrix(source),value.vector);
    if(destination) {
        func_0011D768(&inverse,SceneMatrix(destination));
        value.vector=TransformPackedPoint(&inverse,value.vector);
    }
    return value.vector;
}
extern "C" qword func_001C94E8(SCENE_OBJECT *source,SCENE_OBJECT *destination,qword direction) {
    MATRIX3 inverse;
    struct {qword vector;} value;
    value.vector=direction;
    if(source)value.vector=TransformPackedDirection((MATRIX3 *)SceneMatrix(source),value.vector);
    if(destination) {
        func_0011C6F8(&inverse,(MATRIX3 *)SceneMatrix(destination));
        value.vector=TransformPackedDirection(&inverse,value.vector);
    }
    return value.vector;
}
