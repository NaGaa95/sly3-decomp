// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionWriteReference {
public:
    CRef value;
    OptionWriteReference(int integer) { value.tag=0x13; value.payload.integer=integer; }
    OptionWriteReference(const OptionWriteReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionWriteReference() { Drop(); }
};
struct KEY;
class SubjectOpenBase {
public:
    int prefix[3];
    virtual void V1();
    virtual void V2();
    virtual void Message(int event,int schedule,int count,void **arguments,int result);
};
struct SubjectTarget {
    unsigned char prefix[0x18]; int first;
    unsigned char gap1C[0xAC-0x1C]; int second;
};
struct Action;
struct Notification;
class SubjectOpen : public SubjectOpenBase {
public:
    unsigned char gap10[0x5C-0x10]; SubjectTarget *target;
    unsigned char gap60[0x7C-0x60]; int opens;
    unsigned char gap80[0x98-0x80]; int actionCount; Action *actions;
    int notificationCount; Notification *notifications;
    unsigned char gapA8[0xF0-0xA8]; int flag;
};
struct SubjectOpenGame {
    unsigned char prefix[0x407C]; KEY *first,*second;
    unsigned char gap4084[0x4348-0x4084]; int flags;
};
struct SubjectMode { unsigned char prefix[0x50]; int mode; };
struct SubjectApplication { unsigned char prefix[0x14]; SubjectMode *selected; };
extern "C" {
extern SubjectOpenGame D_00475480;
extern SubjectApplication D_004BC230;
extern unsigned char D_0036C700[];
extern unsigned char D_00468D30[];
OptionWriteReference AssignWriteOption(KEY *,const OptionWriteReference &,unsigned char *) __asm__("func_002BC050");
void func_0018AA48(void *game,void *panel);
int func_00185FD8(void *self);
int func_002852B0(void *application);
void func_001862D0(void *self,int enabled);
void func_00187D30(void *self);
void func_001854C8(void *context,int event,void *payload);
void func_00185A70(void *self,int state,int count,Action *actions);
void func_00185DB0(void *self,int state,int count,Notification *notifications,int flag);
}
static inline void WriteOption(KEY *key,OptionWriteReference value,void *context)
{
    AssignWriteOption(key,value,(unsigned char *)context);
}
static inline void WriteInteger(KEY *key,int integer)
{
    unsigned char *context=D_00468D30;
    OptionWriteReference value(integer);
    WriteOption(key,value,context);
}
extern "C" void func_00186338(SubjectOpen *self)
{
    func_0018AA48(&D_00475480,self);
    if(func_00185FD8(self)) {
        if(func_002852B0(&D_004BC230) && (D_00475480.flags&0x80)) {
            int mode=D_004BC230.selected ? D_004BC230.selected->mode : -1;
            switch(mode) {
            case 1: func_001862D0(self,0); break;
            case 0: case 2: func_001862D0(self,1); break;
            }
            D_00475480.flags&=~0x80;
        }
        self->opens++;
        func_00187D30(self);
        func_001854C8(D_0036C700,0x25,self);
        func_00185A70(self,4,self->actionCount,self->actions);
        func_00185DB0(self,4,self->notificationCount,self->notifications,self->flag);
        self->Message(0x16,0,0,0,0);
        if(self->target) {
            WriteInteger(D_00475480.first,self->target->first);
            WriteInteger(D_00475480.second,self->target->second);
        } else {
            WriteInteger(D_00475480.first,0);
            WriteInteger(D_00475480.second,0);
        }
    }
}

#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char BaseSize[(sizeof(SubjectOpenBase)==16)?1:-1];
typedef char OwningReferenceSize[(sizeof(OptionWriteReference)==8)?1:-1];
typedef char TargetOffset[(MEMBER_OFFSET(SubjectOpen,target)==0x5C)?1:-1];
typedef char OpenCountOffset[(MEMBER_OFFSET(SubjectOpen,opens)==0x7C)?1:-1];
typedef char ActionsOffset[(MEMBER_OFFSET(SubjectOpen,actions)==0x9C)?1:-1];
typedef char NotificationsOffset[(MEMBER_OFFSET(SubjectOpen,notifications)==0xA4)?1:-1];
typedef char FlagOffset[(MEMBER_OFFSET(SubjectOpen,flag)==0xF0)?1:-1];
typedef char FirstKeyOffset[(MEMBER_OFFSET(SubjectOpenGame,first)==0x407C)?1:-1];
typedef char SecondKeyOffset[(MEMBER_OFFSET(SubjectOpenGame,second)==0x4080)?1:-1];
typedef char GameFlagsOffset[(MEMBER_OFFSET(SubjectOpenGame,flags)==0x4348)?1:-1];
typedef char ModeOwnerOffset[(MEMBER_OFFSET(SubjectApplication,selected)==0x14)?1:-1];
typedef char ModeOffset[(MEMBER_OFFSET(SubjectMode,mode)==0x50)?1:-1];
typedef char FirstValueOffset[(MEMBER_OFFSET(SubjectTarget,first)==0x18)?1:-1];
typedef char SecondValueOffset[(MEMBER_OFFSET(SubjectTarget,second)==0xAC)?1:-1];
