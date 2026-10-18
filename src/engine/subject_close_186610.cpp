// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
class SubjectCloseBase {
public:
    int prefix[3];
    virtual void V1();
    virtual void V2();
    virtual void Message(int event,int schedule,int count,void **arguments,int result);
};
struct Action;
struct Notification;
class SubjectClose : public SubjectCloseBase {
public:
    unsigned char gap10[0x98-0x10];
    int actionCount; Action *actions;
    int notificationCount; Notification *notifications;
    unsigned char gapA8[0xF0-0xA8]; int flag;
};
struct SubjectCloseOverlay { unsigned char prefix[0x6C]; SubjectClose *owner; };
struct SubjectCloseGame {
    unsigned char prefix[0x404C]; SubjectCloseOverlay *overlay;
    unsigned char gap4050[0x4428-0x4050]; int selection;
};
extern "C" {
extern SubjectCloseGame D_00475480;
extern unsigned char D_0036C700[];
void func_0018AA48(void *game,void *panel);
void func_0018AAE0(void *game,void *overlay);
int func_0025E150(void);
int func_00185FD8(void *self);
void func_001854C8(void *context,int event,void *payload);
void func_00185A70(void *self,int state,int count,Action *actions);
void func_00185DB0(void *self,int state,int count,Notification *notifications,int flag);
}
extern "C" void func_00186610(SubjectClose *self)
{
    func_0018AA48(&D_00475480,0);
    if(D_00475480.overlay && D_00475480.overlay->owner && D_00475480.overlay->owner==self)
        func_0018AAE0(&D_00475480,0);
    switch(func_0025E150()) {
    case 3: case 8: case 15: case 23: case 31: case 32:
        D_00475480.selection=0x1A8;
        break;
    }
    if(func_00185FD8(self)) {
        func_001854C8(D_0036C700,0x26,self);
        func_00185A70(self,5,self->actionCount,self->actions);
        func_00185DB0(self,5,self->notificationCount,self->notifications,self->flag);
        self->Message(0x17,0,0,0,0);
    }
}

#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char BaseSize[(sizeof(SubjectCloseBase)==16)?1:-1];
typedef char CountOffset[(MEMBER_OFFSET(SubjectClose,actionCount)==0x98)?1:-1];
typedef char ActionsOffset[(MEMBER_OFFSET(SubjectClose,actions)==0x9C)?1:-1];
typedef char NotificationCountOffset[(MEMBER_OFFSET(SubjectClose,notificationCount)==0xA0)?1:-1];
typedef char NotificationsOffset[(MEMBER_OFFSET(SubjectClose,notifications)==0xA4)?1:-1];
typedef char FlagOffset[(MEMBER_OFFSET(SubjectClose,flag)==0xF0)?1:-1];
typedef char OwnerOffset[(MEMBER_OFFSET(SubjectCloseOverlay,owner)==0x6C)?1:-1];
typedef char OverlayOffset[(MEMBER_OFFSET(SubjectCloseGame,overlay)==0x404C)?1:-1];
typedef char SelectionOffset[(MEMBER_OFFSET(SubjectCloseGame,selection)==0x4428)?1:-1];
