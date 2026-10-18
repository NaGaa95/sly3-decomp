// SLY3_CFLAGS: -Os -G0
struct FocusOfferOwner { unsigned char prefix[0x4C]; int selection; };
struct FocusOfferSelf {
    unsigned char prefix[0x6C]; struct FocusOfferOwner *parent;
    unsigned char gap70[0xAC-0x70]; int recordIndex;
    unsigned char gapB0[0xC0-0xB0]; int selection;
};
struct FocusOfferGame {
    unsigned char prefix[0x4044]; void *current;
    unsigned char gap4048[0x42D4-0x4048]; int state;
    unsigned char gap42D8[0x441C-0x42D8]; int recordIndex;
};
struct FocusOfferBank {
    unsigned char prefix[0x10]; int current;
    unsigned char gap14[0x100-0x14]; int pending;
};
struct FocusOfferRecord;
struct FocusOfferApplication;
extern struct FocusOfferGame D_00475480;
extern struct FocusOfferBank D_0036BC10;
extern struct FocusOfferApplication D_004BC230;
extern unsigned char D_0036C700[];
extern int D_0036DBE0;
void func_0018AAE0(struct FocusOfferGame *game,struct FocusOfferSelf *subject);
void func_001854C8(void *context,int event,void *subject);
int func_00186200(struct FocusOfferOwner *parent,int recordIndex);
struct FocusOfferRecord *func_0025E070(int recordIndex);
void func_00289070(struct FocusOfferGame *game,struct FocusOfferRecord *record,int kind,unsigned int flags,int requestIndex);
void func_00284568(struct FocusOfferApplication *application);
void func_00187040(void *parent);
static inline int CurrentSelection(struct FocusOfferBank *bank)
{
    return bank->pending?12:bank->current;
}
void func_00189F38(struct FocusOfferSelf *self,unsigned int flags)
{
    int special=0;
    int changed;
    func_0018AAE0(&D_00475480,self);
    func_001854C8(D_0036C700,0x21,self->parent);
    changed=self->parent!=D_00475480.current;
    if(changed || (flags&0x100)) special=1;
    if(changed) {
        int identity=0;
        if(self->parent) identity=func_00186200(self->parent,self->recordIndex);
        if(identity!=-1 && D_0036DBE0!=identity) flags|=2;
    }
    if(D_00475480.recordIndex!=self->recordIndex) flags|=2;
    else if(D_00475480.state>=2) {
        int selection=self->selection;
        if(self->parent && self->parent->selection!=-1) selection=self->parent->selection;
        if(selection==D_0036BC10.current && D_0036BC10.pending) selection=12;
        if(selection!=CurrentSelection(&D_0036BC10)) flags|=2;
    }
    func_00289070(&D_00475480,func_0025E070(self->recordIndex),0x1A8,flags|4,special?-1:0x36B);
    if(changed) {
        func_00284568(&D_004BC230);
        if(D_00475480.current) func_00187040(D_00475480.current);
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char OwnerSelectionOffset[(MEMBER_OFFSET(struct FocusOfferOwner,selection)==0x4C)?1:-1];
typedef char ParentOffset[(MEMBER_OFFSET(struct FocusOfferSelf,parent)==0x6C)?1:-1];
typedef char RecordIndexOffset[(MEMBER_OFFSET(struct FocusOfferSelf,recordIndex)==0xAC)?1:-1];
typedef char SelectionOffset[(MEMBER_OFFSET(struct FocusOfferSelf,selection)==0xC0)?1:-1];
typedef char GameCurrentOffset[(MEMBER_OFFSET(struct FocusOfferGame,current)==0x4044)?1:-1];
typedef char GameStateOffset[(MEMBER_OFFSET(struct FocusOfferGame,state)==0x42D4)?1:-1];
typedef char GameRecordOffset[(MEMBER_OFFSET(struct FocusOfferGame,recordIndex)==0x441C)?1:-1];
typedef char BankCurrentOffset[(MEMBER_OFFSET(struct FocusOfferBank,current)==0x10)?1:-1];
typedef char BankPendingOffset[(MEMBER_OFFSET(struct FocusOfferBank,pending)==0x100)?1:-1];
