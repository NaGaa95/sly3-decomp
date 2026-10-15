// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "record_construct.h"
// Recovered global record followed by nested object construction.
extern "C" char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern "C" char D_004D2D60[], D_004D2E38[], D_004D2F10[];
extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" void *func_0011E100(void *p, int cb, int c, int cbAlign);
struct INITRECORD { int unk0; void *unk4; int unk8; void *unkC; };
extern "C" INITRECORD D_00389AB0;
extern "C" char D_00389D10[];
extern "C" OBJECT_WITH_NESTED_PREFIX D_00389AC0;
extern "C" char D_00345FC0[];

extern "C" void func_001DC530(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            D_00389AB0.unk0 = 2;
            D_00389AB0.unk4 = D_00345FC0;
            D_00389AB0.unk8 = 0x180;
            D_00389AB0.unkC = D_00389D10;
            func_002BE7B0(&D_00389AC0);
            if (++D_0036AE78 == 1)
                func_0011E100(D_004D2AD8, 16, 2048, 16);
            if (++D_0036AE7C == 1)
                func_0011E100(D_004D2BB0, 24, 1024, 16);
            if (++D_0036AE80 == 1)
                func_0011E100(D_004D2C88, 24, 256, 16);
            if (++D_0036AE84 == 1)
                func_0011E100(D_004D2D60, 28, 1024, 16);
            if (++D_0036AE88 == 1)
                func_0011E100(D_004D2E38, 12, 256, 16);
            if (++D_0036AE8C == 1)
                func_0011E100(D_004D2F10, 24, 256, 16);
        }
    }
}
