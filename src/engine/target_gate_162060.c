// SLY3_CFLAGS: -Os -G0
struct GateEntry { short delta, padding; int (*fn)(void *); };
struct GateObject { unsigned char prefix[0xC]; struct GateEntry *table; unsigned char gap10[0x28-0x10]; unsigned long flags; };
struct GatePair { struct GateObject *object; int argument; };
int func_001C8F20(struct GateObject *object, int argument);
int func_0013B500(void *object, int kind);
int func_00162060(struct GatePair *pair)
{
    struct GateObject *object = pair->object;
    int flagged;
    if(!object) return 0;
    flagged = (object->flags & (1UL << 56)) != 0;
    if(!flagged) return 0;
    if(func_001C8F20(object, pair->argument)) return 0;
    if(func_0013B500(object, 0x31)) {
        if(object->table[81].fn((char *)object + object->table[81].delta) == 2) return 0;
    } else {
        if(func_0013B500(object, 0x66)) return 0;
    }
    return 1;
}
