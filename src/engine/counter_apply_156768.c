// SLY3_CFLAGS: -Os -G0
extern char D_004BC230[];
int func_001F43C8(void *self);
int func_001F43F0(void *self);
void func_001F43D0(void *self,int value);
int func_001F4458(void *self);
void func_001F4438(void *self,int value);
int func_00284828(void *context,void *self,int value);
void func_00156768(void *self,int force)
{
    if(func_001F43C8(self) && !force) return;
    func_001F43D0(self,func_00284828(D_004BC230,self,func_001F43F0(self)));
    func_001F4438(self,func_001F4458(self));
}
