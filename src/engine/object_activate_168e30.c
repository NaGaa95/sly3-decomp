// SLY3_CFLAGS: -Os -G0
struct ActivateEntry { short delta, unused; void (*invoke)(void *); };
struct ActiveObject { char prefix[0xC]; struct ActivateEntry *vtable; char pad10[0x14C-0x10]; int enabled, visible; };
struct ActivationOwner { char prefix[0x324]; unsigned int count; struct ActiveObject *objects[4]; };
void func_00168E30(struct ActivationOwner *owner, struct ActiveObject *object)
{
    if(object) {
        if(owner->count < 4) owner->objects[owner->count++] = object;
        object->enabled = object->visible = 1;
        object->vtable[9].invoke((char *)object + object->vtable[9].delta);
    }
}
