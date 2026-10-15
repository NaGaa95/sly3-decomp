// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Recovered translation-unit initialization and destruction, with original
// global-object callbacks and shared fixed-pool reference registration.
extern "C" char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern "C" char D_004D2D60[], D_004D2E38[], D_004D2F10[];
extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" void *func_0011E100(void *p, int cb, int c, int cbAlign);
extern "C" char D_0036B138[];
extern "C" void func_00129E10(void *p);
extern "C" char D_0036BC10[];
extern "C" void func_002B50F8(void *p);
extern "C" void func_002BC7D0(void *p, int flags);
extern "C" char D_0036C2E0[];
extern "C" char D_0036C308[];
extern "C" void func_0018C750(void *p);
extern "C" void func_0027E190(void *p);
extern "C" char D_0036C6E8[];
extern "C" void func_001890E8(void *p);
extern "C" char D_0046F540[];
extern "C" char D_0046F550[];
extern "C" char D_0046F770[];
extern "C" char D_0046F7A0[];
extern "C" char D_0046F810[];
extern "C" char D_0046FAA0[];
extern "C" char D_0046FBE0[];
extern "C" char D_0046FC30[];
extern "C" char D_0046FC90[];
extern "C" char D_0046FD00[];
extern "C" void func_0021D770(void *p);
extern "C" void func_002BEEC0(void *p);
extern "C" void func_002B52B8(void *p);
extern "C" void func_0021EDE0(void *p);
extern "C" void func_0021FD90(void *p);
extern "C" void func_00220DE0(void *p);
extern "C" void func_00221928(void *p);
extern "C" void func_00221A78(void *p);
extern "C" void func_002227C8(void *p);
extern "C" void func_002BEFF8(void *p);
extern "C" void func_002BF030(void *p, int flags);
extern "C" void func_002BEFD8(void *p, int flags);
extern "C" void func_002BEFB8(void *p, int flags);
extern "C" void func_002BEF98(void *p, int flags);
extern "C" void func_002BEF78(void *p, int flags);
extern "C" void func_002BEF58(void *p, int flags);
extern "C" void func_002BEF38(void *p, int flags);
extern "C" void func_002BEF18(void *p, int flags);
extern "C" void func_002BEEF8(void *p, int flags);
extern "C" char D_00474FF0[];
extern "C" void func_00246BB8(void *p);
extern "C" void func_002BF410(void *p, int flags);
extern "C" char D_004BC220[];
extern "C" void func_002BFDA8(void *p);
extern "C" char D_004BC230[];
extern "C" void func_00283740(void *p);
extern "C" void func_002BFDB0(void *p, int flags);

extern "C" void func_0012A798(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_00129E10(D_0036B138);
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

extern "C" void func_00169558(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_002B50F8(D_0036BC10);
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
            func_002BC7D0(D_0036BC10, 2);
        }
    }
}

extern "C" void func_00183C10(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_0018C750(D_0036C2E0);
            func_0027E190(D_0036C308);
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

extern "C" void func_0018AE50(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_001890E8(D_0036C6E8);
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

extern "C" void func_00223308(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_0021D770(D_0046F540);
            func_002BEEC0(D_0046F550);
            func_002B52B8(D_0046F770);
            func_0021EDE0(D_0046F7A0);
            func_0021FD90(D_0046F810);
            func_00220DE0(D_0046FAA0);
            func_00221928(D_0046FBE0);
            func_00221A78(D_0046FC30);
            func_002227C8(D_0046FC90);
            func_002BEFF8(D_0046FD00);
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
            func_002BF030(D_0046FD00, 2);
            func_002BEFD8(D_0046FC90, 2);
            func_002BEFB8(D_0046FC30, 2);
            func_002BEF98(D_0046FBE0, 2);
            func_002BEF78(D_0046FAA0, 2);
            func_002BEF58(D_0046F810, 2);
            func_002BEF38(D_0046F7A0, 2);
            func_002BEF18(D_0046F770, 2);
            func_002BEEF8(D_0046F550, 2);
        }
    }
}

extern "C" void func_002491A0(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_00246BB8(D_00474FF0);
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
            func_002BF410(D_00474FF0, 2);
        }
    }
}

extern "C" void func_0027EFF8(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_002BFDA8(D_004BC220);
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

extern "C" void func_002852C0(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            func_00283740(D_004BC230);
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
            func_002BFDB0(D_004BC230, 2);
        }
    }
}
