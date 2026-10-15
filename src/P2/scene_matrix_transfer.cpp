// Forward a scene matrix query and apply a transformed position/orientation.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
#include "mat.h"
extern "C" qword func_0028E910(SCENE_OBJECT *,MATRIX4 *,qword);
extern "C" void func_0028EA00(MATRIX3 *,SCENE_OBJECT *,MATRIX3 *,MATRIX4 *);
extern "C" void func_001C8FB0(SCENE_OBJECT *destination,SCENE_OBJECT *source) {
    MATRIX4 matrix;
    SCENE_VIRTUAL_ENTRY *entry=&source->vtable[37];
    void *value=((void *(*)(void *,MATRIX4 *))entry->Simple)((char *)source+entry->delta,&matrix);
    entry=&destination->vtable[43];
    ((void (*)(void *,void *,MATRIX4 *))entry->Simple)((char *)destination+entry->delta,value,&matrix);
}
extern "C" void func_001C9008(SCENE_OBJECT *destination,SCENE_OBJECT *source,MATRIX4 *transform) {
    MATRIX3 orientation;
    SCENE_VIRTUAL_ENTRY *positionEntry=&destination->vtable[34];
    void *adjusted=(char *)destination+positionEntry->delta;
    qword position=func_0028E910(source,0,((qword *)transform)[3]);
    ((void (*)(void *,qword))positionEntry->Simple)(adjusted,position);
    func_0028EA00(&orientation,source,0,transform);
    SCENE_VIRTUAL_ENTRY *orientationEntry=&destination->vtable[35];
    ((void (*)(void *,MATRIX3 *))orientationEntry->Simple)((char *)destination+orientationEntry->delta,&orientation);
}
