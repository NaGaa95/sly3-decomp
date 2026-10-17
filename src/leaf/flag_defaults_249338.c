// SLY3_CFLAGS: -Os -G0
struct FlagRecord;
struct FlagEntry { short delta,padding; struct FlagRecord *(*fn)(void *); };
struct FlagRecord { unsigned char prefix[0x28]; unsigned long flags; unsigned char gap30[0x3C-0x30]; int tagged; };
struct FlagSub { unsigned char prefix[0x14]; struct FlagEntry *table; int word18; };
struct FlagSelf { unsigned char prefix[0xF8]; float f0F8; unsigned char gap0FC[0x11C-0xFC]; float f11C; };
void func_0028FD70(void *self);
void func_001A0708(void *object);
void func_001C9118(void *object,int mode);
void func_00249338(struct FlagSelf *self)
{
    struct FlagSub *sub=(struct FlagSub *)((char *)self+0xF8);
    struct FlagRecord *record;
    int value;
    func_0028FD70(self);
    func_001A0708((char *)self+0xD0);
    func_001C9118(self,2);
    self->f11C=1.0f;
    sub->table[1].fn((char *)sub+sub->table[1].delta)->flags|=1UL<<60;
    self->f0F8=1250.0f;
    sub->word18=-1;
    record=sub->table[1].fn((char *)sub+sub->table[1].delta);
    value=record->tagged;
    if((value^1)&1)*(int *)value&=-0x41;
    else record->tagged=value&-0x41;
}
