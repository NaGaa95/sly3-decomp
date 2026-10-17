// SLY3_CFLAGS: -Os -G0
struct PruneEntry { short delta,padding; void (*fn)(void *); };
struct PruneItem { unsigned char prefix[0xC]; struct PruneEntry *table; };
struct PruneOwner { unsigned char prefix[0xD0]; int count; struct PruneItem *items[8]; };
int func_00173A98(void *item);
void *func_00291F38(void *destination,void *source,int bytes);
void func_00174048(struct PruneOwner *owner,int force)
{
    int i=0;
    while(i<owner->count) {
        struct PruneItem *item=owner->items[i];
        if(force || func_00173A98(item)) {
            item->table[2].fn((char *)item+item->table[2].delta);
            func_00291F38(&owner->items[i],&owner->items[i+1],(owner->count-i)*4-4);
            owner->count--;
        } else {
            i++;
        }
    }
}
