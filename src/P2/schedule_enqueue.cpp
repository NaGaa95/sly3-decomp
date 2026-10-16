// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct SchedulePrimary { unsigned char prefix[0xDC]; unsigned char *target; };
struct ScheduleSource { int unknown_0; SchedulePrimary *primary; };
struct ScheduleNode { ScheduleSource *source; SCENE_OBJECT *other; };
extern "C" ScheduleNode *func_0011E118(void *pool);
extern "C" int func_0011B0C0(void *target);
extern "C" void func_0011AF60(void *list,ScheduleNode *node);
extern "C" void func_0025DDB0(void *owner,ScheduleSource *source,SCENE_OBJECT *other)
{
    if(source) {
        unsigned char *target=source->primary->target;
        if(target && func_0011B0C0(target+0x34)) {
            int inherited=other->flags.fields.inherited;
            if(inherited) {
                ScheduleNode *node=func_0011E118((char *)owner+0x494C);
                node->source=source;
                node->other=other;
                func_0011AF60((char *)owner+0x4964,node);
            }
        }
    }
}
