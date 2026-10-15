// SLY3_CFLAGS: -Os -G0
#include "sequence_activity_api.h"

struct ActorSubstateMethod { short adjustment,unused; void (*method)(); };
struct ActorSubstateOwner {
    char prefix[12]; struct ActorSubstateMethod *methods;
    char unused10[0x1A0-0x10]; float velocity[4];
    char unused1B0[0x113C-0x1B0]; void *animation; void *resource;
    char unused1144[0x1644-0x1144]; void *mode0_animation;
    void *mode2_animation; void *mode3_animation; void *mode4_animation;
    char unused1654[0x1744-0x1654]; void *fallback_animation;
    char unused1748[0x1760-0x1748]; void *mode1_animation;
    char unused1764[0x1820-0x1764]; int state;
};
void func_0023AC58(void *record);
void func_00137588(void *animation,void *receiver,int flags,void **output,float time,float rate);

void func_0013F440(struct ActorSubstateOwner *receiver,int state)
{
    void *animation;
    int flags;
    if(state==receiver->state) return;
    if(receiver->state==-1)
        func_0023FE38(receiver,0x2B6);
    else if(state==-1)
        func_0023FEC0(receiver,0x2B6);
    receiver->state=state;
    {
        float *velocity=receiver->velocity;
        velocity[2]=0.0f;
        velocity[1]=0.0f;
        velocity[0]=0.0f;
    }
    animation=0;
    flags=1;
    switch(state) {
    case 0: animation=receiver->mode0_animation; break;
    case 1: animation=receiver->mode1_animation; flags=9; break;
    case 2:
        animation=receiver->mode2_animation;
        if(!animation) animation=receiver->fallback_animation;
        flags=9;
        break;
    case 3: animation=receiver->mode3_animation; flags=9; break;
    case 4: animation=receiver->mode4_animation; break;
    }
    func_0023AC58(&receiver->resource);
    func_00137588(animation,receiver,flags,&receiver->animation,0.0f,1.0f);
    ((void (*)(void *))receiver->methods[101].method)((char *)receiver+receiver->methods[101].adjustment);
}
