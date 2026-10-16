// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct O;
struct S;
struct OwnerInitializeView {
    char prefix[0x3C];
    unsigned int tagged_flags;
    char opaque40[0x128 - 0x40];
    unsigned long flags;
    int key;
    char list[12];
};
extern "C" {
void func_0023AE08(void *receiver);
void func_0011AF38(void *list, int link_offset);
void func_001C9118(O *receiver, int state);
void func_0023B6A0(void *receiver);
void func_0023FC90(S *receiver, unsigned int enabled);
}
typedef char OwnerInitializeLongIs64[(sizeof(unsigned long) == 8) ? 1 : -1];
extern "C" void func_0020B0C0(void *receiver)
{
    OwnerInitializeView *owner = static_cast<OwnerInitializeView *>(receiver);
    func_0023AE08(receiver);
    func_0011AF38(owner->list, 8);
    func_001C9118(static_cast<O *>(receiver), 1);
    unsigned int flags = owner->tagged_flags;
    if ((flags ^ 1) & 1) {
        unsigned int *storage = reinterpret_cast<unsigned int *>(flags);
        *storage = (*storage & 1) | 0xE;
    } else {
        owner->tagged_flags = (flags & 1) | 0xE;
    }
    owner->flags &= ~8UL;
    if (owner->key == 1) {
        func_0023B6A0(receiver);
        func_0023FC90(static_cast<S *>(receiver), 1);
    }
}
