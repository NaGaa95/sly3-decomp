// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short displacement; short pad; int (*method)(void *); };
struct KindObject { unsigned char opaque00[0xC]; struct VirtualEntry *vtable; };
struct StatusOwner { struct KindObject *object; int mode04; unsigned char opaque08[0x10]; int state18; };
int func_001F43C8(void *object);
int func_001C4018(void *receiver)
{
    struct StatusOwner *owner = (struct StatusOwner *)receiver;
    struct VirtualEntry *entry = owner->object->vtable + 100;
    if (entry->method((char *)owner->object + entry->displacement) != 3)
        return owner->state18 == 1;
    if (func_001F43C8(owner->object) <= 0)
        return 2;
    return owner->mode04 != 7;
}
