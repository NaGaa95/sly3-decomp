// SLY3_CFLAGS: -Os -G0
struct EngineFlagOwner { unsigned char prefix[0x1D4]; float value; };
extern unsigned char D_00475480[];
void func_0019F5F8(void *game,void *owner);
void func_0023BBE0(void *owner);
void func_0019BB00(void *owner,int a,int b);
void func_0019B600(struct EngineFlagOwner *owner)
{
    int active=owner->value!=0.0f;
    if(active) func_0019F5F8(D_00475480,owner);
    func_0023BBE0(owner);
    func_0019BB00(owner,0,0);
}
