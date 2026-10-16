// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct P;
extern "C" {
void *func_0017E1B8(void *,int,int,void *);
int func_0013B500(char *,int);
void func_00241338(P *,float);
void func_002412C8(void *,float);
}
extern "C" void *func_0025D740(void *game,int enabled,int key,void *owner,float gain)
{
    SCENE_OBJECT *object=(SCENE_OBJECT *)func_0017E1B8(game,4,key,owner);
    if(object) {
        if(gain!=0.0f && func_0013B500((char *)object,0x2F)) {
            if(enabled) func_00241338((P *)object,gain);
            else func_002412C8(object,gain);
        } else {
            if(enabled) CallScene(object,8);
            else CallScene(object,9);
        }
    }
    return object;
}
