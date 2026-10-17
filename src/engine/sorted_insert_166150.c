// SLY3_CFLAGS: -Os -G0
struct ListItem { unsigned char prefix[0x124]; int key; };
struct ListOwner { unsigned char prefix[0xE8]; int count; struct ListItem *items[7]; };
void *func_00291F38(void *destination, void *source, int bytes);
static inline void MoveUp(void *destination, void *source, int bytes)
{
    func_00291F38(destination, source, bytes);
}

void func_00166150(struct ListOwner *owner, struct ListItem *item)
{
    int i;
    for(i = 0; i < owner->count; i++) {
        struct ListItem *other = owner->items[i];
        if(other == item) return;
        if(other->key < item->key) break;
    }
    if(owner->count >= 0 && owner->count < 7) {
        MoveUp(&owner->items[i + 1], &owner->items[i], (owner->count - i) * 4);
        owner->items[i] = item;
        owner->count++;
    }
}
