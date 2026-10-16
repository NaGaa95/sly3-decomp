// SLY3_CFLAGS: -Os -G0
struct EngineFlagObject { unsigned char prefix[0x28]; unsigned long flags; };
struct EngineFlagWorld { unsigned char prefix[0x10D8]; struct EngineFlagObject *object; };
struct EngineFlagOwner { unsigned char prefix[0x10]; struct EngineFlagWorld *world; };
int func_0019AEF8(struct EngineFlagOwner *owner)
{
    struct EngineFlagObject *object=owner->world->object;
    int result=0;
    if(object) result=(object->flags&(1UL<<56))!=0;
    return result;
}
