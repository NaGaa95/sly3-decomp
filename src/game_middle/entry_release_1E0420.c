// SLY3_CFLAGS: -Os -G0
typedef int PackedVector __attribute__((mode(TI)));
struct VirtualEntry { short adjustment, reserved; void *function; };
struct EntryOwner {
    unsigned char prefix[0xC];
    struct VirtualEntry *methods;
    unsigned char gap10[0x28 - 0x10];
    unsigned long flags;
};
struct PendingEntry {
    unsigned char prefix[0x190];
    struct EntryOwner *owner;
};
struct ReleaseActor {
    unsigned char prefix[0x1540];
    struct PendingEntry *entry;
};
extern PackedVector D_00324680, D_00317560;
void func_001E0660(void *actor);
int func_0013B500(void *object, int kind);
void func_00255A40(void *object);
PackedVector func_001C94E8(void *source, void *destination, PackedVector direction);
void func_00241150(void *object, int state);

void func_001E0420(struct ReleaseActor *actor)
{
    struct EntryOwner *owner;
    PackedVector direction;
    func_001E0660(actor);
    owner = actor->entry->owner;
    actor->entry = 0;
    if ((int)(owner->flags >> 56) & 1) {
        if (func_0013B500(owner, 0x3A))
            func_00255A40(owner);
        direction = func_001C94E8(actor, 0, D_00324680);
        ((void (*)(void *, PackedVector))owner->methods[40].function)(
            (char *)owner + owner->methods[40].adjustment, direction);
        ((void (*)(void *, PackedVector))owner->methods[41].function)(
            (char *)owner + owner->methods[41].adjustment, D_00317560);
        func_00241150(owner, 3);
    }
}
