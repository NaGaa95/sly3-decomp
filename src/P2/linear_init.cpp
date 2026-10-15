// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "heap.h"
extern "C" char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern "C" char D_004D2D60[], D_004D2E38[], D_004D2F10[];
extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" void *func_0011E100(void *p, int cb, int c, int cbAlign);
extern "C" CLinearHeap D_004C4080;
extern "C" unsigned char D_004C4110[];
extern "C" char D_004C4090[];
inline void *operator new(unsigned int cb, void *pv) { return pv; }
extern "C" void func_00288BA8(void * arg0);
extern "C" void func_002C01F8(void * arg0, int arg1);

extern "C" void func_002894C8(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            new (&D_004C4080) CLinearHeap(24, D_004C4110);
            func_00288BA8(D_004C4090);
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
        else
        {
            func_002C01F8(D_004C4090, 2);
        }
    }
}
