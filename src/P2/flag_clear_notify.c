// SLY3_CFLAGS: -Os -G0
struct Method {
    short delta;
    short unused;
    void (*call)(void *, int, void *);
};
struct Object {
    unsigned char prefix[0xC];
    struct Method *methods;
    unsigned char gap[0x28 - 0x10];
    unsigned long flags;
};
void func_001FCAC8(struct Object *object)
{
    object->flags &= ~(1UL << 59);
    object->methods[4].call((char *)object + object->methods[4].delta, 3, object);
}
