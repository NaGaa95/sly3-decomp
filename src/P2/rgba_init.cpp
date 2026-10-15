// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Sixteen RGBA defaults and two global object constructions recovered from the original.
extern "C" char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern "C" char D_004D2D60[], D_004D2E38[], D_004D2F10[];
extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" void *func_0011E100(void *p, int cb, int c, int cbAlign);
extern "C" char D_0036B088[];
extern "C" char D_002EEF08[];
extern "C" char D_0036B0A8[];
extern "C" char D_0030EF20[];
extern "C" void *func_00234430(void * arg0, void * arg1);
extern "C" void *func_00234780(void * arg0, void * arg1);

struct RGBA { unsigned char r, g, b, a; };
extern "C" RGBA D_0030EF50[16];
static inline void SetRgba(RGBA *p, int r, int g, int b, int a)
{
    p->r = r; p->g = g; p->b = b; p->a = a;
}

extern "C" void func_00115A10(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            RGBA *p = D_0030EF50;
            SetRgba(p, 0, 0, 0, 15);
            ++p;
            SetRgba(p, 103, 103, 103, 125);
            ++p;
            SetRgba(p, 103, 103, 103, 84);
            ++p;
            SetRgba(p, 103, 103, 103, 63);
            ++p;
            SetRgba(p, 103, 103, 103, 42);
            ++p;
            SetRgba(p, 103, 103, 103, 118);
            ++p;
            SetRgba(p, 103, 103, 103, 110);
            ++p;
            SetRgba(p, 103, 103, 103, 31);
            ++p;
            SetRgba(p, 103, 103, 103, 77);
            ++p;
            SetRgba(p, 103, 103, 103, 128);
            ++p;
            SetRgba(p, 103, 103, 103, 71);
            ++p;
            SetRgba(p, 103, 103, 103, 18);
            ++p;
            SetRgba(p, 103, 103, 103, 96);
            ++p;
            SetRgba(p, 103, 103, 103, 54);
            ++p;
            SetRgba(p, 0, 0, 0, 128);
            ++p;
            SetRgba(p, 103, 103, 103, 0);
            func_00234430(D_0036B088, D_002EEF08);
            func_00234780(D_0036B0A8, D_0030EF20);
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
