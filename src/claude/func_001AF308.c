// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CLOCK { char pad[0x1C]; float scale; };
extern struct CLOCK g_clock;
#define AT(p, off, type) (*(type *)((char *)(p) + (off)))
int func_00154518(void *p, int k);
int func_00173428(void *p);
int func_001BD830(void *p, int k);
int func_001B5D08(void *p, int k);
int func_001BFFB8(void *p, int k);
int func_002503C8(void *p, float t);
int func_0013ADE0(void *p);
int func_001FBEA0(void *p);
int func_00279C28(void);
int func_001AF308(char *p, int k)
{
    int r;
    if (!func_00154518(p, k))
        return 0;
    switch (k) {
    case 3: case 0x26: case 0x27: case 0x28:
        break;
    default:
        {
            int r = 0;
            void *q = AT(p, 0x1108, void *);
            if (q)
                r = func_00173428(q) != 0;
            if (r)
                return 0;
        }
        break;
    }
    switch (k) {
    case 0x21:
        if (AT(p, 0x19E0, int) == 5)
            return 0;
        if (g_clock.scale == 1.0f)
            return 1;
        if (g_clock.scale == 0.25f)
            return 1;
        return 0;
    case 0x1C:
        return 1;
    case 0x22: case 0x25:
        return AT(p, 0x19E0, int) != 5;
    }
    {
        int r, n;
        switch (AT(p, 0x19E0, int)) {
        case 0: case 1: case 2: case 6: case 10: case 23:
            break;
        case 3:
            r = func_001BD830(p + 0x320, k);
            goto check;
        case 8:
            r = func_001B5D08(p + 0x500, k);
            goto check;
        case 9:
            r = func_001BFFB8(p + 0x1010, k);
        check:
            if (!r)
                return 0;
            break;
        case 4:
            n = 3;
            goto compare;
        case 24:
            n = 0x24;
            goto compare;
        case 19:
            if (k == 2)
                break;
            n = 0x23;
        compare:
            if (k != n)
                return 0;
            break;
        default:
            return 0;
        }
    }
    switch (k) {
    default:
        return 0;
    case 29: case 30:
        r = 0;
        if (!func_002503C8(p, 0.1f) || (AT(p, 0x50C, int) != -1 && (AT(p, 0x508, int) == 3 || AT(p, 0x508, int) == 4)))
            r = 1;
        return r;
    case 31:
        return AT(p, 0x1F44, int) && func_0013ADE0(p + 0x10D0);
    case 35:
        r = 0;
        if (AT(p, 0x19E0, int) == 0x13 || !func_002503C8(p, 0.1f))
            r = 1;
        return r;
    case 25:
        return AT(p, 0x1F48, int) && func_0013ADE0(p + 0x10D0) && AT(p, 0x1EC0, void *) && func_001FBEA0(AT(p, 0x1EC0, void *));
    case 26:
        if (func_002503C8(p, 0.1f))
            return 0;
        return AT(p, 0x19E0, int) == 6 && AT(p, 0x11B4, int);
    case 27:
        return AT(p, 0x19E0, int) == 3;
    case 32:
        if (AT(p, 0x11C4, int) == 4)
            return 0;
        if (AT(p, 0x10D4, int) != -1)
            return 0;
        switch (AT(p, 0x19E0, int)) {
        case 0: case 1: case 2: case 8: case 10:
            return 1;
        }
        return 0;
    case 38: case 39: case 40:
        if (!AT(p, 0x1108, int))
            return 0;
        if (AT(p, 0x10D4, int) != -1)
            return 0;
        switch (AT(p, 0x19E0, int)) {
        case 0: case 1: case 2: case 6: case 10:
            return 1;
        }
        return 0;
    case 36:
        return func_00279C28() != 0;
    case 1: case 2: case 3:
        return 1;
    }
}
