// SLY3_CFLAGS: -Os -G0
struct PoolSlot { unsigned char bytes[0x11C0]; };
struct Item { unsigned char prefix[0x18]; int pool; };
extern struct PoolSlot D_0036E740[];
void func_001A9158(struct PoolSlot *slot,struct Item *item);
void func_001A9178(struct PoolSlot *slot,struct Item *item);
void func_0021DD58(struct Item *item,int attach)
{
    if(attach)
        func_001A9158(&D_0036E740[item->pool],item);
    else
        func_001A9178(&D_0036E740[item->pool],item);
}
