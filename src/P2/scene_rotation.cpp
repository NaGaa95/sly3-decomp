// Scene Euler rotations are stored in radians and exposed in degrees.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
#include "vector_intrinsics.h"
#include "matrix_algorithms.h"
extern "C" void func_0011C9E8(MATRIX3 *,qword);

extern "C" qword func_001C87C0(SCENE_OBJECT *object) {
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[36];
    MATRIX4 *matrix=(MATRIX4 *)entry->Query((char *)object+entry->delta);
    qword value=func_0011D3C0((const MATRIX3 *)matrix);
    union { qword vector;float scalar; } result;
    result.vector=PackVectorXYZ(PackedVectorX(value)*57.2957763671875f,
                                PackedVectorY(value)*57.2957763671875f,
                                PackedVectorZ(value)*57.2957763671875f);
    return result.vector;
}
extern "C" void func_001C8838(SCENE_OBJECT *object,qword value) {
    MATRIX3 argument;
    union { qword vector;float scalar; } converted;
    MATRIX3 matrix;
    converted.vector=PackVectorXYZ(PackedVectorX(value)*0.01745329424738884f,
                                   PackedVectorY(value)*0.01745329424738884f,
                                   PackedVectorZ(value)*0.01745329424738884f);
    func_0011C9E8(&matrix,converted.vector);
    argument=matrix;
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[35];
    ((void (*)(void *,MATRIX3 *))entry->Simple)((char *)object+entry->delta,&argument);
}
