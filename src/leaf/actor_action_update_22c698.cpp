// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Actor action update for a reduced state set (sibling of func_0013D518 in src/engine/actor_action_update.cpp).
#include "../P2/input_interface.h"
#include "input_query_api.h"
struct ActorActionMethod {
    short adjustment,unused;
    union { int (*predicate)(void *,int); void (*update)(void *); } call;
};
struct ActorActionOwner {
    char prefix[12]; ActorActionMethod *methods;
    char before_input[0x134-0x10]; INPUT_INTERFACE *input;
    char before_context_state[0x508-0x138]; int context_state;
    char before_effect[0x10DC-0x50C]; void *effect;
    char before_effect_flag[0x10F8-0x10E0]; int effect_flag;
    char before_animation[0x113C-0x10FC]; void *animation; void *resource;
    char before_block[0x13E8-0x1144]; int block;
    char before_state[0x1470-0x13EC]; int state; float state_time;
};
extern "C" {
extern float D_0036BB98;
int func_001398F0(void *effect);
int func_002503C8(void *receiver,float threshold);
void func_001B7268(void *context,int kind,void *resource,void *record,float gain);
int func_00156998(void *receiver);
void func_0022CA70(void *receiver,int command);
void func_001BDA88(void *context,int option,const void *record);
void func_001B5170(void *context);
void func_001B9020(void *context);
void func_001B27D8(void *context);
void func_001C2A18(void *context);
int func_00138AC8(void *animation);
int func_00239CC0(void *resource);
}
static inline int ActorActionAllowed(ActorActionOwner *receiver,int kind)
{
    ActorActionMethod *method=&receiver->methods[113];
    return method->call.predicate((char *)receiver+method->adjustment,kind);
}
extern "C" void func_0022C698(ActorActionOwner *receiver)
{
    int state;
    do {
        state=receiver->state;
        switch(state) {
        case 3: case 5: case 6: case 8:
            break;
        case 7:
            if(func_001398F0(receiver->effect)) goto check_expiration;
            if(!receiver->effect_flag) break;
            goto check_expiration;
        case 4:
            if(receiver->context_state==1 || receiver->context_state==12) break;
check_expiration:
            if(func_002503C8(receiver,0.1f))
                func_001B7268((char *)receiver+0x320,0,0,0,1.0f);
            break;
        default:
            if(func_002503C8(receiver,0.1f))
                func_001B7268((char *)receiver+0x320,0,0,0,1.0f);
            break;
        }
        switch(receiver->state) {
        case 0: case 1: case 2:
            if(func_00156998(receiver)) {
                func_0022CA70(receiver,0);
            } else if(func_001A7A80(receiver->input,0x40,0.1f)) {
                func_001B7268((char *)receiver+0x320,1,0,0,1.0f);
            } else if(receiver->input->Query(0.15f,0x400) &&
                      0.1f<D_0036BB98-receiver->state_time && ActorActionAllowed(receiver,3)) {
                func_0022CA70(receiver,0);
                receiver->input->Consume(0x400);
                func_001BDA88((char *)receiver+0xF60,0,0);
            } else if(func_001A7A80(receiver->input,0x20,0.2f)) {
                func_001B5170((char *)receiver+0x500);
            } else {
                float amount=receiver->input->leftAmount;
                if((receiver->state==0 && 0.1f<amount) || (receiver->state!=0 && 0.0f<amount)) {
                    if((receiver->input->held18&8) || receiver->block) func_0022CA70(receiver,1);
                    else func_0022CA70(receiver,2);
                } else func_0022CA70(receiver,0);
            }
            break;
        case 3: func_001B9020((char *)receiver+0x320); break;
        case 4: func_001B27D8((char *)receiver+0x500); break;
        case 5: func_001C2A18((char *)receiver+0xE40); break;
        case 7:
            if(func_001398F0(receiver->effect)) {
                if(0.0f<receiver->input->leftAmount) func_0022CA70(receiver,2);
                else if(func_001A7A80(receiver->input,0x40,0.1f)) func_001B7268((char *)receiver+0x320,1,0,0,1.0f);
            }
            break;
        case 8:
            if(receiver->animation && func_00138AC8(receiver->animation)) func_0022CA70(receiver,0);
            else if(receiver->resource && func_00239CC0(receiver->resource)) func_0022CA70(receiver,0);
            break;
        }
        ActorActionMethod *method=&receiver->methods[98];
        method->call.update((char *)receiver+method->adjustment);
    } while(receiver->state!=state);
}
