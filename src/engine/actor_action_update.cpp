// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"
#include "../P2/input_interface.h"
#include "input_query_api.h"
struct ActorActionMethod {
    short adjustment,unused;
    union { int (*predicate)(void *,int); void (*update)(void *); } call;
};
struct ActorRequestEntry { int kind; void *resource; void *message; };
struct ActorRequestOwner;
union ActorActionVector { qword packed; float components[4]; };
struct ActorActionOptional { char prefix[0x190]; int state; };
struct ActorActionOwner {
    char prefix[12]; ActorActionMethod *methods;
    char before_input[0x134-0x10]; INPUT_INTERFACE *input;
    char before_velocity[0x1A0-0x138]; ActorActionVector velocity;
    char before_context_state[0x508-0x1B0]; int context_state;
    char before_effect[0x10DC-0x50C]; void *effect;
    char before_effect_flag[0x10F8-0x10E0]; int effect_flag;
    char before_lookup[0x1108-0x10FC]; void *lookup;
    char before_animation[0x113C-0x110C]; void *animation; void *resource;
    char before_block[0x13E8-0x1144]; int block;
    char before_state[0x1520-0x13EC]; int state; float state_time;
    char before_reference[0x1560-0x1528]; qword reference;
    char before_direction[0x163C-0x1570]; int direction; int event_flag;
    char before_entry[0x1824-0x1644]; ActorRequestEntry *entry;
    char before_kind[0x19A8-0x1828]; int action_kind;
    char before_optional[0x19B8-0x19AC]; ActorActionOptional *optional;
};
extern "C" {
extern float D_0036BB98;
extern qword D_00317560;
int func_001398F0(void *effect);
int func_002503C8(void *receiver,float threshold);
void func_001B7268(void *context,int kind,void *resource,void *record,float gain);
int func_00156998(void *receiver);
int func_00153290(void *receiver,int option);
int func_00173428(void *lookup);
void func_0013E510(void *receiver,int state);
void func_001BDA88(void *context,int option,const void *record);
void func_001B5170(void *context);
void func_001B9020(void *context);
ActorRequestEntry *func_001400C0(ActorRequestOwner *,int kind);
void func_001B27D8(void *context);
void func_001C2A18(void *context);
qword func_00120D98(qword first,qword second);
int func_0011E9F0(float first,float second,float epsilon);
void func_0013F568(void *receiver);
void func_0017EBA0(void *context);
void func_0013FDE8(void *receiver);
void func_00271F78(void *context);
int func_00138AC8(void *animation);
int func_00239CC0(void *resource);
void func_0013F990(void *receiver);
}
static inline int ActorActionAllowed(ActorActionOwner *receiver,int kind)
{
    ActorActionMethod *method=&receiver->methods[113];
    return method->call.predicate((char *)receiver+method->adjustment,kind);
}
static inline int ActorActionNearXYZ(qword first,qword second)
{
    return func_0011E9F0(PackedVectorX(first),PackedVectorX(second),0.0001f) &&
           func_0011E9F0(PackedVectorY(first),PackedVectorY(second),0.0001f) &&
           func_0011E9F0(PackedVectorZ(first),PackedVectorZ(second),0.0001f);
}
extern "C" void func_0013D518(ActorActionOwner *receiver)
{
    int state;
    do {
        state=receiver->state;
        switch(state) {
        case 2: case 4: case 8: case 10: case 11: case 12: case 13: case 15: case 16:
            break;
        case 17:
            if(func_001398F0(receiver->effect)) goto check_expiration;
            if(receiver->effect_flag) goto check_expiration;
            break;
        case 3:
            if(receiver->context_state==1 || receiver->context_state==12) break;
        default:
check_expiration:
            if(func_002503C8(receiver,0.1f))
                func_001B7268((char *)receiver+0x320,0,0,0,1.0f);
            break;
        }
        switch(receiver->state) {
        case 0: case 1: case 9:
            if(func_00156998(receiver)) {
                func_0013E510(receiver,0);
            } else if(!(receiver->input->held18&8) && !receiver->block && func_00153290(receiver,0)) {
                func_0013E510(receiver,5);
            } else if(func_001A7A80(receiver->input,0x40,0.1f)) {
                int blocked=receiver->lookup && func_00173428(receiver->lookup);
                if(blocked) func_001B7268((char *)receiver+0x320,17,0,0,1.0f);
                else func_001B7268((char *)receiver+0x320,1,0,0,1.0f);
            } else if(receiver->input->Query(0.15f,0x400) &&
                      0.1f<D_0036BB98-receiver->state_time && ActorActionAllowed(receiver,3)) {
                func_0013E510(receiver,0);
                receiver->input->Consume(0x400);
                func_001BDA88((char *)receiver+0xF60,0,0);
            } else if(receiver->input->Query(0.15f,0x10) && ActorActionAllowed(receiver,receiver->action_kind)) {
                receiver->input->Consume(0x10);
                receiver->entry=func_001400C0((ActorRequestOwner *)receiver,receiver->action_kind);
                func_0013E510(receiver,8);
            } else if(func_001A7A80(receiver->input,0x20,0.2f)) {
                func_001B5170((char *)receiver+0x500);
            } else {
                float amount=receiver->input->leftAmount;
                if((receiver->state==0 && 0.1f<amount) || (receiver->state!=0 && 0.0f<amount)) {
                    int blocked=receiver->lookup && func_00173428(receiver->lookup);
                    if(blocked) func_0013E510(receiver,9);
                    else if((receiver->input->held18&8) || receiver->block) func_0013E510(receiver,1);
                    else func_0013E510(receiver,9);
                } else func_0013E510(receiver,0);
            }
            break;
        case 18:
            if(!receiver->optional || receiver->optional->state!=1) func_0013E510(receiver,0);
            break;
        case 2:
            func_001B9020((char *)receiver+0x320);
            if(receiver->input->Query(0.15f,0x10) && ActorActionAllowed(receiver,receiver->action_kind)) {
                receiver->input->Consume(0x10);
                receiver->entry=func_001400C0((ActorRequestOwner *)receiver,receiver->action_kind);
                func_0013E510(receiver,8);
            }
            break;
        case 3: func_001B27D8((char *)receiver+0x500); break;
        case 4: func_001C2A18((char *)receiver+0xE40); break;
        case 5: case 6: case 7:
            if((receiver->input->held18&8) || receiver->block || !func_00153290(receiver,1)) {
                func_0013E510(receiver,0);
            } else if(func_001A7A80(receiver->input,0x40,0.1f)) {
                func_001B7268((char *)receiver+0x320,1,0,0,1.0f);
            } else if(receiver->input->Query(0.15f,0x400) &&
                      0.1f<D_0036BB98-receiver->state_time && ActorActionAllowed(receiver,3)) {
                func_0013E510(receiver,0);
                receiver->input->Consume(0x400);
                func_001BDA88((char *)receiver+0xF60,0,0);
            } else if(func_001A7A80(receiver->input,0x20,0.2f)) {
                func_001B5170((char *)receiver+0x500);
            } else if(receiver->input->Query(0.15f,0x10) && ActorActionAllowed(receiver,receiver->action_kind)) {
                receiver->input->Consume(0x10);
                receiver->entry=func_001400C0((ActorRequestOwner *)receiver,receiver->action_kind);
                func_0013E510(receiver,8);
            }
            if(!receiver->event_flag && (unsigned int)(receiver->state-5)<3U) {
                float alignment=PackedVectorX(func_00120D98(receiver->velocity.packed,receiver->reference));
                if(__builtin_fabsf(alignment)<0.5f && !ActorActionNearXYZ(D_00317560,receiver->velocity.packed)) {
                    receiver->direction=2;
                    func_0013E510(receiver,receiver->velocity.components[1]<0.0f?6:7);
                } else {
                    receiver->direction=alignment<0.0f?1:0;
                    func_0013E510(receiver,5);
                }
            }
            break;
        case 17:
            if(func_001398F0(receiver->effect)) {
                if(0.0f<receiver->input->leftAmount || receiver->input->Query(0.1f,0x40))
                    func_0013E510(receiver,0);
            }
            break;
        case 8: func_0013F568(receiver); break;
        case 16: func_0017EBA0((char *)receiver+0x1830); break;
        case 10: func_0013FDE8(receiver); break;
        case 14: func_00271F78((char *)receiver+0x1290); break;
        case 12:
            if(receiver->animation && func_00138AC8(receiver->animation)) func_0013E510(receiver,0);
            else if(receiver->resource && func_00239CC0(receiver->resource)) func_0013E510(receiver,0);
            break;
        case 15:
            if(2.0f<D_0036BB98-receiver->state_time) func_0013E510(receiver,0);
            break;
        }
        func_0013F990(receiver);
        ActorActionMethod *method=&receiver->methods[98];
        method->call.update((char *)receiver+method->adjustment);
    } while(receiver->state!=state);
}
