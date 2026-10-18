// SLY3_CFLAGS: -Os -G0
struct TickItem { unsigned char prefix[0x60]; unsigned long flags; };
struct TickSubject {
    unsigned char prefix[0xB4]; struct TickSubject *chosen;
    int state; float started; void *pending; struct TickItem *item;
};
struct TickPrompt;
struct TickController { unsigned char prefix[0x50]; int mode; };
struct TickApplication { unsigned char prefix[0x14]; struct TickController *controller; };
struct TickGame { unsigned char prefix[0x433C]; struct TickPrompt *prompt; };
struct TickClock { float time; };
extern struct TickApplication D_004BC230;
extern struct TickGame D_00475480;
extern struct TickPrompt *D_004797C0;
extern struct TickClock D_0036BBD8;
extern unsigned char D_003751D0[],D_0046FBE0[],D_00370AF0[];
void func_001C8168(struct TickSubject *self);
int func_00186930(struct TickSubject *self);
int func_00186B68(struct TickSubject *self);
int func_00260758(struct TickPrompt *prompt,int id);
void func_00186F90(struct TickSubject *self);
void func_00186FE8(struct TickSubject *self);
void func_00187270(struct TickSubject *self);
void func_001874E8(struct TickSubject *self);
void func_001878E0(struct TickSubject *self,int state);
int func_0021DD30(void *system);
int func_001A7980(int button);
int func_001C6F20(void *context);
void func_00283F70(struct TickApplication *application);
static __inline__ int ApplicationMode(void)
{
    struct TickController *controller=D_004BC230.controller;
    int mode=controller ? controller->mode : -1;
    return mode;
}
void func_001875B0(struct TickSubject *self)
{
    func_001C8168(self);
    switch(self->state) {
    case 4:
        if(!(self->item->flags&1)) func_00186F90(self);
        break;
    case 5: {
        int mode=ApplicationMode();
        if(mode==0) {
            if(!func_00260758(D_00475480.prompt,func_00186930(self)))
                func_001878E0(self,3);
        } else {
            if(!func_00260758(D_004797C0,0x376)) func_001878E0(self,7);
        }
        break;
    }
    case 7:
        if(0.5f<D_0036BBD8.time-self->started &&
           !func_0021DD30(D_003751D0) && !func_0021DD30(D_0046FBE0) && func_001A7980(0x40))
            func_00186FE8(self);
        break;
    case 1:
        if(!func_00260758(D_00475480.prompt,func_00186930(self))) {
            if(ApplicationMode()==0 || ApplicationMode()==2) {
                func_001878E0(self,3);
            } else {
                if(self->chosen || self->pending || func_001C6F20(D_00370AF0) || ApplicationMode()==1) {
                    func_00187270(self);
                    func_001874E8(self);
                    func_001878E0(self,8);
                } else {
                    func_00187270(self);
                    func_001878E0(self,2);
                }
            }
        }
        break;
    case 2:
        if(!func_00260758(D_00475480.prompt,func_00186B68(self))) {
            func_001874E8(self);
            func_001878E0(self,0);
        }
        break;
    case 3:
        if(!func_0021DD30(D_003751D0) && !func_0021DD30(D_0046FBE0)) {
            if(func_001A7980(0x80)) func_00186FE8(self);
            else if(func_001A7980(0x10)) {
                func_00283F70(&D_004BC230);
                func_001878E0(self,8);
            }
        }
        break;
    case 6: case 8:
        break;
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char FlagsOffset[(MEMBER_OFFSET(struct TickItem,flags)==0x60)?1:-1];
typedef char FlagsSize[(sizeof(((struct TickItem *)0)->flags)==8)?1:-1];
typedef char ChosenOffset[(MEMBER_OFFSET(struct TickSubject,chosen)==0xB4)?1:-1];
typedef char StateOffset[(MEMBER_OFFSET(struct TickSubject,state)==0xB8)?1:-1];
typedef char TimeOffset[(MEMBER_OFFSET(struct TickSubject,started)==0xBC)?1:-1];
typedef char PendingOffset[(MEMBER_OFFSET(struct TickSubject,pending)==0xC0)?1:-1];
typedef char ItemOffset[(MEMBER_OFFSET(struct TickSubject,item)==0xC4)?1:-1];
typedef char ControllerOffset[(MEMBER_OFFSET(struct TickApplication,controller)==0x14)?1:-1];
typedef char PromptOffset[(MEMBER_OFFSET(struct TickGame,prompt)==0x433C)?1:-1];
