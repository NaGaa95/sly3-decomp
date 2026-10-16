// SLY3_CFLAGS: -Os -G0
struct SlotOwner {
    unsigned char opaque00[0x194];
    int key194;
    void *slot198;
    int key19C;
    void *slot1A0;
    int key1A4;
    unsigned char opaque1A8[0];
};
extern char D_00475480[];
void func_001A1E58(void *owner);
void *func_0017E1B8(void *game, int kind, int key, void *context);
void func_001A2228(void *receiver)
{
    struct SlotOwner *owner = (struct SlotOwner *)receiver;
    func_001A1E58(receiver);
    owner->slot198 = func_0017E1B8(D_00475480, 4, owner->key194, receiver);
    owner->slot1A0 = func_0017E1B8(D_00475480, 4, owner->key19C, receiver);
    *(void **)((char *)receiver + 0x1A8) = func_0017E1B8(D_00475480, 4, owner->key1A4, receiver);
}
