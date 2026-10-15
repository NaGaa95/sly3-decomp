// SLY3_CFLAGS: -Os -G0
typedef unsigned int ActorComponentMask __attribute__((mode(DI)));
typedef int ActorComponentPosition __attribute__((mode(TI)));
struct ActorComponentFlagView { char prefix[0x120]; ActorComponentMask flags; };
struct ActorComponentView {
    char prefix[0x40]; void *object; char unused44[8];
    struct ActorComponentFlagView *owner; char unused50[0x10];
    ActorComponentPosition position;
};
struct ActorComponentReceiver {
    char prefix[0x218]; struct ActorComponentView *component;
    char unused21C[0x1164-0x21C]; int gate;
    char unused1168[0x13E4-0x1168]; int disabled;
    char unused13E8[0x1520-0x13E8]; int state;
};
int func_001BADC0(void *receiver);
void func_001C0F18(void *context,void *object,ActorComponentPosition position);
void func_001B5A90(void *context);
void func_0013F300(struct ActorComponentReceiver *receiver)
{
    if(receiver->disabled) return;
    switch(receiver->state) {
    case 0: case 1: case 5: case 6: case 7: case 8: case 9:
    case 13: case 14: case 15: case 16: case 17: case 18:
        if(func_001BADC0(receiver)) {
            struct ActorComponentView *component=receiver->component;
            if(!(component->owner->flags&((ActorComponentMask)1<<61)) && !receiver->gate)
                func_001C0F18((char *)receiver+0xA20,component->object,component->position);
        }
        break;
    case 3: func_001B5A90((char *)receiver+0x500); break;
    }
}
