// SLY3_CFLAGS: -Os -G0
struct StateKind { unsigned char opaque[0x128]; unsigned long flags; };
struct StateLink { unsigned char opaque[0x14]; struct StateKind *kind; };
struct StateHolder { void *owner; unsigned char opaque04[0x10]; struct StateLink *link; };
extern char D_0036C700[];
int func_001F43C8(void *owner);
void func_001854C8(void *context, int event, void *owner);
int func_0013B500(void *object, int identifier);
void func_001C2FE8(void *holder);
void func_001B7268(void *context, int kind, void *resource, void *record, float gain);
void func_001C21F0(void *holder, int state);
void func_001C3C20(void *receiver)
{
    struct StateHolder *holder = (struct StateHolder *)receiver;
    if (func_001F43C8(holder->owner) > 0) {
        func_001854C8(D_0036C700, 0xB, holder->owner);
        if (func_0013B500(holder->link->kind, 0x2F) && (holder->link->kind->flags & 2))
            func_001C2FE8(receiver);
        else
            func_001B7268((char *)holder->owner + 0x320, 0xB, 0, 0, 1.0f);
    } else {
        func_001C21F0(receiver, 9);
    }
}
