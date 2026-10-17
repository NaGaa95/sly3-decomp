// SLY3_CFLAGS: -Os -G0
struct Target { unsigned char prefix[0xA0]; int expected; unsigned char gapA4[0x1C]; int mode; };
struct Holder { unsigned char prefix[0xD8]; struct Target *target; };
int func_0023E1F0(struct Holder *holder)
{
    struct Target *target=holder->target;
    int result=0;
    if(!target || (target->mode==3 && target->mode==target->expected))
        result=1;
    return result;
}
