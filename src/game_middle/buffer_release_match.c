// SLY3_CFLAGS: -Os -G0
struct BufferEntry { unsigned char opaque00[8]; void *key; unsigned char opaque0C[0x34]; };
struct BufferOwner { unsigned char opaque00[0x1B00]; struct BufferEntry *current; int index; };
void func_0024F068(void *owner, void *key);
void func_001E1D88(void *receiver, void *key)
{
    struct BufferOwner *owner = (struct BufferOwner *)receiver;
    func_0024F068(receiver, key);
    if (owner->current) {
        struct BufferEntry *other = &owner->current[1 - owner->index];
        if (other->key == key)
            owner->current = 0;
    }
}
