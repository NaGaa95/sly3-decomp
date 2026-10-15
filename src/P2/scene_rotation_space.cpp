// Convert a three-column rotation between optional source and target spaces.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
#include "rotation_matrix_intrinsics.h"
extern "C" void func_0011C6F8(ROTATION_MATRIX *,const ROTATION_MATRIX *);
inline ROTATION_MATRIX *SceneRotationMatrix(SCENE_OBJECT *object) {
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[36];
    return (ROTATION_MATRIX *)entry->Query((char *)object+entry->delta);
}
extern "C" ROTATION_MATRIX func_001C9598(SCENE_OBJECT *source,SCENE_OBJECT *destination,ROTATION_MATRIX *rotation) {
    ROTATION_MATRIX value;
    ROTATION_MATRIX product;
    if(source) {
        MultiplyRotation(&product,SceneRotationMatrix(source),rotation);
        value=product;
    } else value=*rotation;
    ROTATION_MATRIX inverse;
    if(destination) {
        func_0011C6F8(&inverse,SceneRotationMatrix(destination));
        MultiplyRotation(&product,&inverse,&value);
        value=product;
    }
    return value;
}
