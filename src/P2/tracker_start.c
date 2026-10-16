// SLY3_CFLAGS: -Os -G0
struct Tracker { unsigned char prefix[0x45C]; int handle; int param460; float param464; int param468; int param46C; unsigned char block470[1]; };
extern char D_00475480[];
void *func_0017E1B8(void *game,int flags,int key,void *context);
void func_0014B590(void *object,void *handle,int a,int b,float c,void *block,int d);
void func_002194B0(struct Tracker *tracker)
{
    void *handle;
    if(tracker->handle==-1)
        return;
    handle=func_0017E1B8(D_00475480,4,tracker->handle,tracker);
    func_0014B590(tracker,handle,tracker->param460,tracker->param46C,tracker->param464,tracker->block470,tracker->param468);
}
