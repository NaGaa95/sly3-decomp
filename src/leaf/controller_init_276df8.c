// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Controller { unsigned char prefix[0x3C]; unsigned int tagged; unsigned char gap40[0xF0]; int first; unsigned char gap134[4]; int second; unsigned char gap13C[0x14]; float range; unsigned char gap154[4]; int count; };
void func_0023AE08(struct Controller *controller);
void func_00240E58(struct Controller *controller,unsigned int mask,int value);
void func_00276DF8(struct Controller *controller)
{
    unsigned int value;
    func_0023AE08(controller);
    controller->count=10;
    controller->range=3000.0f;
    func_00240E58(controller,0x03FFFFFF,2);
    value=controller->tagged;
    controller->second=-1;
    controller->first=-1;
    if((value^1)&1)
        *(unsigned int *)value|=6;
    else
        controller->tagged=value|6;
}
