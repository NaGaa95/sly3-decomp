// SLY3_CFLAGS: -Os -G0
// Recover the Sly 3 state change from the corresponding Sly 2 algorithm.
#include "state_emitter_shared.h"
struct Clock {
    float time, step;
};
extern struct Clock D_0036BB98;
struct EmittedObject {
    char prefix[0xC];
    struct VirtualEntry *table;
    char pad10[0x28];
    union {
        int event;
        struct Actor *actor;
    }
    field38;
    int mode3C;
    char pad40[0x48];
    struct Actor *actor88;
    int mode8C;
    char pad90[0x14];
    int enabledA4;
};
void func_00238AE8(void *retained);
struct EmittedObject *func_00238690(void *pool, int type);
void func_00180460(struct StateEmitter *p,int state) {
    struct PositionRequest request;
    if(state==p->state)return;
    func_00238AE8(&p->retainedChild);
    p->state=state;
    p->changedAt=D_0036BB98.time;
    switch(state) {
        case 1: {
            struct EmittedObject *object=func_00238690((char *)p->owner+0x29C,0xE1);
            struct VirtualEntry *entry=&p->actor->table[36];
            qword position=entry->matrix((char *)p->actor+entry->delta)->row[3];
            p->lastPosition=position;
            object->enabledA4=1;
            object->actor88=p->actor;
            object->mode8C=1;
            func_002B8750(&request);
            request.position=position;
            func_001D7FD0(object,&request);
            object->field38.event=0x30;
            entry=&object->table[8];
            entry->call((char *)object+entry->delta);
        }
        break;
        case 2: {
            struct EmittedObject *object=func_00238690((char *)p->owner+0x29C,0xCA);
            struct VirtualEntry *entry;
            object->field38.actor=p->actor;
            object->mode3C=1;
            entry=&object->table[8];
            entry->call((char *)object+entry->delta);
        }
        break;
        case 0: {
            struct EmittedObject *object=func_00238690((char *)p->owner+0x29C,0xE1);
            struct VirtualEntry *entry=&p->actor->table[36];
            qword position;
            p->lastPosition=entry->matrix((char *)p->actor+entry->delta)->row[3];
            position=func_001C9428(p->actor,0,p->localPosition);
            object->enabledA4=1;
            func_002B8750(&request);
            request.position=position;
            func_001D7FD0(object,&request);
            object->actor88=p->actor;
            entry=&object->table[8];
            entry->call((char *)object+entry->delta);
        }
        break;
    }
}
