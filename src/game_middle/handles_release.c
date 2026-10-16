// SLY3_CFLAGS: -Os -G0
struct HandleOwner {
    unsigned char opaque00[0x3C];
    int handle3C;
    unsigned char opaque40[4];
    void *object44;
    unsigned char opaque48[8];
    int handle50;
};
void func_00296DB8(int handle);
void func_002A1170(void);
void func_00118C30(void *owner);
void func_001A30A8(void *receiver)
{
    struct HandleOwner *owner = (struct HandleOwner *)receiver;
    if (owner->handle3C >= 0) {
        func_00296DB8(owner->handle3C);
        owner->handle3C = -1;
    }
    if (owner->handle50 >= 0) {
        if (owner->object44)
            func_002A1170();
        owner->handle50 = -1;
    }
    func_00118C30(receiver);
}
