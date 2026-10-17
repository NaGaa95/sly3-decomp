// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void *func_0017E5D8(void *game,int flags,int key,int context);
int func_002796A0(void *object);
void *func_00279C28(void)
{
    void *object=func_0017E5D8(D_00475480,5,0x99,0);
    if(!object||!func_002796A0(object))
        return 0;
    return object;
}
