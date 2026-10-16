// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int ComponentTickPosition __attribute__((mode(TI)));
struct ComponentTickOwner {
    char unused00[0x120];
    unsigned long flags;
};
struct ComponentTickInput {
    char unused00[0x40];
    void *object;
    char unused44[8];
    struct ComponentTickOwner *owner;
    char unused50[0x10];
    ComponentTickPosition position;
};
struct ComponentTickActor {
    char unused00[0x218];
    struct ComponentTickInput *input;
    char unused21C[0x1164 - 0x21C];
    int disabled;
    char unused1168[0x13E4 - 0x1168];
    int blocked;
    char unused13E8[0x1470 - 0x13E8];
    int state;
};
int func_001BADC0(void *);
void func_001C0F18(void *, void *, ComponentTickPosition);
void func_001B5A90(void *);

void func_001E96E8(struct ComponentTickActor *actor)
{
    if (actor->blocked)
        return;
    switch (actor->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
        if (func_001BADC0(actor)) {
            struct ComponentTickInput *input = actor->input;
            if (!(input->owner->flags & (1UL << 61)) && !actor->disabled)
                func_001C0F18((char *)actor + 0xA20, input->object, input->position);
        }
        break;
    case 5:
        func_001B5A90((char *)actor + 0x500);
        break;
    case 4:
    case 6:
    case 8:
        break;
    }
}
