// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
extern "C" void func_001C7F18(SCENE_OBJECT *receiver) {
    SCENE_CALLBACK *callbacks[48];
    SCENE_CALLBACK *callback=receiver->callbacks;
    if(callback) {
        int count=0;
        do {
            callbacks[count++]=callback;
            callback=callback->next;
        } while(callback);
        for(--count;count>=0;--count) {
            callback=callbacks[count];
            callback->function(receiver,callback->argument);
        }
    }
}
