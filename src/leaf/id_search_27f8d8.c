// SLY3_CFLAGS: -Os -G0
struct Item { unsigned char prefix[0x18]; int id; unsigned char gap1C[0x140]; int extraCount; int extraIds[1]; };
int func_0017E208(void *game,int flags,int key,void *owner,int limit,struct Item **items);
struct Item *func_0027F8D8(void *game,int id)
{
    struct Item *items[64];
    struct Item *found=0;
    int count=func_0017E208(game,0x405,0x28,0,0x40,items);
    int i;
    for(i=0;i<count;i++) {
        struct Item *item=items[i];
        int j;
        if(item->id==id) {
            found=item;
            continue;
        }
        for(j=0;j<item->extraCount;j++)
            if(item->extraIds[j]==id)
                goto hit;
        continue;
    hit:
        found=item;
    }
    return found;
}
