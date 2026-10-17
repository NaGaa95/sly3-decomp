// SLY3_CFLAGS: -Os -G0
typedef int Vec128 __attribute__((mode(TI)));
extern Vec128 D_0031FC80, D_0031FC90;
void *func_001F4A80(void *owner);
Vec128 func_00212FA0(void *arg, void *controller, Vec128 first, Vec128 second, int flag);
struct ValueOwner { unsigned char prefix[0x1910]; Vec128 value; };
void func_0013EB08(struct ValueOwner *owner, void *arg)
{
    owner->value = func_00212FA0(arg, func_001F4A80(owner), D_0031FC80, D_0031FC90, 0);
}
