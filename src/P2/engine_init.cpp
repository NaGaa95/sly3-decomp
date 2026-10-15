// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" char D_003751D0[], D_00375240[];
extern "C" char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern "C" char D_004D2D60[], D_004D2E38[], D_004D2F10[];
extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" void *func_001D0B60(void *p);
extern "C" void *func_001D2080(void *p);
extern "C" void *func_0011E100(void *p, int cb, int c, int cbAlign);
extern "C" void func_002BE6A0(void *p, int flags);
extern "C" void func_002BE6C0(void *p, int flags);

extern "C" void func_001D2228(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_001D0B60(D_003751D0);
            func_001D2080(D_00375240);
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
            func_002BE6C0(D_00375240, 2);
            func_002BE6A0(D_003751D0, 2);
        }
    }
}
