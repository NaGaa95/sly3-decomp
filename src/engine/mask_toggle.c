// SLY3_CFLAGS: -Os -G0
struct EngineMaskOwner { unsigned char prefix[0x1444]; int enabled; };
void func_00240E58(void *receiver,unsigned int mask,int value);
void func_00156A08(struct EngineMaskOwner *owner,int enabled)
{
    owner->enabled=enabled;
    if(enabled) func_00240E58(owner,0x03FFFFFF,2);
    else {
        func_00240E58(owner,0x03FFFFFF,0);
        func_00240E58(owner,0x0010FF00,2);
    }
}
