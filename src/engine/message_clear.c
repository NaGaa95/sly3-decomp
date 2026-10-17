// SLY3_CFLAGS: -Os -G0
void func_001B40F0(void *context,int kind,int message,int flag);
struct ClearEntry { short delta,padding; void (*fn)(void *,int); };
struct ClearOwner { unsigned char prefix[0xC]; struct ClearEntry *table; unsigned char gap10[0x500-0x10]; char context[8]; int context_kind; };
void func_00154D40(struct ClearOwner *owner,int message)
{
    if(message) func_001B40F0(owner->context,9,message,0);
    else if(owner->context_kind==9) owner->table[99].fn((char *)owner+owner->table[99].delta,0);
}
