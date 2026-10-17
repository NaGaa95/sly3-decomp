// SLY3_CFLAGS: -Os -G0
typedef int Vec128 __attribute__((mode(TI)));
struct FwdEntry { short delta,padding; void *(*fn)(void *); };
struct FwdObject { unsigned char prefix[0xC]; struct FwdEntry *table; unsigned char gap10[0x28-0x10]; unsigned long flags; };
struct FwdInner { unsigned char prefix[0x40]; int blocked; };
struct FwdArg { unsigned char prefix[0x14]; struct FwdInner *inner; };
int func_00173B70(struct FwdArg *arg,Vec128 value);
int func_00174238(struct FwdObject *object,struct FwdArg *arg)
{
    int flagged=(object->flags&(1UL<<56))!=0;
    if(flagged) {
        if(!arg->inner->blocked) {
            char *record=(char *)object->table[36].fn((char *)object+object->table[36].delta);
            return func_00173B70(arg,*(Vec128 *)(record+0x30));
        }
    }
    return 0;
}
