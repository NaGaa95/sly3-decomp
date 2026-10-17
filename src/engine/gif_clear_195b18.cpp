// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"

extern long D_0036DC10[];
extern int D_0036DC90;
extern QW D_0036E630[], D_0036E650[];
extern "C" void func_00195B18(void)
{
    ulong current = D_0036DC10[D_0036DC90];
    ulong other = D_0036DC10[1 - D_0036DC90];
    GIFS first;
    first.AllocStatic(2, D_0036E630);
    first.AddPrimPack(0, 1, 0xE);
    first.PackAD(7, ((long)(int)(other & 0x1FF) << 5) | (((other >> 16) & 0x3F) << 14) | 0x6A8000000);
    first.AddPrimEnd();
    GIFS second;
    second.AllocStatic(2, D_0036E650);
    second.AddPrimPack(0, 1, 0xE);
    second.PackAD(7, ((long)(int)(current & 0x1FF) << 5) | (((current >> 16) & 0x3F) << 14) | 0x6A8000000);
    second.AddPrimEnd();
}
