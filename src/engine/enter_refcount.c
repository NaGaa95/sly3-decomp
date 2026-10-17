// SLY3_CFLAGS: -Os -G0
void func_0024F7C8(void *owner,int unused,int add);
void func_00156900(void *owner);
void func_001BDBB0(void *owner,int value);
struct RefOwner { unsigned char prefix[0xF60]; unsigned char sub[0x48C]; int count; };
void func_00156850(struct RefOwner *owner,int unused,int add)
{
    func_0024F7C8(owner,unused,add);
    if(add) {
        if(++owner->count==1) {
            func_00156900(owner);
            func_001BDBB0(owner->prefix+0xF60,-1);
        }
    }
}
