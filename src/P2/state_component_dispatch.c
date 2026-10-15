// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef unsigned int FLAGS64 __attribute__((mode(DI)));
typedef int QWORD __attribute__((mode(TI)));
struct FlagsOwner {
    char prefix[0x120];
    FLAGS64 flags;
};
struct Component {
    char prefix[0x40];
    void *object;
    char gap44[8];
    struct FlagsOwner *owner;
    char gap50[0x10];
    QWORD position;
};
struct Receiver {
    char prefix[0x218];
    struct Component *component;
    char to_flag[0x1164 - 0x21C];
    int flag1164;
    char to_disabled[0x13E4 - 0x1168];
    int disabled;
    char to_state[0x1470 - 0x13E8];
    int state;
};
int func_001BADC0(void *receiver);
void func_001C0F18(void *context, void *object, QWORD position);
void func_001B5A90(void *context);

void func_001F02D8(void *receiver)
{
    struct Receiver *p = (struct Receiver *)receiver;
    if (p->disabled)
        return;
    switch (p->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 8:
    case 10:
        if (func_001BADC0(p)) {
            struct Component *component = p->component;
            if (!(component->owner->flags & ((FLAGS64)1 << 61)) && !p->flag1164)
                func_001C0F18((char *)p + 0xA20, component->object, component->position);
        }
        break;
    case 6:
        func_001B5A90((char *)p + 0x500);
        break;
    }
}
