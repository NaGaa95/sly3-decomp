// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"
extern "C" unsigned char D_0036C700[];
#include "notify_dispatch_api.h"
extern "C" void func_001854C8(void *,int,SCENE_OBJECT *);
extern "C" void func_001C86B8(SCENE_OBJECT *object,int message,int argument,
                             int count,void *const *parameters,CRef *result) {
    func_0013BB58(object,message,argument,count,parameters,result);
    switch(message) {
        case 5:func_001854C8(D_0036C700,29,object);break;
        case 6:func_001854C8(D_0036C700,30,object);break;
    }
}
