// SLY3_CFLAGS: -Os -G0
#include "mat.h"
struct SCENE_OBJECT;
struct SoundGainMethod { short delta,pad; void (*method)(void *,int); };
union SoundGainOwnerFlags {
    unsigned long value;
    struct {
        unsigned long low:32;
        unsigned long tag:8;
        unsigned long unknown40:4;
        long state44:4;
        long state48:4;
        unsigned long detached:1;
        unsigned int flag53:1;
        unsigned int unknown54:1;
        unsigned long registered:1;
        unsigned int inherited:1;
        unsigned int queued:1;
        unsigned int pending:1;
        unsigned long unknown59:1;
        unsigned long queried:1;
        unsigned long unknown61:3;
    } __attribute__((packed)) fields;
} __attribute__((packed,aligned(8)));
struct SoundGainOwner { unsigned char prefix[0x28]; union SoundGainOwnerFlags flags; };
struct SoundGainUpdateView {
    unsigned char prefix[0xC]; struct SoundGainMethod *vtable;
    float gain; int angle; void *unknown18; struct SoundGainOwner *owner;
    qword localPosition;
    float rangeStart,rangeEnd,rateStrength;
    unsigned char gap3C[0xC]; float currentGain,previousDistance; int rate;
    unsigned char gap54[8]; unsigned short flags;
};
extern float D_0036BB9C;
void func_00244CA8(void *,float);
qword func_001C9428(struct SCENE_OBJECT *,struct SCENE_OBJECT *,qword);
void func_00245440(qword,float *,float *,int *,float *);
void func_00245320(void *,unsigned short,unsigned short);
void func_00244E78(void *,int);
int func_00291DD0(int);
void func_00245138(void *receiver)
{
    struct SoundGainUpdateView *state=(struct SoundGainUpdateView *)receiver;
    float gain,distance,newGain;
    int angle;
    int inherited;
    if(state->owner) {
        inherited=state->owner->flags.fields.inherited;
        if(!inherited) {
            func_00244CA8(state,0.0f);
            return;
        }
    }
    func_00245440(func_001C9428((struct SCENE_OBJECT *)state->owner,0,state->localPosition),
                 &state->rangeStart,&gain,&angle,&distance);
    newGain=state->gain*gain;
    if((int)(newGain*1024.0f)!=(int)(state->currentGain*1024.0f)) {
        if(state->currentGain==0.0f)
            state->vtable[15].method((char *)state+state->vtable[15].delta,0);
        else if(newGain==0.0f)
            state->vtable[15].method((char *)state+state->vtable[15].delta,1);
        state->currentGain=newGain;
        func_00245320(state,0x10,0x10);
    }
    func_00244E78(state,angle);
    if(state->owner && state->rateStrength!=0.0f) {
        if(state->flags&1)
            state->rate=0;
        else {
            int converted=func_00291DD0((int)(((state->previousDistance-distance)/D_0036BB9C)*0.02236936241388321f));
            int rate=(int)(state->rateStrength*converted);
            if(rate!=state->rate) {
                state->rate=rate;
                func_00245320(state,0x40,0x40);
            }
        }
    }
    state->previousDistance=distance;
}
