// SLY3_CFLAGS: -Os -G0
void func_0013C780(void *self);
void func_0013C7D0(void *self);
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver,int flags);
void func_0013C9D0(void *self,int *count,int *items,int capacity);
void func_0013CBD8(void *self);
void func_0013CC90(void *self,int count,int *items);
void func_0013C958(void *self)
{
    int items[0x300];
    void *frame;
    int count;
    func_0013C780(self);
    func_0013C7D0(self);
    func_001D2770(&frame);
    func_0013C9D0(self,&count,items,0x300);
    func_0013CBD8(self);
    func_0013CC90(self,count,items);
    func_001D2798(&frame,2);
}
