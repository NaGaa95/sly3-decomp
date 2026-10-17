// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00317570;
struct InitEntry { short delta,padding; void (*fn)(void *); };
struct InitChild { unsigned char prefix[0xC]; struct InitEntry *table; };
void func_0023C580(void *receiver);
void *func_0023DDA0(void *owner,int identity,int kind);
void *func_00130078(void *owner,void *channel,int a,int b,int c,Qword value);
void func_001697D0(void *receiver,int flag);
struct InitRecord { unsigned char prefix[0x18]; int identity; unsigned char gap1C[0x3C-0x1C]; unsigned int tagged; unsigned char gap40[0x13C-0x40]; struct InitChild *child; void *task; };
void func_001696F0(struct InitRecord *record)
{
    unsigned int value;
    func_0023C580(record);
    record->task=func_00130078(record,func_0023DDA0(record,record->identity,0xC),5,8,3,D_00317570);
    if(record->child) record->child->table[9].fn((char *)record->child+record->child->table[9].delta);
    value=record->tagged;
    if((value^1)&1)*(unsigned int *)value|=2;
    else record->tagged=value|2;
    func_001697D0(record,0);
}
