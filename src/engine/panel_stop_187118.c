// SLY3_CFLAGS: -Os -G0
struct PanelStopSelf {
    unsigned char prefix[0x40]; int kind;
    unsigned char gap44[0x54-0x44]; void *linked;
};
struct PanelStopCurrent { unsigned char prefix[0x6C]; struct PanelStopSelf *owner; };
struct PanelStopContext { unsigned char prefix[0x14A4]; int pending; };
extern struct PanelStopCurrent *D_004794C8;
extern struct PanelStopContext D_0036C700;
void func_001862D0(void *self,int value);
void func_00189B08(void *self,int state);
void func_00188620(void *self);
void func_001854C8(void *context,int event,void *payload);
void func_00186298(void *self);
void func_001734E0(void);

void func_00187118(struct PanelStopSelf *self)
{
    func_001862D0(self,0);
    if(self->kind==2) func_00189B08(self->linked,0);
    else func_00189B08(self->linked,1);
    if(D_004794C8 && D_004794C8->owner==self) func_00188620(D_004794C8);
    func_001854C8(&D_0036C700,0x23,self);
    func_00186298(self);
    func_001734E0();
    D_0036C700.pending=-1;
}

#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char KindOffset[(MEMBER_OFFSET(struct PanelStopSelf,kind)==0x40)?1:-1];
typedef char LinkOffset[(MEMBER_OFFSET(struct PanelStopSelf,linked)==0x54)?1:-1];
typedef char CurrentOwner[(MEMBER_OFFSET(struct PanelStopCurrent,owner)==0x6C)?1:-1];
typedef char PendingOffset[(MEMBER_OFFSET(struct PanelStopContext,pending)==0x14A4)?1:-1];
