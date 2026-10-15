// Update an emitted tracking state using packed world-space positions.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "state_position_ops.h"
#include "state_emitter_shared.h"
extern "C" {
void func_002389A0(StateEmitter *state);
int func_00238AA8(StateEmitter *state);
int func_00254B80(Actor *owner);
void func_00180460(StateEmitter *state,int mode);
void func_001801C0(StateEmitter *state);
}
inline Matrix4 *ActorMatrix(Actor *actor) {
    VirtualEntry *entry=&actor->table[36];
    return entry->matrix((char *)actor+entry->delta);
}
void func_001801C0(StateEmitter *p) {
    PositionRequest request;
    int state;
    func_002389A0(p);
    qword currentPosition=ActorMatrix(p->actor)->row[3];
    qword difference=PackedDifference(currentPosition,ActorMatrix(p->owner)->row[3]);
    while(!func_00238AA8(p)) {
        state=p->state;
        switch(state) {
        case 0:
            if(func_00254B80(p->owner)) {
                func_00180460(p,2);
            } else if(PackedHorizontalLength(difference)>1000.0f) {
                func_00180460(p,1);
            } else if(PackedHorizontalLength(PackedDifference(p->lastPosition,currentPosition))>250.0f) {
                p->lastPosition=currentPosition;
                qword point=func_001C9428(p->actor,0,p->localPosition);
                func_002B8750(&request);
                request.position=point;
                func_001D7FD0(p->retainedChild,&request);
            }
            break;
        case 1:
            if(func_00254B80(p->owner)) {
                func_00180460(p,2);
            } else if(PackedHorizontalLength(difference)<700.0f) {
                func_00180460(p,0);
            } else if(PackedHorizontalLength(PackedDifference(p->lastPosition,currentPosition))>250.0f) {
                p->lastPosition=currentPosition;
                func_002B8750(&request);
                request.position=currentPosition;
                func_001D7FD0(p->retainedChild,&request);
            }
            break;
        case 2:
            if(!func_00254B80(p->owner))func_00180460(p,0);
            break;
        }
        if(state!=p->state)continue;
        break;
    }
}
