// SLY3_CFLAGS: -Os -G0
struct FlagView { unsigned char opaque[0x16EC]; int flag; };

void func_001EA9A8(void *receiver)
{
    ((struct FlagView *)receiver)->flag = 1;
}
