// SLY3_CFLAGS: -Os -G0
void func_001F3BF8(void *self);
void func_001F4670(void *self,int value);
void func_0028F068(void *self,int value,int mode);
void func_0019BF70(void *self);
void func_0019B968(void *self,int value,void *extra);
void func_0019C048(char *self)
{
    func_001F3BF8(self);
    func_001F4670(self,1);
    func_0028F068(self,*(int *)(self+0x48),2);
    func_0028F068(self,*(int *)(self+0x4C),2);
    func_0019BF70(self);
    func_0019B968(self,7,self+0x1F8);
}
