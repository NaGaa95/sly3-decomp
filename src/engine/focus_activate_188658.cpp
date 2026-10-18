// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
class FocusActivateBase {
public:
    int prefix[3];
    virtual void V1();
    virtual void V2();
    virtual void Message(int event,int schedule,int count,void **arguments,int result);
};
struct FocusActivateActor { unsigned char prefix[0x3C]; int flags; };
struct FocusActivateItem;
struct Action;
struct Notification;
class FocusActivate : public FocusActivateBase {
public:
    unsigned char gap10[0x4C-0x10]; int sound; int soundEnabled; int activations;
    unsigned char gap58[0x6C-0x58]; void *owner;
    unsigned char gap70[0x98-0x70]; int actionCount; Action *actions;
    int notificationCount; Notification *notifications; int selection;
    unsigned char gapAC[0xC4-0xAC]; FocusActivateItem *item;
    FocusActivateActor *actor; FocusActivateItem *stopItem;
    unsigned char gapD0[0xFC-0xD0]; int notificationFlag;
};
struct FocusActivateGame;
struct FocusActivateController { unsigned char prefix[0x50]; int mode; };
struct FocusActivateApplication { unsigned char prefix[0x14]; FocusActivateController *controller; };
extern "C" {
extern FocusActivateGame D_00475480;
extern FocusActivateApplication D_004BC230;
extern unsigned char D_0036C700[],D_0046F770[];
void func_0018AAB8(void *game,void *self);
int func_002845B0(void *application,void *self,int flags);
void func_001871C0(void *owner);
void func_0018AAE0(void *game,void *self);
int func_00187CB8(void *owner);
void func_00186DA0(void *owner);
int func_001880F0(void *self);
void func_00188DE0(void *self);
void func_001854C8(void *context,int event,void *self);
void func_00185A70(void *self,int state,int count,Action *actions);
void func_00185DB0(void *self,int state,int count,Notification *notifications,int flag);
void func_0021E870(void *audio,int selector,float duration);
void func_00226010(void *item);
void func_00189078(void *self,int state,int extra);
int func_002852B0(void *application);
void func_0027FCC8(void *actor);
}
extern "C" void func_00188658(FocusActivate *self)
{
    func_0018AAB8(&D_00475480,self);
    if(func_002845B0(&D_004BC230,self,4)) {
        func_001871C0(self->owner);
        return;
    }
    if(self->selection!=-1) {
        int hit=0;
        if(!D_004BC230.controller || D_004BC230.controller->mode==1) hit=1;
        if(hit) func_0018AAE0(&D_00475480,self);
    }
    if(self->owner && !func_00187CB8(self->owner)) func_00186DA0(self->owner);
    if(func_001880F0(self)) {
        self->activations++;
        func_00188DE0(self);
        func_001854C8(D_0036C700,0x27,self);
        func_00185A70(self,4,self->actionCount,self->actions);
        func_00185DB0(self,4,self->notificationCount,self->notifications,self->notificationFlag);
        if(self->sound!=-1 && self->soundEnabled) func_0021E870(D_0046F770,self->sound,-1.0f);
        self->Message(0x16,0,0,0,0);
        if(self->stopItem) func_00226010(self->stopItem);
        if(self->item) func_00189078(self,2,0);
        if(self->actor && !func_002852B0(&D_004BC230)) {
            FocusActivateActor *actor=self->actor;
            int flags=actor->flags;
            if((flags^1)&1) *(int *)flags|=0x200;
            else actor->flags=flags|0x200;
            func_0027FCC8(self->actor);
        }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char BaseSize[(sizeof(FocusActivateBase)==16)?1:-1];
typedef char SoundOffset[(MEMBER_OFFSET(FocusActivate,sound)==0x4C)?1:-1];
typedef char ActivationsOffset[(MEMBER_OFFSET(FocusActivate,activations)==0x54)?1:-1];
typedef char OwnerOffset[(MEMBER_OFFSET(FocusActivate,owner)==0x6C)?1:-1];
typedef char ActionsOffset[(MEMBER_OFFSET(FocusActivate,actions)==0x9C)?1:-1];
typedef char NotificationsOffset[(MEMBER_OFFSET(FocusActivate,notifications)==0xA4)?1:-1];
typedef char SelectionOffset[(MEMBER_OFFSET(FocusActivate,selection)==0xA8)?1:-1];
typedef char ItemOffset[(MEMBER_OFFSET(FocusActivate,item)==0xC4)?1:-1];
typedef char ActorOffset[(MEMBER_OFFSET(FocusActivate,actor)==0xC8)?1:-1];
typedef char StopItemOffset[(MEMBER_OFFSET(FocusActivate,stopItem)==0xCC)?1:-1];
typedef char NotificationFlagOffset[(MEMBER_OFFSET(FocusActivate,notificationFlag)==0xFC)?1:-1];
