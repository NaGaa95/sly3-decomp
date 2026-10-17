// SLY3_CFLAGS: -Os -G0
struct FlagRecord;
struct FlagEntry { short delta,padding; struct FlagRecord *(*fn)(void *); };
struct FlagRecord { unsigned char prefix[0x28]; unsigned long flags; unsigned char gap30[0x3C-0x30]; int tagged; };
struct FlagSub { unsigned char prefix[0x14]; struct FlagEntry *table; int word18; };
struct FlagSelf { unsigned char prefix[0x28]; unsigned long flags; unsigned char gap30[0x3C-0x30]; int tagged; unsigned char gap40[0x210-0x40]; float f210; unsigned char gap214[0x224-0x214]; struct FlagEntry *table; int word228; };
void func_0028FD70(void *self);
void func_0015BDF8(void *list);
void func_0015CB98(struct FlagSelf *self)
{
    struct FlagSub *sub=(struct FlagSub *)((char *)self+0x210);
    struct FlagRecord *record;
    int value;
    func_0028FD70(self);
    func_0015BDF8((char *)self+0x120);
    sub->table[1].fn((char *)sub+sub->table[1].delta)->flags|=1UL<<60;
    self->f210=1250.0f;
    sub->word18=-1;
    record=sub->table[1].fn((char *)sub+sub->table[1].delta);
    value=record->tagged;
    if((value^1)&1)*(int *)value&=-0x41;
    else record->tagged=value&-0x41;
    self->flags&=~(1UL<<60);
    value=self->tagged;
    if((value^1)&1)*(int *)value&=-3;
    else self->tagged=value&-3;
}
