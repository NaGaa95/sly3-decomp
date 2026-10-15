// SLY3_CFLAGS: -Os -G0
#include "actor_state_resource_api.h"
#include "activation_retained_api.h"
typedef int ActorStateVector __attribute__((mode(TI)));
struct ActorStateMethod { short delta,unused; void (*method)(); };
struct ActorStateVirtual { char prefix[12]; struct ActorStateMethod *methods; };
struct ActorStateAnimation { char prefix[0x64]; float duration; };
struct ActorStatePair { unsigned int word; struct ActorStateAnimation *animation; };
struct ActorStateRuntime { char prefix[0x14]; struct ActorStateAnimation *animation; char unused18[4]; float time; };
struct ActorStateGate { char prefix[0x190]; int mode; };
struct ActorStateCurrent { char prefix[0x130]; int index; };
struct ActorStateOwner {
    char prefix[12]; struct ActorStateMethod *methods;
    char unused10[0x48-0x10]; void *bone48,*bone4C;
    char unused50[0x1A0-0x50]; union { ActorStateVector packed; unsigned int words[4]; } vector; float phase;
    char unused1B4[0x320-0x1B4]; char request[0x500-0x320];
    char message[8]; int variant;
    char unused50C[0xE40-0x50C]; char contextE40[0xF60-0xE40];
    char contextF60[0x1108-0xF60]; void *lookup;
    char unused110C[0x1134-0x110C]; void *default_resource,*resource1138;
    struct ActorStateRuntime *runtime; void *retained_resource;
    char unused1144[0x1164-0x1144]; int flag;
    char unused1168[0x1290-0x1168]; char controller[0x1470-0x1290];
    struct ActorStatePair pair; char unused1478[0x14C4-0x1478];
    struct ActorStateAnimation *fallback_animation;
    char unused14C8[0x1520-0x14C8]; int state; float changed;
    char unused1528[0x1630-0x1528]; struct ActorStateAnimation *animation5,*animation6,*animation7;
    char unused163C[0x1770-0x163C]; struct ActorStatePair fallback_pair;
    char unused1778[0x1830-0x1778]; char context1830[0x18F8-0x1830];
    void *property18F8,*property18FC;
    char unused1900[0x1940-0x1900]; int condition;
    struct ActorStateAnimation *animation0,*animation18;
    char unused194C[0x19A4-0x194C]; struct ActorStateVirtual *child;
    char unused19A8[0x19B4-0x19A8]; struct ActorStateAnimation *optional_animation;
    struct ActorStateGate *gate;
};
struct ActorStateClock { float time; };
extern struct ActorStateClock D_0036BB98;
extern ActorStateVector D_00317560;
extern char D_00475480[];
void func_0028F068(struct ActorStateOwner *,void *,int);
void func_00155328(struct ActorStateOwner *);
void func_00286360(struct ActorStateGate *,int);
void *func_001FE728(void *,int);
void func_001B4430(void *,int);
void func_001C21F0(void *,int);
void func_0013F8D0(struct ActorStateOwner *);
void func_0013F440(struct ActorStateOwner *,int);
void func_0017E850(void *,int);
void func_0013FB20(struct ActorStateOwner *,int);
void func_001F4B00(void *,int,struct ActorStateOwner *);
void func_002734E8(void *,int);
int func_00173428(void *);
void *func_001733F8(void *);
int func_00239A78(void *,int);
void func_00155310(struct ActorStateOwner *,int);
struct ActorStatePair *func_00173408(void *);
void func_00258F28(struct ActorStatePair *);
void func_001BDBB0(void *,int);
void func_00137628(struct ActorStateRuntime **);
void func_0023AC58(void **);
void func_00137588(struct ActorStateAnimation *,struct ActorStateOwner *,int,struct ActorStateRuntime **,float,float);
#define STATE_CALL0(p,n) ((void (*)(void *))(p)->methods[n].method)((char *)(p)+(p)->methods[n].delta)
#define STATE_CALL1(p,n,a) ((void (*)(void *,int))(p)->methods[n].method)((char *)(p)+(p)->methods[n].delta,a)
#define STATE_INT0(p,n) ((int (*)(void *))(p)->methods[n].method)((char *)(p)+(p)->methods[n].delta)

void func_0013E510(struct ActorStateOwner *owner,int mode)
{
    int old;
    struct ActorStateAnimation *animation;
    void *resource;
    int flags,identifier,mask;
    float time,rate;
    struct ActorStatePair *pair;
    if(mode==owner->state) return;
    switch(owner->state) {
    case 0: case 18:
        func_0028F068(owner,owner->bone48,2);
        func_0028F068(owner,owner->bone4C,2);
        func_00155328(owner);
        if(owner->state==18 && owner->gate && owner->gate->mode==1)
            func_00286360(owner->gate,2);
        break;
    case 11: case 12:
        func_0028F068(owner,owner->bone48,2);
        func_0028F068(owner,owner->bone4C,2);
        break;
    case 2:
        if(owner->flag==0) {
            void *property=0;
            switch(mode) {
            case 0: case 1: case 18: property=owner->property18F8; break;
            case 3:
                switch(owner->variant) {
                case 1: break;
                case 3: case 4: property=owner->property18FC; break;
                default: property=owner->property18F8; break;
                }
                break;
            }
            if(property) func_001FE728(property,1);
        }
        func_001B77F8(owner->request,-1,0);
        break;
    case 3: func_001B4430(owner->message,-1); break;
    case 4: func_001C21F0(owner->contextE40,-1); break;
    case 8:
        if(owner->child) { STATE_CALL1(owner->child,80,1); func_0013F8D0(owner); }
        func_0013F440(owner,-1); break;
    case 16: func_0017E850(owner->context1830,-1); break;
    case 10:
        func_0013FB20(owner,-1);
        func_001F4B00(D_00475480,((struct ActorStateCurrent *)D_0038AE90)->index,owner);
        break;
    case 1: case 9: owner->phase=owner->runtime->time/owner->runtime->animation->duration; break;
    case 14: func_002734E8(owner->controller,-1); break;
    }
    old=owner->state;
    owner->state=mode;
    animation=0; resource=0; flags=1; identifier=-1; mask=4; time=0.0f; rate=1.0f;
    owner->changed=D_0036BB98.time;
    switch(mode) {
    case 0:
        func_0028F068(owner,owner->bone48,1);
        func_0028F068(owner,owner->bone4C,1);
        if(owner->condition) { animation=owner->animation0; flags=9; }
        else {
            int family=owner->lookup && func_00173428(owner->lookup);
            if(family) resource=func_001733F8(owner->lookup);
            if(!resource) resource=owner->default_resource;
            switch(old) {
            case 9: identifier=0x193; break;
            case 2: identifier=0x195; break;
            case 17: identifier=0x197; break;
            default: identifier=0x192; break;
            }
            if(func_00239A78(resource,identifier)<0) identifier=-1;
        }
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
    case 9: {
        int family;
        pair=0;
        family=owner->lookup && func_00173428(owner->lookup);
        if(family) pair=func_00173408(owner->lookup);
        if(!pair) pair=&owner->fallback_pair;
        animation=pair->animation;
        flags=9;
        time=owner->phase*animation->duration;
        func_00258F28(pair);
        break;
    }
    case 4: func_001BDBB0(owner->contextF60,-1); break;
    case 5: animation=owner->animation5; flags=9; break;
    case 6: animation=owner->animation6; flags=9; break;
    case 7: animation=owner->animation7; flags=9; break;
    case 8: func_0013F440(owner,0); return;
    case 16: func_0017E850(owner->context1830,0); return;
    case 10: func_0013FB20(owner,0); return;
    case 11: resource=owner->resource1138;
    case 12:
        func_0028F068(owner,owner->bone48,1);
        func_0028F068(owner,owner->bone4C,1);
        owner->vector.packed=D_00317560;
        break;
    case 15:
        animation=owner->optional_animation;
        if(!animation) { animation=owner->fallback_animation; rate=1.5f; }
        flags=9;
        break;
    case 17: {
        unsigned int *position=owner->vector.words;
        position[0]=position[1]=position[2]=0;
        break;
    }
    case 18:
        func_0028F068(owner,owner->bone48,1);
        func_0028F068(owner,owner->bone4C,1);
        flags=9; animation=owner->animation18;
        owner->vector.packed=D_00317560;
        func_00155310(owner,1);
        break;
    case 14: return;
    case -1: break;
    }
    func_00137628(&owner->runtime);
    func_0023AC58(&owner->retained_resource);
    func_00137588(animation,owner,flags,&owner->runtime,time,rate);
    func_0023AB98(resource,owner,identifier,flags,mask,&owner->retained_resource);
    STATE_CALL0(owner,101);
}
