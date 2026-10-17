// SLY3_CFLAGS: -Os -G0
typedef int Vector128 __attribute__((mode(TI)));
struct Method {
    short delta;
    short unused;
    void (*call)(void *, void *);
};
struct Owner {
    unsigned char prefix[0xC];
    struct Method *methods;
    unsigned char gap[0x158 - 0x10];
    unsigned char list[1];
};
struct Attachment {
    Vector128 position;
    unsigned char gap[0x50];
    struct Owner *owner;
};
void func_0011AF60(void *, void *);
void func_001F3CB8(struct Owner *owner, struct Attachment *attachment)
{
    struct {
        Vector128 position;
        unsigned char rest[0x70];
    } frame;
    attachment->owner = owner;
    func_0011AF60(owner->list, attachment);
    owner->methods[85].call((char *)owner + owner->methods[85].delta, &frame);
    attachment->position = frame.position;
}
