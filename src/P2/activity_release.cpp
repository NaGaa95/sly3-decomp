// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct ActivityCommandGroup { unsigned char prefix[0x74]; unsigned char *records; };
struct ActivityCommand { int identifier; int kind; ActivityCommandGroup *group; int handle; int index; };
struct ActivityReleaseRecord { unsigned char prefix[0x58]; int index; };
extern "C" {
void func_00267888(void *,int);
void *func_001E8A38(int);
void func_002643F8(void *);
}
extern "C" void func_002646F8(void *rawCommand,void *rawActivity)
{
    ActivityCommand *command=(ActivityCommand *)rawCommand;
    ActivityReleaseRecord *activity=(ActivityReleaseRecord *)rawActivity;
    switch(command->kind) {
    case 4:
        func_00267888(command->group->records+command->index*0x30,activity->index);
        break;
    case 6:
        if(command->handle!=-1) {
            SCENE_OBJECT *object=(SCENE_OBJECT *)func_001E8A38(command->handle);
            if(object) CallScene(object,57);
        }
        break;
    }
    func_002643F8(activity);
}
