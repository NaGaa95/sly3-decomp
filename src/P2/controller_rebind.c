// SLY3_CFLAGS: -Os -G0
struct Player {
    char storage[0x11C0];
};
extern struct Player D_0036E740[];
struct Method {
    short delta;
    short pad;
    void (*call)(void *);
};
struct Child {
    unsigned char prefix[0xC];
    struct Method *methods;
};
struct Actor {
    unsigned char prefix[0x130];
    int controller;
    unsigned char gap134[0x140 - 0x134];
    void *counter;
    unsigned char gap144[0x168 - 0x144];
    struct Child *child;
};
void func_001A91B8(void *, void *);
void func_001A9198(void *, void *);
void func_001F4E48(void *);
void func_001F4E20(void *);
void func_001F4548(struct Actor *actor, int controller)
{
    int old = actor->controller;
    if (controller == old)
        return;
    if (old != -1) {
        func_001A91B8(&D_0036E740[old], actor);
        func_001F4E48(actor->counter);
        if (actor->child)
            actor->child->methods[54].call((char *)actor->child + actor->child->methods[54].delta);
    }
    actor->controller = controller;
    if (controller != -1) {
        func_001A9198(&D_0036E740[controller], actor);
        func_001F4E20(actor->counter);
        if (actor->child)
            actor->child->methods[56].call((char *)actor->child + actor->child->methods[56].delta);
    }
}
