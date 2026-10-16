// SLY3_CFLAGS: -Os -G0
struct ConstructedObject {
    unsigned char opaque00[0xC];
    void *vtable;
    unsigned char opaque10[0x20];
    int kind30;
    unsigned char opaque34[0x1C];
    int state50;
};
extern char D_0035C8B0[];
void *func_0021EB00(void *object);
void func_001D0BD0(void *object);
void *func_001D0B60(void *receiver)
{
    struct ConstructedObject *object = (struct ConstructedObject *)receiver;
    func_0021EB00(receiver);
    object->vtable = D_0035C8B0;
    object->kind30 = 0x5BA;
    object->state50 = -1;
    func_001D0BD0(receiver);
    return receiver;
}
