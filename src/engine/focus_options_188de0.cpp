// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class FocusOptionReference {
public:
    CRef value;
    FocusOptionReference(int integer) { value.tag=0x13; value.payload.integer=integer; }
    FocusOptionReference(bool flag) { value.tag=0x15; value.payload.integer=flag; }
    FocusOptionReference(const FocusOptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~FocusOptionReference() { Drop(); }
};
struct FocusOption { int kind,payload; };
struct FocusOptionSelf {
    unsigned char prefix[0x44]; int state;
    unsigned char gap48[0x54-0x48]; int first,second;
    unsigned char gap5C[0x6C-0x5C]; void *parent;
    unsigned char gap70[0xD0-0x70];
    FocusOption firstOption,secondOption,boolOption,stateOption,falseOption;
    unsigned char gapF8[0xFC-0xF8]; int guard;
};
extern "C" {
extern unsigned char D_00468D30[];
FocusOptionReference AssignFocusOption(FocusOption *,const FocusOptionReference &,unsigned char *) __asm__("func_002BC050");
int func_00188A38(FocusOptionSelf *self);
void func_00187D30(void *parent);
}
static inline void WriteOption(FocusOption *option,const FocusOptionReference &value,void *context)
{
    FocusOptionReference argument(value);
    const FocusOptionReference &result=AssignFocusOption(option,argument,(unsigned char *)context);
}
static inline void WriteInteger(FocusOption *option,int integer)
{
    unsigned char *context=D_00468D30;
    FocusOptionReference value(integer);
    WriteOption(option,value,context);
}
static inline void WriteBool(FocusOption *option,bool flag)
{
    unsigned char *context=D_00468D30;
    FocusOptionReference value(flag);
    WriteOption(option,value,context);
}
extern "C" void func_00188DE0(FocusOptionSelf *self)
{
    if(self->guard==1 || self->guard==2) return;
    {
        FocusOption *option=&self->firstOption;
        if(option->kind) WriteInteger(option,self->first);
    }
    {
        FocusOption *option=&self->secondOption;
        if(option->kind) WriteInteger(option,self->second);
    }
    {
        FocusOption *option=&self->boolOption;
        if(option->kind) {
            int flag=func_00188A38(self);
            WriteBool(option,flag!=0);
        }
    }
    {
        FocusOption *option=&self->stateOption;
        if(option->kind) WriteInteger(option,self->state);
    }
    {
        FocusOption *option=&self->falseOption;
        if(option->kind) WriteBool(option,false);
    }
    if(self->parent) func_00187D30(self->parent);
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char OwningReferenceSize[(sizeof(FocusOptionReference)==8)?1:-1];
typedef char OptionSize[(sizeof(FocusOption)==8)?1:-1];
typedef char StateOffset[(MEMBER_OFFSET(FocusOptionSelf,state)==0x44)?1:-1];
typedef char FirstOffset[(MEMBER_OFFSET(FocusOptionSelf,first)==0x54)?1:-1];
typedef char SecondOffset[(MEMBER_OFFSET(FocusOptionSelf,second)==0x58)?1:-1];
typedef char ParentOffset[(MEMBER_OFFSET(FocusOptionSelf,parent)==0x6C)?1:-1];
typedef char FirstOptionOffset[(MEMBER_OFFSET(FocusOptionSelf,firstOption)==0xD0)?1:-1];
typedef char SecondOptionOffset[(MEMBER_OFFSET(FocusOptionSelf,secondOption)==0xD8)?1:-1];
typedef char BoolOptionOffset[(MEMBER_OFFSET(FocusOptionSelf,boolOption)==0xE0)?1:-1];
typedef char StateOptionOffset[(MEMBER_OFFSET(FocusOptionSelf,stateOption)==0xE8)?1:-1];
typedef char FalseOptionOffset[(MEMBER_OFFSET(FocusOptionSelf,falseOption)==0xF0)?1:-1];
typedef char GuardOffset[(MEMBER_OFFSET(FocusOptionSelf,guard)==0xFC)?1:-1];
