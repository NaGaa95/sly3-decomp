// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Complete original716 command and264 release; original zero4 is separate.
// Algorithm reference only: Sly2 18DA48/18DD78. Fields/events are Sly3 original.
#include "actor_state_resource_api.h"
#include "actor_command_method_api.h"
#include "activation_selector_api.h"

struct CommandActor {
    char prefix320[0x320];
    char context320;
    char unused321[0x500-0x321];
    char context500;
    char unused501[0x508-0x501];
    int mode508;
    char unused50C[0x10D0-0x50C];
    char context10D0;
    char unused10D1[0x1108-0x10D1];
    void *resource1108;
    char unused110C[0x1400-0x110C];
    int current_command;
    char unused1404[0x19E0-0x1404];
    int state;
    char unused19E4[0x1EF4-0x19E4];
    void *retained_sound;
    char unused1EF8[4];
    void *landing1EFC;
    char unused1F00[0x1F1C-0x1F00];
    int flag1F1C;
    void *record1F20;
    char unused1F24[8];
    void *request1F2C;
    char unused1F30[0x1F44-0x1F30];
    void *resource1F44;
    void *resource1F48;
};
extern char D_0036C700[];
extern char D_0036BB98[];
extern float D_0047A3D0;
void func_001854C8(void *context,int event,void *receiver);
void func_00154460(void *receiver,int command);
void func_001545A8(void *receiver,int command);
void func_00165548(void *clock,int channel,float scale);
void *func_002459F8(int identifier);
void func_00244F08(void *sound,void *owner);
void func_002BBCD8(void **reference,void *value);
void func_001ADDD0(void *receiver,int state,int secondary);
void func_001FE728(void *receiver,int value);
void func_001B7268(void *context,int kind,void *resource,void *record,float gain);
void *func_00279C28(void);
int func_00173428(void *resource);
void func_00172AE8(void *resource,int identifier);
int func_00173560(int command);
void func_0013A678(void *context,void *resource,int option);
void func_00244CA8(void *sound,float gain);

void func_001AF6C0(struct CommandActor *p, int command)
{
    p->current_command=command;
    func_001854C8(D_0036C700,0x4D,p);
    p->current_command=-1;
    switch (command) {
    case 0x21: {
        void *sound;
        func_00154460(p,command);
        func_00165548(D_0036BB98,1,0.25f);
        D_0047A3D0=-1.0f;
        sound=func_002459F8(0x67);
        func_00244F08(sound,0);
        func_002BBCD8(&p->retained_sound,sound);
        break;
    }
    case 0x1B:
        func_00154460(p,command);
        func_001B77F8(&p->context320,0x14,0);
        break;
    case 0x1A:
        func_00154460(p,command);
        func_001ADDD0(p,7,-1);
        break;
    case 0x23:
        func_00154460(p,command);
        func_001ADDD0(p,19,6);
        break;
    case 0x20:
        func_00154460(p,command);
        func_001B40F0(&p->context500,2,0,0);
        break;
    case 0x1E:
        if (p->landing1EFC)func_001FE728(p->landing1EFC,1);
        func_00154460(p,command);
        func_001B7268(&p->context320,9,0,0,1.0f);
        break;
    case 0x1D:
        func_00154460(p,command);
        func_001B7268(&p->context320,13,0,0,1.0f);
        break;
    case 0x22:
        func_00154460(p,command);
        p->flag1F1C=1;
        break;
    case 0x24:
        p->record1F20=func_00279C28();
        func_001ADDD0(p,24,8);
        break;
    case 0x25:
        func_00154460(p,command);
        if (p->request1F2C)func_00239CE8(p->request1F2C,0x1A1);
        break;
    case 0x19:
        func_00154460(p,command);
        func_0013A678(&p->context10D0,p->resource1F48,0);
        break;
    case 0x26: case 0x27: case 0x28: {
        int family=p->resource1108&&func_00173428(p->resource1108);
        if (family)func_00172AE8(p->resource1108,-1);
        else {
            func_00154460(p,command);
            func_00172AE8(p->resource1108,func_00173560(command));
        }
        break;
    }
    case 0x1F:
        func_00154460(p,command);
        func_0013A678(&p->context10D0,p->resource1F44,0);
        break;
    default:
        func_001545A8(p,command);
        break;
    }
}

void func_001AF990(struct CommandActor *p, int command)
{
    switch (command) {
    case 0x21: {
        void **reference;
        func_00165548(D_0036BB98,1,1.0f);
        reference=&p->retained_sound;
        if (*reference) {
            func_00244CA8(*reference,0.0f);
            func_002BBCD8(reference,0);
        }
        D_0047A3D0=0.0f;
        break;
    }
    case 0x23:
        if (p->state==19)
            func_001B7268(&p->context320,11,0,0,1.0f);
        break;
    case 0x22:
        p->flag1F1C = 0;
        break;
    case 0x20:
        if (p->state==8&&p->mode508==2)
            func_001B7268(&p->context320,11,0,0,1.0f);
        break;
    default:
        func_001546B0(p,command);
        break;
    }
}
