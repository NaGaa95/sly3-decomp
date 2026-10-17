// SLY3_CFLAGS: -Os -G0
struct TimerSelf { unsigned char prefix[0x10]; void *owner; unsigned char gap14[0x38-0x14]; void *value; float stamp; };
extern float D_0036BB98;
void func_00238978(void);
void func_002541F8(void *owner,void *value);
int func_00257F20(void *owner);
void func_00134860(void *self,int flag);
void func_00135288(void *self);
void func_001344D8(struct TimerSelf *self)
{
    func_00238978();
    func_002541F8(self->owner,self->value);
    if(func_00257F20(self->owner)) func_00134860(self,1);
    else func_00134860(self,0);
    func_00135288(self);
    self->stamp=D_0036BB98;
}
