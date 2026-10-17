// SLY3_CFLAGS: -Os -G0
int func_0017E208(void *game,int flags,int key,int context,int capacity,int *ids);
void func_00226050(void *receiver);
void func_0025BD68(void *game)
{
    int ids[0x400];
    int count=func_0017E208(game,0x405,0x87,0,0x400,ids);
    int i;
    for(i=0;i<count;i++)
        func_00226050((void *)ids[i]);
}
