// SLY3_CFLAGS: -Os -G0
// Take the next free slot of a pool, construct an item of the requested kind in it (clearing the slot first), link it behind the
// previously created item, call the item's virtual method 7 and the pool owner's virtual method 92, and return the item.
struct VirtualEntry { short delta; short pad; void (*call)(void *); };
struct Item {
    unsigned char pad00[0xC]; struct VirtualEntry *vtable;
    struct Item *owner; struct Item *previous; struct Item *next;
    unsigned char pad1C[0x24 - 0x1C]; struct Item *link24;
};
struct Pool { struct Item *owner; int count; struct Item *slots[1]; };
void *func_00292034(void *destination, int value, unsigned int bytes);
int func_001158A0(void);
struct Item *func_00115238(int kind, void *storage);

struct Item *func_00238690(struct Pool *pool, int kind)
{
    struct Item *previous, *slot, *item;
    int count = pool->count;
    if (count == 0)
        previous = 0;
    else
        previous = pool->slots[count - 1];
    slot = pool->slots[count];
    pool->count = count + 1;
    func_00292034(slot, 0, func_001158A0());
    item = func_00115238(kind, slot);
    {
        register struct Item *owner __asm__("$3") = pool->owner; /* register pin: owner lives in $v1 */
        item->owner = owner;
    }
    item->previous = previous;
    if (previous) {
        previous->next = item;
        previous->link24 = 0;
    }
    item->vtable[7].call((char *)item + item->vtable[7].delta);
    pool->owner->vtable[92].call((char *)pool->owner + pool->owner->vtable[92].delta);
    return item;
}
