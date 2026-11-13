// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Rolls the reward of an actor: a pending item is kept unless its object is gone, otherwise a weighted pick from the
// table of the current level (or nothing), then a random amount (table min..max) is split over 2-3 item slots.
struct RewardItem { int kind, flags, key, count; };
struct RewardPick { int weight, key; };
struct RewardTable { int minimum, maximum; float chance; RewardPick picks[6]; };
struct RewardObject { char unknown00[0x1A0]; void *subject; };
struct RewardActor {
    char unknown00[0x2F0]; int category;
    char unknown2F4[0x414 - 0x2F4]; RewardItem items[8]; int count;
    char unknown498[8]; int busy, pending, unknown4A8; void *owner;
};
extern "C" {
extern char D_00475480[];
extern RewardTable D_00346D50[], D_00346B30[];
void func_001F2950(void *owner);
int func_0025E188(void);
void *func_00292034(void *destination, int value, unsigned int size);
RewardObject *func_0017E1B8(void *game, int kind, int key, void *owner);
int func_0013B500(void *object, int kind);
int func_00188A38(void *subject);
float func_0011E940(float low, float high);
int func_0011E8F0(int low, int high);
}
extern "C" void func_001F1A30(RewardActor *actor)
{
    RewardTable *table;
    RewardItem reward;
    int id, total, remaining, slots, j;
    unsigned int i;
    actor->pending = 0;
    func_001F2950(actor->owner);
    if (actor->busy)
        return;
    id = func_0025E188();
    if (id == -1)
        id = 3;
    switch (actor->category) {
    case 1:
    case 2:
        table = &D_00346D50[id];
        break;
    default:
        table = &D_00346B30[id];
        break;
    }
    func_00292034(&reward, 0, sizeof(reward));
    if (actor->count > 0) {
        RewardObject *object = func_0017E1B8(D_00475480, 4, actor->items[0].kind, actor->owner);
        if (object && func_0013B500(object, 0x68) && object->subject && func_00188A38(object->subject))
            actor->count = 0;
    }
    if (actor->count > 0) {
        reward = actor->items[0];
    } else if (func_0011E940(0.0f, 1.0f) > table->chance) {
        reward.key = -1;
        reward.kind = -1;
    } else {
        int draw;
        total = 0;
        for (i = 0; i < 6; i++)
            total += table->picks[i].weight;
        draw = func_0011E8F0(0, total - 1);
        for (i = 0; i < 6; i++) {
            RewardPick *pick = &table->picks[i];
            if (draw < pick->weight) {
                reward.key = pick->key;
                break;
            }
            draw -= pick->weight;
        }
        reward.count = 1;
        reward.kind = 0x30C;
    }
    actor->count = 0;
    remaining = func_0011E8F0(table->minimum, table->maximum);
    slots = func_0011E8F0(2, 3);
    /* rotated counting loop: the entry test reads j (folded to 0 by cse) rather than testing slots directly */
    j = 0;
    if (j < slots) do {
        RewardItem *item = &actor->items[actor->count++];
        int amount;
        item->kind = 0x30A;
        item->flags = 0;
        amount = remaining / (slots - j);
        if (amount < 1)
            amount = 1;
        remaining -= amount;
        item->count = amount;
        if (!remaining)
            break;
        j++;
    } while (j < slots);
    if (reward.count > 0)
        actor->items[actor->count++] = reward;
}
