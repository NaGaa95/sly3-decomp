// SLY3_CFLAGS: -Os -G0
struct Item { unsigned char prefix[0x28]; int pending; unsigned char gap2C[0x28]; };
struct Manager { unsigned char prefix[0x694]; int index; struct Item items[1]; };
void func_0028AD48(struct Manager *manager,struct Item *item,int mode);
struct Item *func_0028AFC0(struct Manager *manager,int drain)
{
    struct Item *item=&manager->items[manager->index];
    if(drain==1) {
        while(item->pending)
            func_0028AD48(manager,item,0);
    }
    return item;
}
