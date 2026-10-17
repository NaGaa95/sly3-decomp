// SLY3_CFLAGS: -Os -G0
void func_001F48F8(void);
int func_0013B500(void *object,int kind);
int func_001F4430(void *self);
void func_001F4438(void *self,int value);
struct ShiftOther { unsigned char prefix[0x1A8]; int offset; };
void func_00141810(void *self,struct ShiftOther *other)
{
    func_001F48F8();
    if(func_0013B500(other,0x6B)) func_001F4438(self,func_001F4430(self)+other->offset);
}
