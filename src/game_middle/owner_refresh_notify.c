// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short displacement; short pad; void *(*method)(void *); };
struct VirtualObject { unsigned char opaque00[0xC]; struct VirtualEntry *vtable; };
struct RefreshOwner { unsigned char opaque[0x1AEC]; struct VirtualObject *notify; };
void func_001E47F0(void *owner, int mode);
void func_001E04E8(void *owner);
void func_00152828(void *owner, void *argument);
void func_001DCE40(void *receiver, void *argument)
{
    struct RefreshOwner *owner = (struct RefreshOwner *)receiver;
    struct VirtualEntry *entry;
    func_001E47F0(receiver, 0);
    func_001E04E8(receiver);
    func_00152828(receiver, argument);
    if (owner->notify) {
        entry = owner->notify->vtable + 9;
        entry->method((char *)owner->notify + entry->displacement);
    }
}
