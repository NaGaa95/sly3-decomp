// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Qualified Sly2 algorithm: hand/func_0017ECF0.c. Actual Sly3 fields and clamp flag.
#include "state_emitter_shared.h"
struct CursorOwner { char prefix[0x2F0];int speedMode; };
struct CurveInterval { float low,high; };
struct CurveIntervals;
struct CursorCurve {
    char prefix[0xD4];int wraps;
    char gap[0x170-0xD8];struct CurveIntervals *intervals;
};
struct EmittedObject { char prefix[0x94];int insideLimits; };
struct CursorState {
    char prefix[0x10];struct CursorOwner *owner;
    char gap14[4];struct EmittedObject *output;
    char gap1C[0x30-0x1C];struct CursorCurve *curve;
    int forward;float position;char gap3C[4];qword value;
    char gap50[8];int ignoreIntervals;
};
float func_0022DFB0(struct CursorCurve *curve);
float func_0022DFD8(struct CursorCurve *curve);
float func_0022E058(struct CursorCurve *curve,float position);
void func_00231D00(struct CurveIntervals *intervals);
struct CurveInterval *func_002320A0(struct CurveIntervals *intervals,float position);
void func_0022E330(struct CursorCurve *curve,qword *position,qword *direction,float value);

void func_001D9500(struct CursorState *state,int force)
{
    float step=250.0f;
    int speedMode=state->owner->speedMode;
    int clamped;
    float position;
    if(speedMode<3){
        if(speedMode>0)step=100.0f;
    }
    if(state->forward==0)
        step=-step;
    position=state->position+step;
    clamped=0;
    if(state->curve->wraps==0){
        float low=func_0022DFB0(state->curve);
        float high=func_0022DFD8(state->curve);
        float bounded;
        if(position<low)bounded=low;
        else if(high<position)bounded=high;
        else bounded=position;
        if(bounded!=position){position=bounded;clamped=1;}
    }else{
        position=func_0022E058(state->curve,position);
    }
    if(state->ignoreIntervals==0){
        struct CurveInterval *interval;
        func_00231D00(state->curve->intervals);
        interval=func_002320A0(state->curve->intervals,position);
        if(interval)
            position=func_0022E058(state->curve,state->forward?interval->high:interval->low);
    }
    if(force==0 && __builtin_fabsf(state->position-position)<5.0f)
        return;
    state->position=position;
    func_0022E330(state->curve,&state->value,0,position);
    {
        struct EmittedObject *output=state->output;
        struct PositionRequest request;
        output->insideLimits=!clamped;
        func_002B8750(&request);
        request.position=state->value;
        func_001D7FD0(output,&request);
    }
}
