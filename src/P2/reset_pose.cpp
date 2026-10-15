// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Restore the optional stored pose after the common reset and channel update.
#include "scene.h"
#include "rotation_matrix_intrinsics.h"
struct RESET_POSE {
    ROTATION_MATRIX rotation;
    qword position,linear_velocity,angular_velocity;
    int enabled;
};
struct RESET_POSE_OBJECT {
    char reserved0[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    SCENE_OBJECT *owner;
    char reserved14[0x28-0x14];
    unsigned long flags;
    char reserved30[0x48-0x30];
    void *position_attachment,*rotation_attachment;
    char reserved50[0xBC-0x50];
    int index;
    char reservedC0[0x120-0xC0];
    RESET_POSE *pose;
};
struct P;
extern "C" {
    void func_001FC8F8(void *,void *);
    void func_00241150(void *,int);
    qword func_001C9428(SCENE_OBJECT *,SCENE_OBJECT *,qword);
    ROTATION_MATRIX func_001C9598(SCENE_OBJECT *,SCENE_OBJECT *,ROTATION_MATRIX *);
    void func_0023D938(P *,qword);
    void func_0023D9D0(P *,qword);
}
extern "C" void func_001FC968(void *receiver,void *owner)
{
    RESET_POSE_OBJECT *object=(RESET_POSE_OBJECT *)receiver;
    func_001FC8F8(receiver,owner);
    func_00241150(receiver,0);
    if(owner)
        object->index=-1;
    if(object->pose && !owner) {
        if(object->flags&(1UL<<52))
            CallScene((SCENE_OBJECT *)object,20);
        if(object->position_attachment) {
            SCENE_VIRTUAL_ENTRY *entry=&object->vtable[34];
            void *adjusted=(char *)object+entry->delta;
            qword position=func_001C9428(object->owner,0,object->pose->position);
            ((void (*)(void *,qword))entry->Simple)(adjusted,position);
            func_0023D938((P *)object,object->pose->linear_velocity);
        }
        if(object->rotation_attachment) {
            ROTATION_MATRIX rotation=func_001C9598(object->owner,0,&object->pose->rotation);
            SCENE_VIRTUAL_ENTRY *entry=&object->vtable[35];
            ((void (*)(void *,ROTATION_MATRIX *))entry->Simple)
                ((char *)object+entry->delta,&rotation);
            func_0023D9D0((P *)object,object->pose->angular_velocity);
        }
        if(object->pose->enabled)
            CallScene((SCENE_OBJECT *)object,9);
        else
            CallScene((SCENE_OBJECT *)object,8);
    }
}
