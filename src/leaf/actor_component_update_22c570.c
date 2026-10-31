// SLY3_CFLAGS: -Os -G0
// SLY3_AS: gnu-2.9
// Per-frame component update of an actor (sibling of func_001E0B48): depending on the state the active or the linked actor feeds its
// component position into the actor component list unless the owner flag bit 61 or the gate blocks it.
typedef unsigned int ComponentFlags __attribute__((mode(DI)));
typedef int ComponentPosition __attribute__((mode(TI)));
struct ComponentFlagOwner { char prefix[0x120]; ComponentFlags flags; };
struct ActorComponent {
    char prefix[0x40]; void *object; char gap44[8]; struct ComponentFlagOwner *owner; char gap50[0x10]; ComponentPosition position;
};
struct ComponentActor;
struct ActorLink { char prefix[0x14]; struct ComponentActor **target; };
struct ComponentActor {
    char prefix[0x218]; struct ActorComponent *component;
    char gap21C[0x1164 - 0x21C]; int gate1164;
    char gap1168[0x13E4 - 0x1168]; int disabled;
    char gap13E8[0x1470 - 0x13E8]; int state;
    char gap1474[0x15E0 - 0x1474]; struct ActorLink *link;
};
int func_001BADC0(void *receiver);
int func_0013B500(void *object, int identifier);
void func_001C0F18(void *context, void *object, ComponentPosition position);
void func_001B5A90(void *context);
void func_0022C570(struct ComponentActor *p)
{
    if (p->disabled)
        return;
    switch (p->state) {
    case 0: case 1: case 2: case 7:
        if (func_001BADC0(p)) {
            struct ActorComponent *component = p->component;
            if (!(component->owner->flags & ((ComponentFlags)1 << 61)) && !p->gate1164)
                func_001C0F18((char *)p + 0xA20, component->object, component->position);
        }
        break;
    case 4:
        func_001B5A90((char *)p + 0x500);
        break;
    case 6:
        if (func_0013B500(*p->link->target, 0x32)) {
            struct ComponentActor *target = *p->link->target;
            if (func_001BADC0(target)) {
                struct ActorComponent *component = target->component;
                if (!(component->owner->flags & ((ComponentFlags)1 << 61)))
                    func_001C0F18((char *)p + 0xA20, component->object, component->position);
            }
        }
        break;
    case 3: case 5: case 8:
    default:
        break;
    }
}
