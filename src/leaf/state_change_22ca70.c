// SLY3_CFLAGS: -Os -G0
// State change of a simple actor (states 0..8): tear down the old state (bones, request/message/context, animation phase, linked
// task), then set up the new one (identifier/mask, pair animations, linked tasks, vector) and restart the runtime animation and
// the retained resource. Sibling of func_0013E510 (src/engine/actor_state.c).
#include "actor_state_resource_api.h"
#include "activation_retained_api.h"
typedef int ActorStateVector __attribute__((mode(TI)));
struct ActorStateMethod { short delta,unused; void (*method)(); };
struct ActorStateAnimation { char prefix[0x64]; float duration; };
struct ActorStatePair { unsigned int word; struct ActorStateAnimation *animation; };
struct ActorStateRuntime { char prefix[0x14]; struct ActorStateAnimation *animation; char unused18[4]; float time; };
struct ActorStateLink { char prefix[0x14]; void **target; };
struct ActorStateOwner {
    char prefix[12]; struct ActorStateMethod *methods;
    char unused10[0x48-0x10]; void *bone48,*bone4C;
    char unused50[0x180-0x50]; int flag180;
    char unused184[0x1A0-0x184]; union { ActorStateVector packed; unsigned int words[4]; } vector; float phase;
    char unused1B4[0x320-0x1B4]; char request[0x500-0x320];
    char message[0xA24-0x500]; int linkA24;
    char unusedA28[0xE40-0xA28]; char contextE40[0xF60-0xE40];
    char contextF60[0x1134-0xF60]; void *default_resource,*resource1138;
    struct ActorStateRuntime *runtime; void *retained_resource;
    char unused1144[0x1470-0x1144]; int state; float changed;
    char unused1474[0x1480-0x1478]; struct ActorStatePair pair; char unused1488[0x1530-0x1488]; struct ActorStatePair pair2;
    char unused1538[0x15E0-0x1538]; struct ActorStateLink *link; void *task15E4,*task15E8; void *resource15EC; struct ActorStateLink *link15F0; float time15F4;
};
struct ActorStateClock { float time; };
extern struct ActorStateClock D_0036BB98;
extern ActorStateVector D_00317560;
extern char D_00475480[];
void func_0028F068(struct ActorStateOwner *,void *,int);
void func_00155328(struct ActorStateOwner *);
void func_001B4430(void *,int);
void func_001C21F0(void *,int);
int func_00239A78(void *,int);
void func_00155310(struct ActorStateOwner *,int);
void func_00258F28(struct ActorStatePair *);
void func_001BDBB0(void *,int);
void func_00137628(struct ActorStateRuntime **);
void func_0023AC58(void **);
void func_00137588(struct ActorStateAnimation *,struct ActorStateOwner *,int,struct ActorStateRuntime **,float,float);
void func_0022D2B0(struct ActorStateOwner *);
void func_0013BD88(void *,void *);
void func_0013BD00(void *,void *);
void func_001A28C8(void *,void *);
void func_001309D8(void *);
void func_001C7A00(struct ActorStateOwner *,void *,int);
void func_0013CD10(void *,struct ActorStateOwner *);
void *func_00130078(void *,void *,int,int,int,ActorStateVector);
#define STATE_CALL0(p,n) ((void (*)(void *))(p)->methods[n].method)((char *)(p)+(p)->methods[n].delta)
#define STATE_INT0(p,n) ((int (*)(void *))(p)->methods[n].method)((char *)(p)+(p)->methods[n].delta)

void func_0022CA70(struct ActorStateOwner *owner,int mode)
{
    int old;
    struct ActorStateAnimation *animation;
    void *resource;
    int flags,identifier,mask;
    float time,rate;
    if(mode==owner->state) return;
    switch(owner->state) {
    case 0:
        func_0028F068(owner,owner->bone48,2);
        func_0028F068(owner,owner->bone4C,2);
        func_00155328(owner);
        break;
    case 8:
        func_0028F068(owner,owner->bone48,2);
        func_0028F068(owner,owner->bone4C,2);
        break;
    case 3: func_001B77F8(owner->request,-1,0); break;
    case 4: func_001B4430(owner->message,-1); break;
    case 5: func_001C21F0(owner->contextE40,-1); break;
    case 1: case 2: owner->phase=owner->runtime->time/owner->runtime->animation->duration; break;
    case 6: {
        int saved;
        func_0022D2B0(owner);
        func_0013BD88(*owner->link->target,owner);
        func_001A28C8(owner->link,0);
        func_001309D8(&owner->task15E4);
        func_001309D8(&owner->task15E8);
        saved=owner->linkA24;
        func_001C7A00(owner,0,0xF);
        owner->linkA24=saved;
        owner->link15F0=owner->link;
        owner->link=0;
        owner->time15F4=D_0036BB98.time;
        func_0028F068(owner,owner->bone48,1);
        func_0028F068(owner,owner->bone4C,1);
        owner->flag180=0;
        func_0013CD10(D_00475480,owner);
        break;
    }
    }
    old=owner->state;
    owner->state=mode;
    animation=0; resource=0; flags=1; identifier=-1; mask=4; time=0.0f; rate=1.0f;
    owner->changed=D_0036BB98.time;
    switch(mode) {
    case 0:
        func_0028F068(owner,owner->bone48,1);
        func_0028F068(owner,owner->bone4C,1);
        resource=owner->default_resource;
        switch(old) {
        case 2: identifier=0x193; break;
        case 3: identifier=0x195; break;
        case 7: identifier=0x197; break;
        default: identifier=0x192; break;
        }
        if(func_00239A78(resource,identifier)<0) identifier=-1;
        owner->vector.packed=D_00317560;
        mask=STATE_INT0(owner,111);
        func_00155310(owner,1);
        break;
    case 1:
        animation=owner->pair.animation;
        time=owner->phase*animation->duration;
        func_00258F28(&owner->pair);
        flags=9;
        break;
    case 2:
        animation=owner->pair2.animation;
        time=owner->phase*animation->duration;
        func_00258F28(&owner->pair2);
        flags=9;
        break;
    case 5: func_001BDBB0(owner->contextF60,-1); break;
    case 6:
        func_001A28C8(owner->link,owner);
        func_0013BD00(*owner->link->target,owner);
        {
            int saved=owner->linkA24;
            func_001C7A00(owner,owner->link,0xF);
            owner->linkA24=saved;
        }
        owner->task15E4=func_00130078(owner,owner->bone48,5,8,2,D_00317560);
        owner->task15E8=func_00130078(owner,owner->bone4C,5,8,2,D_00317560);
        owner->flag180=1;
        resource=owner->resource15EC;
        func_0013CD10(D_00475480,owner);
        break;
    case 7:
        {
            unsigned int *position=owner->vector.words;
            position[0]=position[1]=position[2]=0;
        }
        break;
    case 8:
        func_0028F068(owner,owner->bone48,1);
        func_0028F068(owner,owner->bone4C,1);
        owner->vector.packed=D_00317560;
        break;
    case -1: break;
    }
    func_00137628(&owner->runtime);
    func_0023AC58(&owner->retained_resource);
    func_00137588(animation,owner,flags,&owner->runtime,time,rate);
    func_0023AB98(resource,owner,identifier,flags,mask,&owner->retained_resource);
    STATE_CALL0(owner,101);
}
