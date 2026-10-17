// SLY3_CFLAGS: -Os -G0
struct Method {
    short delta;
    short unused;
    void (*call)(void *);
};
struct Component {
    unsigned char prefix[0xC];
    struct Method *methods;
};
struct Owner {
    unsigned char prefix[0x48];
    int selector;
    unsigned char gap[0x144 - 0x4C];
    struct Component *child;
};
extern char D_00475480[];
void func_0023C580(void *);
struct Component *func_0017E5D8(void *, int, int, void *);
void func_0028F068(void *, int, int);
void func_001F6728(struct Owner *owner)
{
    struct Component *child;
    func_0023C580(owner);
    child = func_0017E5D8(D_00475480, 1, 0x11, owner);
    owner->child = child;
    if (child)
        child->methods[9].call((char *)child + child->methods[9].delta);
    func_0028F068(owner, owner->selector, 2);
}
