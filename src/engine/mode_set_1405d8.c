// SLY3_CFLAGS: -Os -G0
struct Owner { unsigned char prefix[0x4B0]; int mode; };
void func_001546B8(void *owner);
int func_0021F410(int identity);
void func_001405D8(struct Owner *owner)
{
    func_001546B8(owner);
    if(func_0021F410(11)) owner->mode=3;
    else owner->mode=1;
}
