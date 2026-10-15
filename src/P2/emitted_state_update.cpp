// Update the position state after the emitted child's progress changes.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "vector_intrinsics.h"

struct StateClock { float time,step; };
extern StateClock D_0036BB98;
struct WorldFrame { char prefix[0x28];int frame; };
extern WorldFrame *D_0047A27C;
struct Owner { char prefix[0x1144];int flags; };
struct Curve;
struct ChildState { char prefix[0x30];Curve *curve;float progress; };
struct EmittedState {
    char prefix[0x10];Owner *owner;int unknown14;ChildState *child;
    char pad1C[0x14];int state;
    char pad34[0x4C];float lastUpdate;int lastFrame;
};
struct TransitionRequest {
    char header[16];VECTOR4 position;
};
typedef char TransitionRequest_is_32[(sizeof(TransitionRequest)==32)?1:-1];

extern "C" {
void func_002389A0(EmittedState *state);
int func_00238AA8(EmittedState *state);
int func_001D8AC0(ChildState *child);
void func_001D77E0(EmittedState *state,int mode,void *payload);
int func_001D8FD8(ChildState *child);
float func_001EF588(Curve *curve);
void func_001EF498(Curve *curve,float progress,VECTOR4 *position,VECTOR4 *direction);
qword func_00250600(Owner *owner);
int func_00238AD0(EmittedState *state);
void func_001D7D10(EmittedState *state);
void *func_00292034(void *destination,int byteValue,unsigned int bytes);
void func_001D79C0(EmittedState *state);
}

static inline float Minimum(float left,float right) { return left <? right; }

void func_001D79C0(EmittedState *p) {
    int state;
    func_002389A0(p);
    if(!(p->owner->flags&2))return;
    while(!func_00238AA8(p)) {
        state=p->state;
        switch(state) {
        case 1:
        case 2:
            {
                ChildState *child=p->child;
                if(state==2&&func_001D8AC0(child)) {
                    func_001D77E0(p,3,0);
                } else if(D_0036BB98.time-p->lastUpdate>5.0f || p->lastFrame!=D_0047A27C->frame) {
                    func_001D7D10(p);
                } else if(func_001D8FD8(child)) {
                    TransitionRequest request;
                    func_00292034(&request,0,sizeof(request));
                    float target=child->progress+50.0f;
                    float limit=func_001EF588(child->curve);
                    func_001EF498(child->curve,Minimum(limit,target),&request.position,0);
                    request.position.z=PackedVectorZ(func_00250600(p->owner));
                    func_001D77E0(p,5,&request);
                }
            }
            break;
        case 3:
            if(func_00238AD0(p))func_001D7D10(p);
            break;
        case 5:
            if(func_00238AD0(p))func_001D7D10(p);
            break;
        }
        if(state!=p->state)continue;
        break;
    }
}
