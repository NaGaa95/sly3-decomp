// SLY3_CFLAGS: -Os -G0
typedef unsigned int ComponentFlags __attribute__((mode(DI)));
typedef int ComponentPosition __attribute__((mode(TI)));

struct ComponentFlagOwner {
    char prefix[0x120];
    ComponentFlags flags;
};

struct ActorComponent {
    char prefix[0x40];
    void *object;
    char gap44[8];
    struct ComponentFlagOwner *owner;
    char gap50[0x10];
    ComponentPosition position;
};

struct AlternateComponent {
    void *object;
    char gap04[8];
    struct ComponentFlagOwner *owner;
    char gap10[0x10];
    ComponentPosition position;
    char gap30[0x10];
};

struct ComponentActor {
    char prefix[0x218];
    struct ActorComponent *component;
    char gap21C[0x1164 - 0x21C];
    int gate1164;
    char gap1168[0x13E4 - 0x1168];
    int disabled;
    char gap13E8[0x1520 - 0x13E8];
    int state;
    char gap1524[0x1B00 - 0x1524];
    struct AlternateComponent *alternates;
    int selected;
};

int func_001BADC0(void *receiver);
void func_001C0F18(void *context, void *object, ComponentPosition position);
void func_001B5A90(void *context);
void func_001BFA80(void *context);

void func_001E0B48(struct ComponentActor *p)
{
    if (p->disabled)
        return;
    switch (p->state) {
    case 0: case 1: case 4: case 5: case 7:
    case 8: case 9: case 10: case 11: case 19:
        if (func_001BADC0(p)) {
            struct ActorComponent *component = p->component;
            if (!(component->owner->flags & ((ComponentFlags)1 << 61)) && !p->gate1164)
                func_001C0F18((char *)p + 0xA20, component->object, component->position);
        }
        break;
    case 22:
        if (p->alternates) {
            struct AlternateComponent *component = p->alternates + (1 - p->selected);
            if (!(component->owner->flags & ((ComponentFlags)1 << 61)) && !p->gate1164)
                func_001C0F18((char *)p + 0xA20, component->object, component->position);
        }
        break;
    case 14:
        func_001B5A90((char *)p + 0x500);
        break;
    case 21:
        func_001BFA80((char *)p + 0x1010);
        break;
    case 2: case 3: case 6: case 12: case 13: case 15:
    case 16: case 17: case 18: case 20: case 23:
    default:
        break;
    }
}
