// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
typedef unsigned int SceneRateVector __attribute__((mode(TI)));
struct SceneRateAnimation { char prefix[0xDC];void *pending; };
struct SceneRateState {
    SCENE_OBJECT scene;char pad68[0xD8-0x68];SceneRateAnimation *animation;
    char padDC[0x104-0xDC];float scale,rate;
};
struct SceneRateClock { float time,delta; };
struct SceneRateMatrix { char prefix[0x30];SceneRateVector position; };
extern "C" SceneRateClock D_0036BB98;
extern "C" void func_001C8168(void *);
extern "C" void *func_001ED678(SceneRateVector,int);
extern "C" void func_0023C750(void *,void *);
typedef SceneRateMatrix *(*SceneRateMatrixMethod)(void *);
extern "C" void func_0023C660(SceneRateState *object) {
    func_001C8168(object);
    void *pending=object->animation?object->animation->pending:0;
    if(pending) {
        SCENE_VIRTUAL_ENTRY *entry=&object->scene.vtable[36];
        SceneRateMatrix *matrix=((SceneRateMatrixMethod)entry->Simple)((char *)object+entry->delta);
        func_0023C750(object,func_001ED678(matrix->position,1));
    }
    float rate=object->rate;
    if(rate!=0.0f) {
        float value=object->scale+D_0036BB98.delta*rate;
        object->scale=value;
        if(value<=0.0f) {
            object->scale=0.0f;
            object->rate=0.0f;
            CallScene(&object->scene,9);
        } else if(1.0f<=value) {
            object->scale=1.0f;
            object->rate=0.0f;
        }
    }
}
