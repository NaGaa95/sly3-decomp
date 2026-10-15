// SLY3_CFLAGS: -Os -G0
typedef unsigned int StateComponentFlags __attribute__((mode(DI)));
typedef int StateComponentPosition __attribute__((mode(TI)));

struct StateFlagOwner {
    char prefix[0x120];
    StateComponentFlags flags;
};

struct StatePackedComponent {
    char prefix[0x40];
    void *object;
    char gap44[8];
    struct StateFlagOwner *owner;
    char gap50[0x10];
    StateComponentPosition position;
};

struct StateScalarResource {
    char prefix[0xF8];
    int active;
};

struct StateDispatchActor {
    char prefix[0x218];
    struct StatePackedComponent *component;
    char gap21C[0x1164 - 0x21C];
    int gate1164;
    char gap1168[0x13E4 - 0x1168];
    int disabled;
    char gap13E8[0x19E0 - 0x13E8];
    int state;
    char gap19E4[0x10];
    struct StateScalarResource *resource;
};

int func_001BADC0(void *receiver);
void func_001C0F18(void *context, void *object, StateComponentPosition position);
void func_001C0DA8(void *context, void *resource, float value);
void func_001B5A90(void *context);
void func_001BFA80(void *context);

void func_001C0CB8(struct StateDispatchActor *p)
{
    if (p->disabled)
        return;
    switch (p->state) {
    case 0: case 1: case 2: case 6: case 7: case 10: case 11: case 12:
    case 13: case 16: case 18: case 19: case 21: case 22: case 23: case 24:
        if (func_001BADC0(p)) {
            struct StatePackedComponent *component = p->component;
            if (!(component->owner->flags & ((StateComponentFlags)1 << 61)) && !p->gate1164)
                func_001C0F18((char *)p + 0xA20, component->object, component->position);
        }
        break;
    case 4: case 17:
    {
        struct StateScalarResource *resource = p->resource;
        if (!resource->active)
            func_001C0DA8((char *)p + 0xA20, resource ? (char *)resource + 0xEC : 0, 0.0f);
        break;
    }
    case 8:
        func_001B5A90((char *)p + 0x500);
        break;
    case 9:
        func_001BFA80((char *)p + 0x1010);
        break;
    default:
        break;
    }
}
