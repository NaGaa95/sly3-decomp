// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
#include "mat.h"
struct SceneLocalTransform {
    MATRIX4 matrix;
    char pad40[0xA4-0x40];
    int generation;
};
struct SceneMatrixState {
    char prefix[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    char pad10[0x44-0x10];
    SceneLocalTransform *local;
    void *firstBounds;
    void *secondBounds;
};
struct SceneMatrixGlobals { char prefix[0x44F4]; int generation; };
extern "C" SceneMatrixGlobals D_00475480;
extern "C" MATRIX4 *func_0011D558(MATRIX4 *,const MATRIX4 *,const MATRIX4 *);
extern "C" void func_0023C8F8(void *);
extern "C" void func_0023DF78(void *);
extern "C" void func_0028F260(void *,void *);
typedef char CheckMatrix64[sizeof(MATRIX4)==64?1:-1];
typedef char CheckState50[sizeof(SceneMatrixState)==0x50?1:-1];
extern "C" void func_0023D028(SceneMatrixState *object,const MATRIX4 *matrix) {
    SceneLocalTransform *local=object->local;
    MATRIX4 product;
    func_0011D558(&product,matrix,&local->matrix);
    local->matrix=product;
    int generation=++D_00475480.generation;
    object->local->generation=generation;
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[20];
    entry->Simple((char *)object+entry->delta);
    func_0023C8F8(object);
    func_0023DF78(object);
    if(object->firstBounds) func_0028F260(object,object->firstBounds);
    if(object->secondBounds) func_0028F260(object,object->secondBounds);
}
