// SLY3_CFLAGS: -Os -G0
struct EntryOwner {
    unsigned char prefix[0x28];
    unsigned long flags;
};
struct PendingEntry {
    unsigned char prefix[0x190];
    struct EntryOwner *owner;
};
struct StateActor {
    unsigned char prefix0[0x113C];
    void *animation;
    unsigned char gap1140[0x1540 - 0x1140];
    struct PendingEntry *entry;
    unsigned char gap1544[0x1584 - 0x1544];
    int pending;
    unsigned char gap1588[4];
    int state;
};
int func_00138AC8(void *animation);
void func_001DE690(void *actor, int state);

void func_001E1DE0(struct StateActor *actor)
{
    int state;
    for (;;) {
        state = actor->state;
        switch (state) {
        case 0:
            break;
        case 1:
            if (actor->pending) {
                if (!actor->entry) {
                    func_001DE690(actor, 0);
                } else if (!((int)(actor->entry->owner->flags >> 56) & 1)) {
                    func_001DE690(actor, 0);
                    actor->entry = 0;
                }
            }
            break;
        case 2:
            if (func_00138AC8(actor->animation))
                func_001DE690(actor, 5);
            break;
        }
        if (actor->state == state || actor->state == -1)
            break;
    }
}
