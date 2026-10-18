// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class SubjectOptionReference {
public:
    CRef value;
    SubjectOptionReference(int integer) { value.tag=0x13; value.payload.integer=integer; }
    SubjectOptionReference(bool flag) { value.tag=0x15; value.payload.integer=flag; }
    SubjectOptionReference(float real) { value.tag=0x14; value.payload.real=real; }
    SubjectOptionReference(const SubjectOptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~SubjectOptionReference() { Drop(); }
};
struct SubjectOption { int kind,payload; };
struct SubjectOptionSelf {
    unsigned char prefix[0x7C]; int count;
    unsigned char gap80[0xA8-0x80]; float real;
    unsigned char gapAC[0xD0-0xAC]; SubjectOption integerOption,boolOption,realOption;
    unsigned char gapE8[0xF0-0xE8]; int state;
};
extern "C" {
extern unsigned char D_00468D30[];
SubjectOptionReference AssignSubjectOption(SubjectOption *,const SubjectOptionReference &,unsigned char *) __asm__("func_002BC050");
int func_00187CD0(SubjectOptionSelf *self);
}
static inline void WriteOption(SubjectOption *option,const SubjectOptionReference &value,void *context)
{
    SubjectOptionReference argument(value);
    const SubjectOptionReference &result=AssignSubjectOption(option,argument,(unsigned char *)context);
}
static inline void WriteInteger(SubjectOption *option,int integer)
{
    unsigned char *context=D_00468D30;
    SubjectOptionReference value(integer);
    WriteOption(option,value,context);
}
static inline void WriteBool(SubjectOption *option,bool flag)
{
    unsigned char *context=D_00468D30;
    SubjectOptionReference value(flag);
    WriteOption(option,value,context);
}
extern "C" void func_00187D30(SubjectOptionSelf *self)
{
    if(self->state==1 || self->state==2) return;
    {
        SubjectOption *option=&self->integerOption;
        if(option->kind) WriteInteger(option,self->count);
    }
    {
        SubjectOption *option=&self->boolOption;
        if(option->kind) {
            int flag=func_00187CD0(self);
            WriteBool(option,flag!=0);
        }
    }
    {
        SubjectOption *option=&self->realOption;
        if(option->kind) {
            SubjectOptionReference value(self->real);
            WriteOption(option,value,D_00468D30);
        }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char OwningReferenceSize[(sizeof(SubjectOptionReference)==8)?1:-1];
typedef char OptionSize[(sizeof(SubjectOption)==8)?1:-1];
typedef char CountOffset[(MEMBER_OFFSET(SubjectOptionSelf,count)==0x7C)?1:-1];
typedef char RealOffset[(MEMBER_OFFSET(SubjectOptionSelf,real)==0xA8)?1:-1];
typedef char IntegerOptionOffset[(MEMBER_OFFSET(SubjectOptionSelf,integerOption)==0xD0)?1:-1];
typedef char BoolOptionOffset[(MEMBER_OFFSET(SubjectOptionSelf,boolOption)==0xD8)?1:-1];
typedef char RealOptionOffset[(MEMBER_OFFSET(SubjectOptionSelf,realOption)==0xE0)?1:-1];
typedef char StateOffset[(MEMBER_OFFSET(SubjectOptionSelf,state)==0xF0)?1:-1];
