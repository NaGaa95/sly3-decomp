// SLY3_CFLAGS: -Os -G0
extern void *D_00370AC0;
void func_00162698(void *range,int mode);
struct RangeOwner { unsigned char prefix[0x1884]; void *actor; unsigned char gap[0x18B0-0x1888]; int mode; };
void func_00161C60(struct RangeOwner *owner,int mode)
{
    if(owner->mode!=mode) {
        if(owner->mode==0x33) func_00162698(&owner->actor,-1);
        owner->mode=mode;
        if(mode==0x33) {
            owner->actor=D_00370AC0;
            func_00162698(&owner->actor,0);
        }
    }
}
