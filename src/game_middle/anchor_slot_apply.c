// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct VirtualEntry { short displacement; short pad; void *(*method)(void *); };
struct VirtualObject { unsigned char opaque00[0xC]; struct VirtualEntry *vtable; };
struct TransformRecord { unsigned char opaque00[0x30]; Quad position; };
struct AnchorOwner { unsigned char opaque00[0x10]; struct VirtualObject *target; unsigned char opaque14[0x1C]; char *slots; int slot; };
struct ChannelObject { unsigned char opaque00[0xC]; struct VirtualEntry *vtable; unsigned char opaque10[0xBC]; int active; };
struct ChannelObject *func_00238690(void *owner, int identity);
Quad func_001EE788(void *slot, Quad position);
void func_00132930(void *channel, Quad value);
void func_001D99E8(void *receiver)
{
    struct AnchorOwner *owner = (struct AnchorOwner *)receiver;
    struct ChannelObject *channel = func_00238690((char *)owner->target + 0x29C, 0xCB);
    struct VirtualEntry *entry;
    struct VirtualObject *target;
    struct TransformRecord *record;
    char *slot;
    channel->active = 1;
    target = owner->target;
    slot = owner->slots + (owner->slot * 32 + 0x50);
    entry = target->vtable + 36;
    record = (struct TransformRecord *)entry->method((char *)target + entry->displacement);
    func_00132930(channel, func_001EE788(slot, record->position));
    entry = channel->vtable + 8;
    entry->method((char *)channel + entry->displacement);
}
