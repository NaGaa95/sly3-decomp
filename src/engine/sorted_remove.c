// SLY3_CFLAGS: -Os -G0
struct RemoveGame { unsigned char prefix[0x3EB4]; int counter; int count; int items[8]; };
extern struct RemoveGame D_00475480;
int func_00165B48(struct RemoveGame *game,int item);
void *func_001D2898(void *destination,void *source,int bytes);
void func_00165B88(struct RemoveGame *game);
void func_0015AF48(struct RemoveGame *game);
void func_00165D40(struct RemoveGame *game,int item)
{
    int i=func_00165B48(game,item);
    func_001D2898(&D_00475480.items[i],&D_00475480.items[i+1],(D_00475480.count-i-1)*4);
    D_00475480.count--;
    game->counter++;
    func_00165B88(game);
    func_0015AF48(game);
}
